import math

class BAM:
    """Standard Angular Measurements (BAM) Utility for STANAG 4586"""
    
    @staticmethod
    def to_bam16(val_rad: float) -> int:
        return int(((val_rad + math.pi) / (2 * math.pi)) * 65535) & 0xFFFF

    @staticmethod
    def from_bam16(val_uint16: int) -> float:
        return (val_uint16 / 65535.0 * 2 * math.pi) - math.pi

    @staticmethod
    def to_bam32(val_rad: float) -> int:
        return int(((val_rad + math.pi) / (2 * math.pi)) * 4294967295) & 0xFFFFFFFF

    @staticmethod
    def from_bam32(val_uint32: int) -> float:
        return (val_uint32 / 4294967295.0 * 2 * math.pi) - math.pi

class Scaled:
    """Linear Scaling Utility for STANAG 4586"""
    
    @staticmethod
    def to_scaled(val: float, offset: float, scale: float) -> int:
        return int((val - offset) / scale)

    @staticmethod
    def from_scaled(val_int: int, offset: float, scale: float) -> float:
        return (val_int * scale) + offset
