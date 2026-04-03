from dli.core.bit_cursor import BitCursor

class DliHeader:
    FIXED_SIZE = 20

    def __init__(self):
        self.reserved_start = 0
        self.payload_length = 0
        self.source_id = 0
        self.destination_id = 0
        self.message_type = 0
        self.message_properties = 0
        self.reserved_end = 0

    def serialize(self, cursor: BitCursor):
        cursor.write_uint16(self.reserved_start)
        cursor.write_uint16(self.payload_length)
        cursor.write_uint32(self.source_id)
        cursor.write_uint32(self.destination_id)
        cursor.write_uint16(self.message_type)
        cursor.write_uint16(self.message_properties)
        cursor.write_uint32(self.reserved_end)

    def deserialize(self, cursor: BitCursor) -> bool:
        self.reserved_start = cursor.read_uint16()
        self.payload_length = cursor.read_uint16()
        self.source_id = cursor.read_uint32()
        self.destination_id = cursor.read_uint32()
        self.message_type = cursor.read_uint16()
        self.message_properties = cursor.read_uint16()
        self.reserved_end = cursor.read_uint32()
        return cursor.error() is None

    def get_checksum_type(self) -> int:
        return (self.message_properties >> 6) & 0x03

    def requires_ack(self) -> bool:
        return (self.message_properties & 0x8000) != 0
