from .header import DliHeader
from dli.core.bit_cursor import BitCursor
from dli.core.checksum import Checksum

class DliMessage:
    def __init__(self, body_cls):
        self.header = DliHeader()
        self.body = body_cls()
        self.checksum = None

    def serialize(self, cursor: BitCursor):
        header_start = cursor.pos
        self.header.serialize(cursor)

        body_start = cursor.pos
        self.body.serialize(cursor)
        body_end = cursor.pos

        # Update payload length
        self.header.payload_length = body_end - body_start
        
        # Go back and re-serialize header with correct length
        current_pos = cursor.pos
        cursor.pos = header_start
        self.header.serialize(cursor)
        cursor.pos = current_pos

        # Checksum calculation
        cksum_type = self.header.get_checksum_type()
        if cksum_type > 0:
            data_to_checksum = cursor.data[header_start:body_end]
            if cksum_type == 1: # CRC-16
                self.checksum = Checksum.calculate_crc16(data_to_checksum)
                cursor.write_uint16(self.checksum)
            elif cksum_type >= 2: # CRC-32
                self.checksum = Checksum.calculate_crc32(data_to_checksum)
                cursor.write_uint32(self.checksum)

    def deserialize(self, cursor: BitCursor) -> bool:
        if not self.header.deserialize(cursor):
            return False
        
        self.body.deserialize(cursor)
        if cursor.error():
            return False

        cksum_type = self.header.get_checksum_type()
        if cksum_type == 1:
            self.checksum = cursor.read_uint16()
        elif cksum_type >= 2:
            self.checksum = cursor.read_uint32()
        
        return cursor.error() is None
