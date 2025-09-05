#include <stdint.h>

volatile uint16_t* VGA = (uint16_t*)0xB8000;

void vga_print(const char* str) {
    static int row = 0, col = 0;
    while(*str) {
        VGA[row * 80 + col] = (0x0F << 8) | *str;
        col++;
        if(col >= 80) { col = 0; row++; }
        str++;
    }
}
