from dli.core.bit_cursor import BitCursor
from dli.utils import BAM, Scaled
import math

class VehicleConfigurationCommand:
    def __init__(self):
        # Presence Vector
        self.pv = 0
        
        self.time_stamp = 0
        self.has_time_stamp = False
        
        self.energy_storage_unit = 0
        self.has_energy_storage_unit = False
        
        self.initial_propulsion_energy = 0.0
        self.has_initial_propulsion_energy = False
        

    def serialize(self, cursor: BitCursor):
        # 1. Prepare PV
        self.pv = 0
        
        if self.has_time_stamp:
            self.pv |= (1 << 0)
        
        if self.has_energy_storage_unit:
            self.pv |= (1 << 1)
        
        if self.has_initial_propulsion_energy:
            self.pv |= (1 << 2)
        

        # 2. Write PV
        
        cursor.write_uint8(self.pv)
        
        
        
        
        

        # 3. Write Fields
        
        if self.has_time_stamp:
            cursor.write_uint40(self.time_stamp)
        
        if self.has_energy_storage_unit:
            cursor.write_uint8(self.energy_storage_unit)
        
        if self.has_initial_propulsion_energy:
            cursor.write_uint16(Scaled.to_scaled(self.initial_propulsion_energy, 0.0, 0.002))
        

    def deserialize(self, cursor: BitCursor):
        # 1. Read PV
        
        self.pv = cursor.read_uint8()
        
        
        
        
        

        # 2. Read Fields
        
        if self.pv & (1 << 0):
            self.has_time_stamp = True
            self.time_stamp = cursor.read_uint40()
        else:
            self.has_time_stamp = False
        
        if self.pv & (1 << 1):
            self.has_energy_storage_unit = True
            self.energy_storage_unit = cursor.read_uint8()
        else:
            self.has_energy_storage_unit = False
        
        if self.pv & (1 << 2):
            self.has_initial_propulsion_energy = True
            self.initial_propulsion_energy = Scaled.from_scaled(cursor.read_uint16(), 0.0, 0.002)
        else:
            self.has_initial_propulsion_energy = False
        
