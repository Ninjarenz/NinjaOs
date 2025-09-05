#include "vga.h"

static volatile uint16_t* const VGA = (uint16_t*)0xB8000;
static size_t row = 0, col = 0;
static const uint8_t color = 0x0F; // Weiß auf Schwarz

void putc(char c) {
    if (c == '\n') { row++; col = 0; return; }
    VGA[row * 80 + col] = ((uint16_t)color << 8) | (uint8_t)c;
    if (++col >= 80) { col = 0; row++; }
}

void puts(const char* str) {
    while (*str) putc(*str++);
}
