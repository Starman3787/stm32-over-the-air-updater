#include <stdint.h>
#include "bootloader/bootloader.h"

void Bootloader_init(void)
{
    uint64_t tock = 0ULL;
    while (1)
        tock++;
}