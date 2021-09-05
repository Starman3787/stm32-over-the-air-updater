#ifndef SYSTEMINIT_H_
#define SYSTEMINIT_H_

void SystemInit(void);

extern char __bootloader_copy;
extern char __sbootloader_copy;
extern char __ebootloader_copy;

#endif