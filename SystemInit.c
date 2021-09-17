#include <stdint.h>
#include "timers/systick/systick.h"
#include "drivers/led/led.h"
#include "drivers/uart/uart.h"
#include "bootloader/bootloader.h"
#include "SystemInit.h"

void SystemInit(void)
{
    init_systick();
    init_uart();
    init_led();

    long *bootloaderSource = (long *)&__bootloader_copy;
    long *bootloaderDestination = (long *)&__sbootloader_copy;
    long *bootloaderEnd = (long *)&__ebootloader_copy;

    if (bootloaderSource != bootloaderDestination)
        while (bootloaderDestination < bootloaderEnd)
            *(bootloaderDestination++) = *(bootloaderSource++);

    Bootloader_init();
}