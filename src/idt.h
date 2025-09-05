#pragma once
#include <stdint.h>

// Eintrag der IDT
struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed, aligned(16)));

// IDT Pointer
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init(void);

// Dummy-Handler für Keyboard
void keyboard_handler(void);
extern void keyboard_handler_stub(void);
