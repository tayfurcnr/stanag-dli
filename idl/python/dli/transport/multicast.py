import socket
import struct
from typing import Callable, Optional

from .base import ITransport


class MulticastTransport(ITransport):
    """A simple non-blocking UDP multicast transport for the Python SDK."""

    def __init__(
        self,
        multicast_group: str = "225.200.1.0",
        port: int = 51017,
        local_interface: str = "0.0.0.0",
        ttl: int = 1,
        bind_socket: bool = True,
        autostart: bool = True,
    ):
        self.multicast_group = multicast_group
        self.port = port
        self.local_interface = local_interface
        self.ttl = ttl
        self.bind_socket = bind_socket
        self._sock: Optional[socket.socket] = None
        self._membership: Optional[bytes] = None
        self._tx_count = 0
        self._rx_count = 0
        if autostart:
            self.start()

    def start(self) -> bool:
        if self._sock is not None:
            return True

        sock = None
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, self.ttl)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 1)

            if self.bind_socket:
                sock.bind(("", self.port))
                membership = struct.pack(
                    "4s4s",
                    socket.inet_aton(self.multicast_group),
                    socket.inet_aton(self.local_interface),
                )
                sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, membership)
                self._membership = membership

            sock.setblocking(False)
            self._sock = sock
            return True
        except OSError:
            if sock is not None:
                sock.close()
            self._sock = None
            self._membership = None
            return False

    def send(self, data: bytes) -> bool:
        if self._sock is None:
            return False
        sent = self._sock.sendto(data, (self.multicast_group, self.port))
        if sent > 0:
            self._tx_count += 1
        return sent > 0

    def poll(self, callback: Callable[[bytes], None]) -> None:
        if self._sock is None:
            return

        while True:
            try:
                data, _addr = self._sock.recvfrom(65535)
            except BlockingIOError:
                break
            if not data:
                break
            self._rx_count += 1
            callback(data)

    def flush(self) -> None:
        return None

    def stop(self) -> None:
        if self._sock is None:
            return
        if self._membership is not None:
            try:
                self._sock.setsockopt(socket.IPPROTO_IP, socket.IP_DROP_MEMBERSHIP, self._membership)
            except OSError:
                pass
        self._sock.close()
        self._sock = None
        self._membership = None

    @property
    def tx_count(self) -> int:
        return self._tx_count

    @property
    def rx_count(self) -> int:
        return self._rx_count
