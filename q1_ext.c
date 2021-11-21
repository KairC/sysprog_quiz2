#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str[] = "I'm a dog.";
    printf("str : %s\n", str);
    printf("str address : %p\n", str);

    // create a uint64_t pointer points to (uint64_t *)str
    uint64_t *payload_ = (uint64_t *) str;
    const char s[] = "She is a pig.";

    printf("payload_ in uint64_t : %lx\n", *payload_);
    printf("payload_ in string : %s\n", (char *) payload_);
    printf("payload_ address : %p\n", payload_);

    /*** use memcpy to copy 8 bytes string at one time.***/

    // memcpy(payload_, s, 8);

    /*** not use memcpy to copy 8 bytes string at one time.***/

    *payload_ = *((uint64_t *) s);

    /*** not use memcpy to copy 8 bytes string one by one.***/
    /*
    for (int i = 0; i < 8; i++) {
        *((char *) payload_ + i) = *(s + i);
    }
    */

    printf("payload_ in uint64_t after copy : %lx\n", *payload_);
    printf("payload_ in string after copy : %s\n", (char *) payload_);
    printf("payload_ address after copy : %p\n", payload_);

    return 0;
}
