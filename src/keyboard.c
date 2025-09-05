#include "keyboard.h"

void keyboard_init(void) {
    // für später
}

void keyboard_handler_stub(void) {
    __asm__ __volatile__("movb $0x20, %al; outb %al, $0x20");
}

