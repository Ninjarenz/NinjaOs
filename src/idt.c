#include "idt.h"
#include "keyboard.h"

// 256 Einträge für die IDT
static struct idt_entry idt[256] __attribute__((aligned(16)));
static struct idt_ptr idtp;
extern void keyboard_handler(void);


// Interner Helfer zum Setzen eines IDT-Eintrags
static void set_idt_entry(int n, uint32_t handler_addr) {
    idt[n].offset_low  = handler_addr & 0xFFFF;
    idt[n].selector    = 0x08;       // Kernel Code Segment
    idt[n].zero        = 0;
    idt[n].type_attr   = 0x8E;       // Present, Ring0, Interrupt Gate
    idt[n].offset_high = (handler_addr >> 16) & 0xFFFF;
}

// Inline-Assembly für LIDT
static inline void lidt(struct idt_ptr* idtp) {
    __asm__ __volatile__("lidt (%0)" : : "r"(idtp));
}

// Dummy Keyboard Handler (nur für Boot-Test)
void keyboard_handler(void) {
    // EOI an PIC
    __asm__ __volatile__("movb $0x20, %al; outb %al, $0x20");
}

// IDT initialisieren
void idt_init(void) {
    // IDT Pointer füllen
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    // Alle Einträge auf 0 setzen
    for (int i = 0; i < 256; i++) {
        idt[i].offset_low  = 0;
        idt[i].offset_high = 0;
        idt[i].selector    = 0;
        idt[i].zero        = 0;
        idt[i].type_attr   = 0;
    }

    // IRQ1 = Keyboard (nur Dummy Stub)
    set_idt_entry(0x21, (uint32_t)keyboard_handler_stub);

    // IDT laden
    lidt(&idtp);

    // PIC Remap (8259)
    __asm__ __volatile__(
        "movb $0x11, %%al; outb %%al, $0x20; outb %%al, $0xA0;"
        "movb $0x20, %%al; outb %%al, $0x21;"
        "movb $0x28, %%al; outb %%al, $0xA1;"
        "movb $0x04, %%al; outb %%al, $0x21;"
        "movb $0x02, %%al; outb %%al, $0xA1;"
        "movb $0x01, %%al; outb %%al, $0x21; outb %%al, $0xA1;"
        "movb $0x0,  %%al; outb %%al, $0x21; outb %%al, $0xA1;"
        :::"al"
    );

    // Interrupts noch NICHT aktivieren; sti erst im Kernel
}
