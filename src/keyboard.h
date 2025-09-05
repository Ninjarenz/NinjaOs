#pragma once
#include <stdint.h>
#include <stddef.h>  // für size_t

// IRQ1 Handler, aufgerufen vom ASM-Stub
void keyboard_handler(void);
