#include "convert_endian.h"
#include <stdio.h>


int main(void) {
  uint16_t val16 = 0xAABB;
  uint32_t val32 = 0xAABBCCDD;
  uint64_t val64 = 0x1122334455667788ULL;

  printf("16-bit: 0x%04X -> 0x%04X\n", val16,
         (uint16_t)convert_endian(val16, sizeof(val16)));

  printf("32-bit: 0x%08X -> 0x%08X\n", val32,
         (uint32_t)convert_endian(val32, sizeof(val32)));

  printf("64-bit: 0x%016llX -> 0x%016llX\n", (unsigned long long)val64,
         (unsigned long long)convert_endian(val64, sizeof(val64)));

  return 0;
}
