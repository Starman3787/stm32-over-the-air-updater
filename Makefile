TARGET = main

# Define the linker script location and chip architecture
LD_SCRIPT	= link/stm32h7a3zi.ld
MCU_SPEC	= cortex-m7

# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN	= /usr
CC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc
AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
OC = $(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OD = $(TOOLCHAIN)/bin/arm-none-eabi-objdump
OS = $(TOOLCHAIN)/bin/arm-none-eabi-size

# Assembly directives
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -g
# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs
CFLAGS += -DSTM32H7A3xx
CFLAGS += -Wno-main
CFLAGS += -Wno-unused-variable

# Linker directives.
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += -Wextra
LFLAGS += -Werror
LFLAGS += --specs=nosys.specs
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)

AS_SRC = ./startup.S
C_SRC = ./main.c
C_SRC += ./timers/systick/systick_interrupt_handler.c
C_SRC += ./timers/systick/systick.c
C_SRC += ./util/delay/delay.c
C_SRC += ./drivers/led/led.c
C_SRC += ./drivers/uart/uart.c
C_SRC += ./SystemInit.c
C_SRC += ./bootloader/bootloader.c

INCLUDE = -I./

OBJS = $(AS_SRC:.S=.o)
OBJS += $(C_SRC:.c=.o)

.PHONY: all
all: $(TARGET).bin

%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf 
	rm -f $(TARGET).bin 