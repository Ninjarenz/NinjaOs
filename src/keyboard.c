#include <stdint.h>
#include "keyboard.h"
#include "vga.h"

// Scancode → ASCII map
static char scancode_to_ascii(uint8_t sc) {
    static char map[128] = {
        0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
        'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
        'z','x','c','v','b','n','m',',','.','/', 0, '*', 0,' ',
    };
    if (sc < 128) return map[sc];
    return 0;
}

void keyboard_handler(void) {
    uint8_t scancode;
    __asm__ __volatile__("inb $0x60, %0" : "=a"(scancode));

    char c = scancode_to_ascii(scancode);
    if (c) vga_putc(c);

    // EOI
    __asm__ __volatile__("movb $0x20, %al; outb %al, $0x20");
}

void keyboard_init(void) {
    // TODO: später PIC/IRQ einrichten
}
