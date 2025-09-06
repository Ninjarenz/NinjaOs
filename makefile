# =================================
# Makefile for NINJA_OS
# =================================

CC = clang
ASM = nasm
LD = ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32 -fno-pic -fno-pie -fno-stack-protector -I src
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC)) build/boot.o

ISO_DIR = iso
ISO_BOOT = $(ISO_DIR)/boot
GRUB_CFG = $(ISO_BOOT)/grub/grub.cfg

all: build/kernel.elf ninja_os.iso

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/boot.o: src/boot.s
	mkdir -p build
	$(ASM) $(ASFLAGS) $< -o $@

build/kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

ninja_os.iso: build/kernel.elf
	mkdir -p $(ISO_BOOT)/grub
	cp build/kernel.elf $(ISO_BOOT)/
	cp grub.cfg $(ISO_BOOT)/grub/
	grub-mkrescue -o ninja_os.iso $(ISO_DIR)

clean:
	rm -rf build *.elf iso ninja_os.iso

run: ninja_os.iso
	qemu-system-i386 -m 512M -cdrom ninja_os.iso -boot d -monitor stdio



