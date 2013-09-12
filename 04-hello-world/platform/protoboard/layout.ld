_stack_base = 0x10002000;
_boot_checksum = 0 - (_stack_base + main + 1 + isr_nmi + 1 + isr_hardfault + 1);

ENTRY(main)

MEMORY
{
    rom(RX)   : ORIGIN = 0x00000000, LENGTH = 0x8000
    ram(WAIL) : ORIGIN = 0x10000000, LENGTH = 0x2000
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        KEEP(*(.isr_vector_nvic))
        *(.text*)
    } > rom
}
