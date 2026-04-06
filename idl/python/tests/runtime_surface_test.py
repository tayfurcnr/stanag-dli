import os
import socket
import sys
from unittest.mock import patch


TEST_DIR = os.path.dirname(os.path.abspath(__file__))
PYTHON_ROOT = os.path.dirname(TEST_DIR)
if PYTHON_ROOT not in sys.path:
    sys.path.insert(0, PYTHON_ROOT)

from dli.core import BitCursor
from dli.generated.messages.Heartbeat import Heartbeat
from dli.generated.messages.MessageAcknowledgement import MessageAcknowledgement
from dli.generated.profiles import Profiles
from dli.protocol import DliHeader, Dispatcher, DliMessage, Profile
from dli.session import DliSession
from dli.transport import MulticastTransport


def _build_packet(message_type: int, payload: bytes = b"", message_properties: int = 0) -> bytes:
    header = DliHeader()
    header.message_type = message_type
    header.source_id = 0x01020304
    header.destination_id = 0x05060708
    header.payload_length = len(payload)
    header.message_properties = message_properties

    buffer = bytearray(DliHeader.FIXED_SIZE + len(payload))
    cursor = BitCursor(buffer)
    header.serialize(cursor)
    buffer[cursor.pos:cursor.pos + len(payload)] = payload
    return bytes(buffer)


def test_profile_allow_and_deny():
    profile = Profile("LOI4", 4)

    assert profile.is_permitted(4000) is False

    profile.allow(4000)
    assert profile.is_permitted(4000) is True

    profile.deny(4000)
    assert profile.is_permitted(4000) is False


def test_dispatcher_routes_permitted_messages():
    dispatcher = Dispatcher()
    profile = Profile("LOI4", 4)
    profile.allow(4000)
    dispatcher.set_profile(profile)

    captured = {}

    def handler(header: DliHeader, payload_cursor: BitCursor) -> int:
        captured["message_type"] = header.message_type
        captured["payload"] = bytes(payload_cursor.data)
        return header.message_type

    dispatcher.register_handler(4000, handler)
    result = dispatcher.dispatch(_build_packet(4000, b"\xAA\xBB\xCC"))

    assert result == 4000
    assert captured == {"message_type": 4000, "payload": b"\xAA\xBB\xCC"}


def test_dispatcher_rejects_messages_blocked_by_profile():
    dispatcher = Dispatcher()
    profile = Profile("LOI2", 2)
    profile.allow(16002)
    dispatcher.set_profile(profile)
    dispatcher.register_handler(4000, lambda _header, _payload: 1)

    assert dispatcher.dispatch(_build_packet(4000)) is None


def test_dispatcher_rejects_truncated_payloads():
    dispatcher = Dispatcher()
    dispatcher.register_handler(4000, lambda _header, _payload: 1)

    truncated = _build_packet(4000, b"\xAA\xBB")[:-1]
    assert dispatcher.dispatch(truncated) is None


def test_generated_python_profile_matches_expected_messages():
    loi4 = Profiles.LOI4_UA_Control()

    assert loi4.loi == 4
    assert loi4.is_permitted(3002) is True
    assert loi4.is_permitted(4000) is True
    assert loi4.is_permitted(3) is True
    assert loi4.is_permitted(16002) is False
    assert loi4.is_permitted(99999) is False


class _FakeSocket:
    def __init__(self, recv_packets=None):
        self.recv_packets = list(recv_packets or [])
        self.sent_packets = []
        self.sockopts = []
        self.bound_to = None
        self.blocking = True
        self.closed = False

    def setsockopt(self, level, option, value):
        self.sockopts.append((level, option, value))

    def bind(self, addr):
        self.bound_to = addr

    def setblocking(self, enabled):
        self.blocking = enabled

    def sendto(self, data, addr):
        self.sent_packets.append((bytes(data), addr))
        return len(data)

    def recvfrom(self, _bufsize):
        if self.recv_packets:
            return self.recv_packets.pop(0), ("127.0.0.1", 51017)
        raise BlockingIOError()

    def close(self):
        self.closed = True


class _BrokenSocket:
    def setsockopt(self, _level, _option, _value):
        return None

    def bind(self, _addr):
        raise OSError("bind failed")

    def close(self):
        return None


def test_multicast_transport_send_poll_and_close():
    packet = _build_packet(16002, b"\x10\x20")
    fake_socket = _FakeSocket(recv_packets=[packet])

    with patch("dli.transport.multicast.socket.socket", return_value=fake_socket):
        transport = MulticastTransport(multicast_group="239.1.1.1", port=50123)
        received = []

        assert transport.send(b"\x01\x02\x03") is True
        transport.poll(received.append)
        transport.close()

    assert fake_socket.bound_to == ("", 50123)
    assert fake_socket.blocking is False
    assert fake_socket.sent_packets == [(b"\x01\x02\x03", ("239.1.1.1", 50123))]
    assert received == [packet]
    assert transport.tx_count == 1
    assert transport.rx_count == 1
    assert fake_socket.closed is True
    assert any(opt == socket.IP_ADD_MEMBERSHIP for _lvl, opt, _value in fake_socket.sockopts)
    assert any(opt == socket.IP_DROP_MEMBERSHIP for _lvl, opt, _value in fake_socket.sockopts)


def test_multicast_transport_start_failure_returns_false():
    with patch("dli.transport.multicast.socket.socket", return_value=_BrokenSocket()):
        transport = MulticastTransport(autostart=False)
        assert transport.start() is False


class _FakeTransport:
    def __init__(self):
        self.sent_packets = []
        self.started = False
        self.stopped = False
        self.flushed = False
        self.polled = False
        self.polled_packets = []

    def start(self):
        self.started = True
        return True

    def send(self, data: bytes):
        self.sent_packets.append(bytes(data))
        return True

    def poll(self, callback):
        self.polled = True
        for packet in self.polled_packets:
            callback(packet)

    def flush(self):
        self.flushed = True

    def stop(self):
        self.stopped = True


def _decode_ack(packet: bytes) -> DliMessage:
    msg = DliMessage(MessageAcknowledgement)
    assert msg.deserialize(BitCursor(bytearray(packet))) is True
    return msg


def test_session_dispatches_and_sends_auto_ack_with_original_timestamp():
    dispatcher = Dispatcher()
    profile = Profile("LOI4", 4)
    profile.allow(16002)
    dispatcher.set_profile(profile)
    transport = _FakeTransport()
    session = DliSession(dispatcher, transport=transport)

    def heartbeat_handler(_header: DliHeader, payload_cursor: BitCursor) -> int:
        msg = DliMessage(Heartbeat)
        assert msg.body.deserialize(payload_cursor) is None
        return msg.body.time_stamp

    dispatcher.register_handler(16002, heartbeat_handler)

    outbound = DliMessage(Heartbeat)
    outbound.header.message_type = 16002
    outbound.header.source_id = 0x10
    outbound.header.destination_id = 0x20
    outbound.header.message_properties = 0x8000
    outbound.body.time_stamp = 424242
    outbound.body.has_time_stamp = True

    buffer = bytearray(128)
    cursor = BitCursor(buffer)
    outbound.serialize(cursor)

    session.process_incoming(bytes(buffer[:cursor.pos]))

    assert len(transport.sent_packets) == 1
    ack = _decode_ack(transport.sent_packets[0])
    assert ack.header.message_type == 17000
    assert ack.body.original_message_type == 16002
    assert ack.body.original_message_time_stamp == 424242


def test_session_reliable_ack_correlation_and_timeout():
    transport = _FakeTransport()
    dispatcher = Dispatcher()
    session = DliSession(dispatcher, transport=transport)
    callbacks = []

    msg = DliMessage(Heartbeat)
    msg.header.message_type = 16002
    msg.header.source_id = 0x01
    msg.header.destination_id = 0x99
    msg.body.time_stamp = 777
    msg.body.has_time_stamp = True

    assert session.send_reliable(msg, max_retries=1, callback=callbacks.append) is True
    assert len(transport.sent_packets) == 1

    ack = DliMessage(MessageAcknowledgement)
    ack.header.message_type = 17000
    ack.header.source_id = 0x99
    ack.header.destination_id = 0x01
    ack.body.time_stamp = 1000
    ack.body.has_time_stamp = True
    ack.body.original_message_time_stamp = 777
    ack.body.has_original_message_time_stamp = True
    ack.body.original_message_type = 16002
    ack.body.has_original_message_type = True
    ack.body.acknowledgement_type = 1
    ack.body.has_acknowledgement_type = True

    ack_buffer = bytearray(128)
    ack_cursor = BitCursor(ack_buffer)
    ack.serialize(ack_cursor)
    session.process_incoming(bytes(ack_buffer[:ack_cursor.pos]))

    assert callbacks == [True]
    assert session.pending_acks == {}

    timeout_msg = DliMessage(Heartbeat)
    timeout_msg.header.message_type = 16002
    timeout_msg.header.destination_id = 0x55
    timeout_msg.body.time_stamp = 888
    timeout_msg.body.has_time_stamp = True

    assert session.send_reliable(timeout_msg, max_retries=0, callback=callbacks.append) is True
    key = (0x55, 16002, 888)
    session.pending_acks[key]["deadline"] = 0
    session.tick()

    assert callbacks[-1] is False
    assert key not in session.pending_acks


def test_session_manages_multiple_transports_symmetrically():
    transport_a = _FakeTransport()
    transport_b = _FakeTransport()
    session = DliSession(Dispatcher())
    session.add_transport(transport_a)
    session.add_transport(transport_b)

    assert session.transport is transport_a
    assert session.start_transports() is True

    assert session.send_raw(b"\xAA\xBB") is True
    session.flush_transports()
    session.stop_transports()

    assert transport_a.started is True and transport_b.started is True
    assert transport_a.sent_packets == [b"\xAA\xBB"]
    assert transport_b.sent_packets == [b"\xAA\xBB"]
    assert transport_a.flushed is True and transport_b.flushed is True
    assert transport_a.stopped is True and transport_b.stopped is True


def test_session_spin_once_polls_transports_and_ticks():
    dispatcher = Dispatcher()
    profile = Profile("LOI4", 4)
    profile.allow(16002)
    dispatcher.set_profile(profile)

    transport = _FakeTransport()
    session = DliSession(dispatcher, transport=transport)
    observed = []

    def heartbeat_handler(_header: DliHeader, payload_cursor: BitCursor) -> int:
        msg = DliMessage(Heartbeat)
        msg.body.deserialize(payload_cursor)
        observed.append(msg.body.time_stamp)
        return msg.body.time_stamp

    dispatcher.register_handler(16002, heartbeat_handler)

    msg = DliMessage(Heartbeat)
    msg.header.message_type = 16002
    msg.header.source_id = 0x10
    msg.header.destination_id = 0x20
    msg.body.time_stamp = 12345
    msg.body.has_time_stamp = True

    payload = bytearray(128)
    cursor = BitCursor(payload)
    msg.serialize(cursor)
    transport.polled_packets = [bytes(payload[:cursor.pos])]

    session.spin_once()

    assert transport.polled is True
    assert observed == [12345]


def test_session_requires_dispatcher():
    try:
        DliSession(None)
    except ValueError as exc:
        assert "dispatcher is required" in str(exc)
    else:
        raise AssertionError("DliSession should require a dispatcher")


def test_session_tick_does_not_retry_acknowledged_entry():
    transport = _FakeTransport()
    session = DliSession(Dispatcher(), transport=transport)

    key = (0x55, 16002, 999)
    session.pending_acks[key] = {
        "packet": b"\xAA\xBB",
        "callback": None,
        "retries": 0,
        "max_retries": 1,
        "hop_count": 0,
        "deadline": 0,
    }

    with session._lock:
        session.pending_acks.pop(key)

    session.tick()
    assert transport.sent_packets == []
