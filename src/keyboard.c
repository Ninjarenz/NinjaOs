#include <stdint.h>
#include <stddef.h>  // <- für size_t
#include "keyboard.h"


// VGA-Output
static volatile uint16_t* const VGA = (uint16_t*)0xB8000;
static size_t row = 10, col = 0;

static void putc(char c) {
    VGA[row * 80 + col] = ((uint16_t)0x0F << 8) | c;
    if (++col >= 80) { col = 0; row++; }
}

// Simple scancode-to-ASCII (nur Buchstaben A-Z)
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

// IRQ1 handler (called from ASM stub)
void keyboard_handler(void) {
    uint8_t scancode;
    __asm__ __volatile__("inb $0x60, %0" : "=a"(scancode));

    char c = scancode_to_ascii(scancode);
    if (c) putc(c);

    // Send EOI
    __asm__ __volatile__("movb $0x20, %al; outb %al, $0x20");
}
