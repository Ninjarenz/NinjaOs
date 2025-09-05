#include "idt.h"
#include "keyboard.h"
#include "vga.h"   // <- hinzufügen
#include <stdint.h>

void kmain(void) {
    puts("NINJA_OS v0.3\n");
    puts("Keyboard demo: Type something!\n");

    idt_init();
    puts("Boot Test...\n");

    while (1) { __asm__ __volatile__("hlt"); }
}
