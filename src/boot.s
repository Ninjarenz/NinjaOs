[BITS 32]
section .multiboot
    align 4
    dd 0x1BADB002        ; magic
    dd 0x00010003        ; flags
    dd -(0x1BADB002 + 0x00010003) ; checksum

extern kmain
global _start

section .text
_start:
    call kmain
    cli
.hang:
    hlt
    jmp .hang
