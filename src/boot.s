; ------------------------------------------------------------
; Bootloader / Multiboot Header
; ------------------------------------------------------------
section .multiboot
align 8

MB2_MAGIC   equ 0xE85250D6
MB2_ARCH    equ 0
MB2_LENGTH  equ header_end - header_start
MB2_CSUM    equ -(MB2_MAGIC + MB2_ARCH + MB2_LENGTH)

header_start:
    dd MB2_MAGIC
    dd MB2_ARCH
    dd MB2_LENGTH
    dd MB2_CSUM
    dw 0
    dw 0
    dd 8
header_end:

; ------------------------------------------------------------
; Textmodus Start + Stack
; ------------------------------------------------------------
section .text
global start
extern kmain
extern keyboard_handler
; extern idt_load     ; -> entfernen, wird nicht mehr benötigt
; extern keyboard_handler_stub  ; -> entfernen, global gleich definiert

start:
    cli                 ; Interrupts aus
    mov esp, 0x9FC00    ; Stack setzen (sicherer Bereich)
    call kmain          ; Kernel starten
.hang:
    hlt
    jmp .hang

; ------------------------------------------------------------
; IDT Load (inline stub, falls benötigt)
; ------------------------------------------------------------
; global idt_load    ; <- optional, nur wenn du es extern aufrufst
; idt_load:
;     mov eax, [esp+4]
;     lidt [eax]
;     ret

; ------------------------------------------------------------
; Keyboard Handler Stub
; ------------------------------------------------------------
global keyboard_handler_stub
keyboard_handler_stub:
    pusha               ; Alle Register sichern
    call keyboard_handler
    popa
    iretd               ; Return from IRQ
