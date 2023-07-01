TOOLCHAIN_PREFIX = aarch64-linux-gnu-
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
OBJCPY = $(TOOLCHAIN_PREFIX)objcopy

CFLAGS = -Wall -g

.PHONY: all clean run

all: kernel8.img clean

lab0.o: lab0.s
	$(CC) $(CFLAGS) -c $< -o $@

kernel8.img: lab0.o
	$(LD) -T lab0.ld -o kernel8.elf $<
	$(OBJCPY) -O binary kernel8.elf $@

clean:
	rm -f *.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -d in_asm