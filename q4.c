#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))

bool divisible(uint32_t n)
{
    return n * M <= M - 1;
}

uint32_t quickmod(uint32_t n)
{
    uint64_t quotient = ((__uint128_t) M * n) >> 64;
    return n - quotient * D;
}

int main()
{
    printf("D=3 , divisible(7) will get : %d\n", divisible(7));
    printf("D=3 , divisible(87) will get : %d\n", divisible(87));
    return 0;
}
