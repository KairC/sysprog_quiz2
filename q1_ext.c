#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <=
           size) {  // check 8 bytes (64-bits) at a time, if the rest of
                    // bytes are smaller than 8 bytes, end while-loop.
                    //   uint64_t payload;
        //   memcpy(&payload, str + i, 8); // copy 8 bytes (64-bits) from str
        uint64_t *payload = (uint64_t *) str;
        if (*payload & 0x8080808080808080)
            return false;
        i += 8;  // previous 8 bytes (64-bits) have been checked, so move to the
                 // address which is next to the previous 8 bytes.
    }
    while (i < size) {  // because the rest of bytes are insufficient to 8
                        // bytes, check 1 bytes at a time.
        if (str[i] & 0x80)
            return false;
        i++;
    }

    return true;
}
int main()
{
    char str[] = "I'm a dog.";
    // char str[] = "I'm a dog. μ";
    assert(is_ascii(str, sizeof(str)));

    return 0;
}
