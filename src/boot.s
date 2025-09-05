; ====================================
; boot.s für NINJA_OS, Multiboot-kompatibel
; ====================================

[BITS 32]

; -------------------------
; Multiboot Header
; -------------------------
section .multiboot
    align 4
    dd 0x1BADB002        ; magic
    dd 0x00010003        ; flags
    dd -(0x1BADB002 + 0x00010003)  ; checksum

; -------------------------
; Kernel Start
; -------------------------
extern kmain

global _start
global keyboard_handler_stub

section .text
_start:
    call kmain
    cli

.hang:
    hlt
    jmp .hang

keyboard_handler_stub:
    iret

