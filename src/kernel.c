#include "vga.h"
#include "idt.h"
#include "keyboard.h"

void kmain(void) {
    vga_print("NINJA_OS booted!\n");
    idt_init();
    keyboard_init();
    vga_print("Keyboard ready. Type something:\n");

    for (;;) {
        __asm__ __volatile__("hlt");
    }
}
