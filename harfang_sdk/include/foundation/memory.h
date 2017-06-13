// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {
namespace memory {

/// Return smallest number of bits that can be used to represent a value.
int GetBitCount(int value);
/// Return the position in bit of the first non-zero bit.
int GetShiftCount(int value);
/// Return the number of bit set in a given value.
int CountSetBit(int value);

void WriteBit(void *ptr, unsigned offset_in_bit, unsigned bit_count, unsigned value);
unsigned ReadBit(const void *ptr, unsigned offset_in_bit, unsigned bit_count);

} // memory
} // gs
