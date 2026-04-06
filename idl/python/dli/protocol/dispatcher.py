from typing import Callable, Dict, Optional

from .header import DliHeader
from .profile import Profile
from ..core import BitCursor, Logger


class Dispatcher:
    """Routes Python DLI messages by message type, matching the C++ dispatcher shape."""

    MessageHandler = Callable[[DliHeader, BitCursor], int]

    def __init__(self):
        self._handlers: Dict[int, Dispatcher.MessageHandler] = {}
        self._active_profile: Optional[Profile] = None

    def register_handler(self, message_type: int, handler: MessageHandler) -> None:
        self._handlers[message_type] = handler

    def set_profile(self, profile: Profile) -> None:
        self._active_profile = profile
        Logger.info(f"Dispatcher profile set to: {profile.name} (LOI {profile.loi})")

    def dispatch(self, data: bytes) -> Optional[int]:
        if len(data) < DliHeader.FIXED_SIZE:
            return None

        cursor = BitCursor(bytearray(data))
        header = DliHeader()
        if not header.deserialize(cursor):
            return None

        expected_total = DliHeader.FIXED_SIZE + header.payload_length
        if len(data) < expected_total:
            return None

        if self._active_profile is not None and not self._active_profile.is_permitted(header.message_type):
            Logger.warn(
                f"Message #{header.message_type} is REJECTED by active profile: {self._active_profile.name}"
            )
            return None

        handler = self._handlers.get(header.message_type)
        if handler is None:
            return None

        payload = bytearray(data[DliHeader.FIXED_SIZE:expected_total])
        payload_cursor = BitCursor(payload)
        return handler(header, payload_cursor)
