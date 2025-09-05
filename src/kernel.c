#include "vga.h"

void kmain(void) {
    vga_print("NINJA_OS booted!\n");
    for(;;); // Endlosschleife
}
