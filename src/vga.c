#include "vga.h"

static volatile uint16_t* const VGA = (uint16_t*)0xB8000;
static size_t row = 10, col = 0;

void vga_putc(char c) {
    VGA[row * 80 + col] = ((uint16_t)0x0F << 8) | c;
    if (++col >= 80) { col = 0; row++; }
}

void vga_print(const char* str) {
    while (*str) {
        vga_putc(*str++);
    }
}
