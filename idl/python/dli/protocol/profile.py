class Profile:
    """A lightweight Python equivalent of the C++ AEP-84 profile filter."""

    def __init__(self, name: str, loi: int):
        self._name = name
        self._loi = loi
        self._allowed_messages = set()

    def allow(self, message_type: int) -> None:
        self._allowed_messages.add(message_type)

    def deny(self, message_type: int) -> None:
        self._allowed_messages.discard(message_type)

    def is_permitted(self, message_type: int) -> bool:
        if not self._allowed_messages:
            return False
        return message_type in self._allowed_messages

    @property
    def name(self) -> str:
        return self._name

    @property
    def loi(self) -> int:
        return self._loi
