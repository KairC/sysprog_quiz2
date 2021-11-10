#include <stdint.h>
#include <stdio.h>
const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))

uint32_t quickmod(uint32_t n)
{
    uint64_t quotient = ((__uint128_t) M * n) >> 64;
    return n - quotient * D;
}

int main()
{
    printf("D = 3 , quickmod(5) will get : %u\n", quickmod(5));
    printf("D = 3 , quickmod(55) will get : %u\n", quickmod(55));
    printf("D = 3 , quickmod(555) will get : %u\n", quickmod(555));
    return 0;
}
