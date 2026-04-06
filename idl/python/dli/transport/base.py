from abc import ABC, abstractmethod
from typing import Callable


DataCallback = Callable[[bytes], None]


class ITransport(ABC):
    """Abstract Base Class for DLI Transports"""

    @abstractmethod
    def start(self) -> bool:
        """Start the transport and acquire underlying resources."""
        pass

    @abstractmethod
    def stop(self) -> None:
        """Stop the transport and release underlying resources."""
        pass

    @abstractmethod
    def send(self, data: bytes) -> bool:
        """Send raw bytes over the transport"""
        pass

    @abstractmethod
    def poll(self, callback: DataCallback) -> None:
        """Poll for incoming frames and invoke the callback for each message."""
        pass

    @abstractmethod
    def flush(self) -> None:
        """Flush buffered transport state if supported."""
        pass

    def close(self):
        """Backward-compatible alias for stop()."""
        self.stop()
        pass
