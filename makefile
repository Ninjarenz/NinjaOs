AS      = nasm
CC      = clang
LD      = ld

CFLAGS  = -ffreestanding -O2 -Wall -Wextra -target i686-elf -m32 -fno-pic -fno-pie -fno-stack-protector
LDFLAGS = -T linker.ld -nostdlib -m elf_i386

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o) build/boot.o


all: kernel.elf

# Boot-Assembly
build/boot.o: src/boot.s
	mkdir -p build
	$(AS) -felf32 $< -o $@

# C-Dateien
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Linken
kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

# ISO erzeugen
iso: kernel.elf grub.cfg
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o ninja_os.iso iso

# Emulator starten
run: iso
	qemu-system-i386 -cdrom ninja_os.iso
	

# Aufräumen
clean:
	rm -rf build *.o *.elf iso ninja_os.iso
	clear
