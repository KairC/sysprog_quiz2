#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    long unsigned int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if ((payload & PACKED_BYTE(0x80)) == 0) {
            uint64_t A = payload + PACKED_BYTE(128 - 'A' + 0);
            uint64_t Z = payload + PACKED_BYTE(128 - 'Z' - 1);
            uint64_t a = payload + PACKED_BYTE(128 - 'a' + 0);
            uint64_t z = payload + PACKED_BYTE(128 - 'z' - 1);
            if (((A ^ Z ^ a ^ z) & PACKED_BYTE(0x80)) != PACKED_BYTE(0x00))
                return true;  // the string dose have at least one uppercase or
                              // lowercase
        }

        i += 8;
    }
    while (i < size) {
        if (((0x41 <= str[i] && str[i] <= 0x5A) ||
             (0x61 <= str[i] && str[i] <= 0x7A)))
            return true;  // it does have at least one uppercase or lowercase
        i++;
    }
    return false;
}

int main()
{
    char str[] = "What's updog.";
    char str2[] = "1231-+_@3=,.?!";
    assert(is_ascii(str, sizeof(str)));
    assert(is_ascii(str2, sizeof(str2)));
    return 0;
}
