#include <stdint.h>
#include <stdio.h>
const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))

uint32_t quickmod(uint32_t n) {
  uint64_t quotient = ((__uint128_t)M * n) >> 64;
  return n - quotient * D;
}

int main() {
  uint32_t tt = 4294967295;
  printf("%u\n", quickmod(55));
  uint64_t test = 0xFFFFFFFFFFFFFFFF;
  printf("%lx\n%lx\n%lx %lx\n", test, test / D,
         (uint64_t)(((__uint128_t)tt * (test / D + 1)) >> 64),
         tt * (test / D + 1));
  printf("================\n%lx\n%lx\n%lx %lx\n", test, test / D,
         (uint64_t)(((__uint128_t)tt * (test / D)) >> 64), tt * (test / D));

  printf("================\n%lx %lx\n%lx\n",
         (uint64_t)(((__uint128_t)((__uint128_t)test + D) / D) >> 64),
         (uint64_t)((__uint128_t)((__uint128_t)test + D) / D), M);

  return 0;
}
