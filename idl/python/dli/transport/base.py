from abc import ABC, abstractmethod

class ITransport(ABC):
    """Abstract Base Class for DLI Transports"""
    
    @abstractmethod
    def send(self, data: bytes):
        """Send raw bytes over the transport"""
        pass

    @abstractmethod
    def close(self):
        """Close the transport connection"""
        pass
