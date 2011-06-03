#include "common.h"

// lfsr113_Bits
uint32 randu32()
{
  static uint32 z1 = 1234567,
                z2 = 3219231,
                z3 = 9182319,
                z4 = 9127938;
  uint32 b;
  b  = ((z1 << 6) ^ z1) >> 13;
  z1 = ((z1 & 4294967294U) << 18) ^ b;
  b  = ((z2 << 2) ^ z2) >> 27; 
  z2 = ((z2 & 4294967288U) << 2) ^ b;
  b  = ((z3 << 13) ^ z3) >> 21;
  z3 = ((z3 & 4294967280U) << 7) ^ b;
  b  = ((z4 << 3) ^ z4) >> 12;
  z4 = ((z4 & 4294967168U) << 13) ^ b;
  return z1 ^ z2 ^ z3 ^ z4;
}

uint32 randu32_limit(uint32 upper)
{
  return randu32() % upper;
}

uint32 randu32_range(uint32 lower, uint32 upper)
{
  return lower + randu32() % upper;
}
