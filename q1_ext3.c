#include <assert.h>
#include <ctype.h>
#include <immintrin.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)
#define time_cost \
    end_t.tv_sec * 1e9 + end_t.tv_nsec - start_t.tv_sec * 1e9 - start_t.tv_nsec

bool is_ascii_noIntrinsics(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if ((payload & PACKED_BYTE(0x80)) == 0) {
            uint64_t A = payload + PACKED_BYTE(128 - 'A' + 0);
            uint64_t Z = payload + PACKED_BYTE(128 - 'Z' - 1);
            uint64_t a = payload + PACKED_BYTE(128 - 'a' + 0);
            uint64_t z = payload + PACKED_BYTE(128 - 'z' - 1);
            uint64_t punctuation_marks_1 = payload + PACKED_BYTE(128 - ' ' + 0);
            uint64_t punctuation_marks_2 =
                payload + PACKED_BYTE(128 - '\"' - 1);
            uint64_t punctuation_marks_3 = payload + PACKED_BYTE(128 - ',' + 0);
            uint64_t punctuation_marks_4 = payload + PACKED_BYTE(128 - ',' - 1);
            uint64_t punctuation_marks_5 = payload + PACKED_BYTE(128 - '.' + 0);
            uint64_t punctuation_marks_6 = payload + PACKED_BYTE(128 - '.' - 1);
            uint64_t punctuation_marks_7 = payload + PACKED_BYTE(128 - ':' + 0);
            uint64_t punctuation_marks_8 = payload + PACKED_BYTE(128 - ';' - 1);
            uint64_t punctuation_marks_9 =
                payload + PACKED_BYTE(128 - '\'' + 0);
            uint64_t punctuation_marks_10 =
                payload + PACKED_BYTE(128 - '\'' - 1);
            uint64_t punctuation_marks_11 =
                payload + PACKED_BYTE(128 - '?' + 0);
            uint64_t punctuation_marks_12 =
                payload + PACKED_BYTE(128 - '?' - 1);
            uint64_t punctuation_marks_13 =
                payload + PACKED_BYTE(128 - '\0' + 0);
            uint64_t punctuation_marks_14 =
                payload + PACKED_BYTE(128 - '\0' - 1);
            if (((A ^ Z ^ a ^ z ^ punctuation_marks_1 ^ punctuation_marks_2 ^
                  punctuation_marks_3 ^ punctuation_marks_4 ^
                  punctuation_marks_5 ^ punctuation_marks_6 ^
                  punctuation_marks_7 ^ punctuation_marks_8 ^
                  punctuation_marks_9 ^ punctuation_marks_10 ^
                  punctuation_marks_11 ^ punctuation_marks_12 ^
                  punctuation_marks_13 ^ punctuation_marks_14) &
                 PACKED_BYTE(0x80)) != PACKED_BYTE(0x80))
                return false;
        } else {
            return false;
        }

        i += 8;
    }
    while (i < size) {
        if (!((0x41 <= str[i] && str[i] <= 0x5A) ||
              (0x61 <= str[i] && str[i] <= 0x7A) || str[i] == ' ' ||
              str[i] == '\"' || str[i] == ',' || str[i] == '.' ||
              str[i] == ':' || str[i] == ';' || str[i] == '\'' ||
              str[i] == '?' || str[i] == '\0'))
            return false;
        i++;
    }
    return true;
}

bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;

    const char str2[] = "azAZ \",,..:;''??";
    __m128i ranges = _mm_loadu_si128((const __m128i *) str2);
    for (int i = 0; i < size - 1; i += 16) {
        __m128i target = _mm_loadu_si128((const __m128i *) (str + i));
        if (_mm_cmpistrc(ranges, target,
                         _SIDD_UBYTE_OPS | _SIDD_CMP_RANGES |
                             _SIDD_MASKED_NEGATIVE_POLARITY | _SIDD_UNIT_MASK))
            return false;
    }
    return true;
}

int main()
{
    /*    print out CPU info
        int infotype, a, b, c, d;
        for (infotype = 0; infotype < 5; infotype++) {
          __asm__("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "0"(infotype));
          printf("InfoType %x\nEAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", infotype,
       a, b, c, d);
        }

        infotype = 7;
        c = 0;
        __asm__("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "0"(infotype),
        "2"(c)); printf("InfoType %x\nEAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n",
        infotype, a, b, c, d);
    */

    struct timespec start_t, end_t;
    FILE *fp;
    fp = fopen("q1_ext3_output.txt", "w");
    assert(fp);
    // char str[] = "I'm a dog, a pretty dog. Her cat is cute.";
    char str[] =
        "This eBook is for the use of anyone anywhere at no cost and with \
almost no restrictions whatsoever.  You may copy it, give it away or \
reuse it under the terms of the Project Gutenberg License included \
with this eBook or online at www.gutenberg.net";
    for (int i = 0; i < 46340; ++i) {
        long long int output_t;
        fprintf(fp, "%3d ", i);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
        assert(is_ascii(str, sizeof(str)));
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);
        output_t = time_cost;
        fprintf(fp, "%3lld ", output_t);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
        assert(is_ascii_noIntrinsics(str, sizeof(str)));
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);
        output_t = time_cost;
        fprintf(fp, "%3lld \n", output_t);
    }
    fclose(fp);
    return 0;
}
