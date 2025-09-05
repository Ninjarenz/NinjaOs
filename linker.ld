/* ==========================================
   NINJA_OS linker script
   - Multiboot-kompatibel
   - Kernel lädt bei 1MB
   ========================================== */

ENTRY(_start)

SECTIONS
{
    /* Startadresse des Kernels bei 1 MB */
    . = 1M;

    /* Multiboot Header + Text */
    .multiboot ALIGN(4) :
    {
        *(.multiboot)
    }

    .text ALIGN(4) :
    {
        *(.text)       /* alle Text-Segmente aus allen .o */
        *(.text.*)
    }

    .rodata ALIGN(4) :
    {
        *(.rodata)
        *(.rodata.*)
    }

    .data ALIGN(4) :
    {
        *(.data)
        *(.data.*)
    }

    .bss ALIGN(4) :
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
}
