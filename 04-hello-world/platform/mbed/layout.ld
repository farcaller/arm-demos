_stack_base = 0x10008000;
_boot_checksum = 0 - (_stack_base + main + 1 + (hang + 1) * 5);

ENTRY(main)

MEMORY
{
    rom(RX)   : ORIGIN = 0x00000000, LENGTH = 0x80000
    ram(WAIL) : ORIGIN = 0x10000000, LENGTH = 0x8000
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
    } > rom
}
