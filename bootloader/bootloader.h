#ifndef BOOTLOADER_BOOTLOADER_H_
#define BOOTLOADER_BOOTLOADER_H_

void Bootloader_init(void) __attribute__ ((section(".bootloader")));
extern uint64_t tock __attribute__ ((section(".bootloader")));

#endif