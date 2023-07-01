TOOLCHAIN_PREFIX = aarch64-linux-gnu-
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
OBJCPY = $(TOOLCHAIN_PREFIX)objcopy

SRC_DIR = src
OUT_DIR = out


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
LINKER_FILE = $(SRC_DIR)/linker.ld
ENTRY_OBJS = $(OUT_DIR)/start.o
ENTRY = $(SRC_DIR)/start.s

CFLAGS = -Wall  -fno-stack-protector -ffreestanding -nostdlib -Iinclude
LIB = -Iinclude 
#
.PHONY: all clean asm run debug directories 

all: directories kernel8.img

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(ENTRY_OBJS): $(ENTRY)
	$(CC) $(CFLAGS) -c $< -o $@




kernel8.img: $(OBJS) $(ENTRY_OBJS)
	$(LD) $(ENTRY_OBJS) $(OBJS) -T $(LINKER_FILE) -o kernel8.elf
	$(OBJCPY) -O binary kernel8.elf kernel8.img

asm:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -d in_asm

run: all
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -serial null -serial stdio -initrd b.cpio -dtb bcm2710-rpi-3-b-plus.dtb

debug: all
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -S -s 

raspi:
	sudo screen /dev/ttyUSB0 115200
tty:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial pty

cpio:
	cd rootfs;find . | cpio -o -H newc > ../initramfs.cpio
py:
	sudo python3 loadimg.py

directories: $(OUT_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -f out/* kernel8.*