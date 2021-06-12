#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
uint32_t hexchar2val(const char in[]) {
  uint32_t val = 0;
  uint32_t range = strlen(in) - 2;
  for (uint32_t i = range - 1; i != -1; i--) {
    uint32_t payload = (uint32_t) * (in + i + 2);
    const uint32_t letter = payload & 0x00000040;
    const uint32_t shift = (letter >> 3) | (letter >> 6);
    payload = (payload + shift) & 0x0000000f;
    payload <<= 4 * (range - 1 - i);
    printf("%x\n", payload);
    val += payload;
  }
  printf("%x\n", val);
  return val;
}

int main()
{
  printf("%u\n", hexchar2val("0xFF"));
  return 0;
}

