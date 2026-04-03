import struct

class BitCursor:
    def __init__(self, data: bytearray):
        self.data = data
        self.pos = 0
        self._error = None

    def read_uint8(self) -> int:
        if self.pos + 1 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = self.data[self.pos]
        self.pos += 1
        return val

    def write_uint8(self, val: int):
        if self.pos + 1 > len(self.data):
            self._error = "EndOfStream"
            return
        self.data[self.pos] = int(val) & 0xFF
        self.pos += 1

    def read_int8(self) -> int:
        if self.pos + 1 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = self.data[self.pos]
        if val & 0x80:
            val -= 0x100
        self.pos += 1
        return val

    def write_int8(self, val: int):
        if self.pos + 1 > len(self.data):
            self._error = "EndOfStream"
            return
        self.data[self.pos] = int(val) & 0xFF
        self.pos += 1

    def read_uint16(self) -> int:
        if self.pos + 2 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = struct.unpack_from(">H", self.data, self.pos)[0]
        self.pos += 2
        return val

    def write_uint16(self, val: int):
        if self.pos + 2 > len(self.data):
            self._error = "EndOfStream"
            return
        struct.pack_into(">H", self.data, self.pos, int(val))
        self.pos += 2

    def read_uint32(self) -> int:
        if self.pos + 4 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = struct.unpack_from(">I", self.data, self.pos)[0]
        self.pos += 4
        return val

    def write_uint32(self, val: int):
        if self.pos + 4 > len(self.data):
            self._error = "EndOfStream"
            return
        struct.pack_into(">I", self.data, self.pos, int(val))
        self.pos += 4

    def read_int16(self) -> int:
        if self.pos + 2 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = struct.unpack_from(">h", self.data, self.pos)[0]
        self.pos += 2
        return val

    def write_int16(self, val: int):
        if self.pos + 2 > len(self.data):
            self._error = "EndOfStream"
            return
        struct.pack_into(">h", self.data, self.pos, int(val))
        self.pos += 2

    def read_int32(self) -> int:
        if self.pos + 4 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = struct.unpack_from(">i", self.data, self.pos)[0]
        self.pos += 4
        return val

    def write_int32(self, val: int):
        if self.pos + 4 > len(self.data):
            self._error = "EndOfStream"
            return
        struct.pack_into(">i", self.data, self.pos, int(val))
        self.pos += 4

    # Special STANAG types
    def write_int24(self, val: int):
        if self.pos + 3 > len(self.data):
            self._error = "EndOfStream"
            return
        val = int(val)
        self.data[self.pos] = (val >> 16) & 0xFF
        self.data[self.pos+1] = (val >> 8) & 0xFF
        self.data[self.pos+2] = val & 0xFF
        self.pos += 3

    def read_int24(self) -> int:
        if self.pos + 3 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = (self.data[self.pos] << 16) | (self.data[self.pos+1] << 8) | self.data[self.pos+2]
        # Sign extension
        if val & 0x800000:
            val -= 0x1000000
        self.pos += 3
        return val

    def write_uint24(self, val: int):
        if self.pos + 3 > len(self.data):
            self._error = "EndOfStream"
            return
        val = int(val)
        self.data[self.pos] = (val >> 16) & 0xFF
        self.data[self.pos+1] = (val >> 8) & 0xFF
        self.data[self.pos+2] = val & 0xFF
        self.pos += 3

    def read_uint24(self) -> int:
        if self.pos + 3 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = (self.data[self.pos] << 16) | (self.data[self.pos+1] << 8) | self.data[self.pos+2]
        self.pos += 3
        return val

    def write_uint40(self, val: int):
        if self.pos + 5 > len(self.data):
            self._error = "EndOfStream"
            return
        val = int(val)
        self.data[self.pos] = (val >> 32) & 0xFF
        self.data[self.pos+1] = (val >> 24) & 0xFF
        self.data[self.pos+2] = (val >> 16) & 0xFF
        self.data[self.pos+3] = (val >> 8) & 0xFF
        self.data[self.pos+4] = val & 0xFF
        self.pos += 5

    def read_uint40(self) -> int:
        if self.pos + 5 > len(self.data):
            self._error = "EndOfStream"
            return 0
        val = (self.data[self.pos] << 32) | (self.data[self.pos+1] << 24) | \
              (self.data[self.pos+2] << 16) | (self.data[self.pos+3] << 8) | self.data[self.pos+4]
        self.pos += 5
        return val

    def error(self):
        return self._error
