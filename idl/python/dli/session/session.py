import time
import threading
from typing import Dict, Tuple, Optional, Callable
from ..core import BitCursor
from ..protocol import DliHeader, DliMessage
from ..generated.messages.MessageAcknowledgement import MessageAcknowledgement

class DliSession:
    def __init__(self, transport=None):
        self.transport = transport
        self.dispatcher = None # Placeholder for future logic
        self.pending_acks: Dict[Tuple[int, int, int], dict] = {}
        self._lock = threading.Lock()
        self.source_id = 0x01
        self._last_ts = 0

    def process_incoming(self, data: bytes):
        cursor = BitCursor(bytearray(data))
        header = DliHeader()
        if not header.deserialize(cursor):
            return

        # Handle ACK message (#17000)
        if header.message_type == 17000:
            self._handle_ack(header, data)
            return

        # Auto-ACK logic
        if header.requires_ack():
            self._send_auto_ack(header)

    def _handle_ack(self, header: DliHeader, data: bytes):
        cursor = BitCursor(bytearray(data))
        msg = DliMessage(MessageAcknowledgement)
        if msg.deserialize(cursor):
            key = (header.source_id, msg.body.original_message_type, msg.body.original_message_time_stamp)
            with self._lock:
                if key in self.pending_acks:
                    entry = self.pending_acks.pop(key)
                    if entry['callback']:
                        entry['callback'](True)

    def _send_auto_ack(self, original_header: DliHeader):
        ack = DliMessage(MessageAcknowledgement)
        ack.header.message_type = 17000
        ack.header.source_id = original_header.destination_id
        ack.header.destination_id = original_header.source_id
        
        ack.body.time_stamp = self._generate_ts()
        ack.body.has_time_stamp = True
        ack.body.original_message_time_stamp = 0 # Simplified for now, should be from original
        ack.body.has_original_message_time_stamp = True
        ack.body.original_message_type = original_header.message_type
        ack.body.has_original_message_type = True
        ack.body.acknowledgement_type = 1 # Received
        ack.body.has_acknowledgement_type = True

        buffer = bytearray(128)
        cursor = BitCursor(buffer)
        ack.serialize(cursor)
        if self.transport:
            self.transport.send(bytes(buffer[:cursor.pos]))

    def send_reliable(self, msg: DliMessage, callback: Callable[[bool], None] = None):
        # Set message properties to require ACK (Version 1, Bit 15)
        msg.header.message_properties |= 0x8000
        
        buffer = bytearray(256)
        cursor = BitCursor(buffer)
        msg.serialize(cursor)
        packet = bytes(buffer[:cursor.pos])

        # Save for retransmission
        key = (msg.header.destination_id, msg.header.message_type, 0) # simplified key
        with self._lock:
            self.pending_acks[key] = {
                'packet': packet,
                'callback': callback,
                'retries': 0,
                'deadline': time.time() + 0.5
            }
        
        if self.transport:
            self.transport.send(packet)

    def _generate_ts(self) -> int:
        now = int(time.time() * 1000)
        if now <= self._last_ts:
            now = self._last_ts + 1
        self._last_ts = now
        return now
