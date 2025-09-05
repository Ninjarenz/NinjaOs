OS_NAME = ninja_os
ISO_NAME = ninja_os.iso

SRC = src
BUILD = build

CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32 -fno-pic -fno-pie -fno-stack-protector
ASMFLAGS = -f elf32

all: iso

$(BUILD):
	make clean
	mkdir -p $(BUILD)

$(BUILD)/boot.o: $(SRC)/boot.s | $(BUILD)
	nasm $(ASMFLAGS) $< -o $@

$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	clang $(CFLAGS) -c $< -o $@

kernel.elf: $(BUILD)/boot.o $(BUILD)/idt.o $(BUILD)/keyboard.o $(BUILD)/vga.o $(BUILD)/kernel.o
	ld -m elf_i386 -T linker.ld -nostdlib $^ -o $@

iso: kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "NINJA_OS" { multiboot /boot/kernel.elf }' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_NAME) iso

run: iso
	qemu-system-i386 -cdrom $(ISO_NAME)

clean:
	rm -rf $(BUILD) *.elf iso $(ISO_NAME)
	clear
