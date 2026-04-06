import threading
import time
from typing import Callable, Dict, List, Optional, Tuple

from ..core import BitCursor
from ..core.checksum import Checksum
from ..generated.messages.MessageAcknowledgement import MessageAcknowledgement
from ..protocol import DliHeader, DliMessage


class DliSession:
    def __init__(self, dispatcher, transport=None):
        if dispatcher is None:
            raise ValueError("dispatcher is required")
        self.dispatcher = dispatcher
        self.transports: List[object] = []
        self.pending_acks: Dict[Tuple[int, int, int], dict] = {}
        self._lock = threading.Lock()
        self.source_id = 0x01
        self._last_ts = 0
        if transport is not None:
            self.add_transport(transport)

    def set_dispatcher(self, dispatcher) -> None:
        self.dispatcher = dispatcher

    @property
    def transport(self):
        return self.transports[0] if self.transports else None

    def add_transport(self, transport) -> None:
        if transport is not None:
            self.transports.append(transport)

    def start_transports(self) -> bool:
        any_success = False
        for transport in self.transports:
            if transport.start():
                any_success = True
        return any_success

    def stop_transports(self) -> None:
        for transport in self.transports:
            transport.stop()

    def flush_transports(self) -> None:
        for transport in self.transports:
            transport.flush()

    def poll_transports(self) -> None:
        for transport in self.transports:
            transport.poll(self.process_incoming)

    def spin_once(self) -> None:
        self.poll_transports()
        self.tick()

    def send_raw(self, data: bytes) -> bool:
        any_success = False
        for transport in self.transports:
            if transport.send(data):
                any_success = True
        return any_success

    def process_incoming(self, data: bytes):
        cursor = BitCursor(bytearray(data))
        header = DliHeader()
        if not header.deserialize(cursor):
            return
        if len(data) < (DliHeader.FIXED_SIZE + header.payload_length):
            return

        checksum_type = header.get_checksum_type()
        expected_total = DliHeader.FIXED_SIZE + header.payload_length
        checksum_size = 0
        if checksum_type == 0x01:
            checksum_size = 2
        elif checksum_type >= 0x02:
            checksum_size = 4

        if checksum_size:
            if len(data) < expected_total + checksum_size:
                return
            payload = data[:expected_total]
            actual = int.from_bytes(data[expected_total:expected_total + checksum_size], "big")
            if checksum_type == 0x01:
                expected = Checksum.calculate_crc16(payload)
            else:
                expected = Checksum.calculate_crc32(payload)
            if actual != expected:
                return

        if header.message_type == 17000:
            self._handle_ack(header, data)
            return

        dispatch_result = None
        if self.dispatcher is not None:
            dispatch_result = self.dispatcher.dispatch(data)

        if dispatch_result is not None and header.requires_ack():
            self._send_auto_ack(header, dispatch_result)

    def _handle_ack(self, header: DliHeader, data: bytes):
        cursor = BitCursor(bytearray(data))
        msg = DliMessage(MessageAcknowledgement)
        if msg.deserialize(cursor):
            if not msg.body.has_original_message_type or not msg.body.has_original_message_time_stamp:
                return
            key = (header.source_id, msg.body.original_message_type, msg.body.original_message_time_stamp)
            with self._lock:
                if key in self.pending_acks:
                    entry = self.pending_acks.pop(key)
                    if entry["callback"]:
                        entry["callback"](True)

    def _send_auto_ack(self, original_header: DliHeader, original_ts: int):
        ack = DliMessage(MessageAcknowledgement)
        ack.header.message_type = 17000
        ack.header.source_id = original_header.destination_id
        ack.header.destination_id = original_header.source_id

        ack.body.time_stamp = self._generate_ts()
        ack.body.has_time_stamp = True
        ack.body.original_message_time_stamp = original_ts
        ack.body.has_original_message_time_stamp = True
        ack.body.original_message_type = original_header.message_type
        ack.body.has_original_message_type = True
        ack.body.acknowledgement_type = 1
        ack.body.has_acknowledgement_type = True

        buffer = bytearray(128)
        cursor = BitCursor(buffer)
        ack.serialize(cursor)
        self.send_raw(bytes(buffer[:cursor.pos]))

    def send_reliable(
        self,
        msg: DliMessage,
        max_retries: int = 3,
        hop_count: int = 0,
        callback: Callable[[bool], None] = None,
    ):
        if hasattr(msg.body, "time_stamp") and getattr(msg.body, "time_stamp", 0) == 0:
            msg.body.time_stamp = self._generate_ts()
            if hasattr(msg.body, "has_time_stamp"):
                msg.body.has_time_stamp = True

        msg.header.message_properties |= 0x8000

        buffer = bytearray(256)
        cursor = BitCursor(buffer)
        msg.serialize(cursor)
        packet = bytes(buffer[:cursor.pos])

        original_ts = getattr(msg.body, "time_stamp", 0)
        key = (msg.header.destination_id, msg.header.message_type, original_ts)
        with self._lock:
            self.pending_acks[key] = {
                "packet": packet,
                "callback": callback,
                "retries": 0,
                "max_retries": max_retries,
                "hop_count": hop_count,
                "deadline": self._current_time_ms() + self._calculate_timeout(hop_count),
            }
        return self.send_raw(packet)

    def tick(self):
        now = self._current_time_ms()
        to_retry = []
        expired = []

        with self._lock:
            for key, entry in list(self.pending_acks.items()):
                if now < entry["deadline"]:
                    continue

                if entry["retries"] < entry["max_retries"]:
                    entry["retries"] += 1
                    entry["deadline"] = now + self._calculate_timeout(entry["hop_count"])
                    to_retry.append(bytes(entry["packet"]))
                else:
                    callback = entry.get("callback")
                    self.pending_acks.pop(key, None)
                    expired.append(callback)

        for packet in to_retry:
            self.send_raw(packet)

        for callback in expired:
            if callback:
                callback(False)

    def _calculate_timeout(self, hop_count: int) -> int:
        return 500 + (hop_count * 100)

    def _current_time_ms(self) -> int:
        return int(time.monotonic() * 1000)

    def _generate_ts(self) -> int:
        now = self._current_time_ms()
        if now <= self._last_ts:
            now = self._last_ts + 1
        self._last_ts = now
        return now

    def close(self) -> None:
        self.stop_transports()
