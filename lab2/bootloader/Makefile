TOOLCHAIN_PREFIX = aarch64-linux-gnu-
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
OBJCPY = $(TOOLCHAIN_PREFIX)objcopy

SRC_DIR = .
OUT_DIR = out


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
LINKER_FILE = $(SRC_DIR)/linker.ld
ENTRY_OBJS = $(OUT_DIR)/start.o
ENTRY = $(SRC_DIR)/start.s

CFLAGS = -Wall  -fno-stack-protector -ffreestanding -nostdlib -I../include
LIB = -I../include 
#
.PHONY: all clean asm run debug directories 

all: directories bootloader.img

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(ENTRY_OBJS): $(ENTRY)
	$(CC) $(CFLAGS) -c $< -o $@




bootloader.img: $(OBJS) $(ENTRY_OBJS)
	$(LD) $(ENTRY_OBJS) $(OBJS) -T $(LINKER_FILE) -o bootloader.elf
	$(OBJCPY) -O binary bootloader.elf bootloader.img

# asm:
# 	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -d in_asm

# run: all
# 	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -serial null -serial stdio

# debug: all
# 	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -S -s

raspi:
	sudo screen /dev/ttyUSB0 115200
tty:
	qemu-system-aarch64 -M raspi3 -kernel bootloader.img -serial null -serial pty

directories: $(OUT_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -f out/* bootloader.*