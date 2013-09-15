_stack_base = 0x10002000;
_boot_checksum = 0 - (_stack_base + main + 1 + isr_nmi + 1 + isr_hardfault + 1);

_data_load = LOADADDR(.data);

ENTRY(main)

MEMORY
{
    rom(RX)   : ORIGIN = 0x00000000, LENGTH = 0x8000
    ram(WAIL) : ORIGIN = 0x10000000, LENGTH = 0x2000
}

SECTIONS
{
    .text : ALIGN(4)
    {
        FILL(0xff)

        KEEP(*(.isr_vector))
        KEEP(*(.isr_vector_nvic))
    } > rom

    .text : ALIGN(4)
    {
        FILL(0xff)

        *(.text*)
        *(.rodata .rodata.*)
    } > rom

    .data : ALIGN(4)
    {
        FILL(0xff)
        _data = .;

        *(vtable)
        *(.data*)
        . = ALIGN(4);

        _edata = .;
    } > ram AT>rom

    .bss : ALIGN(4)
    {
        _bss = .;

        *(.bss*)
        *(COMMON)
        . = ALIGN(4);

        _ebss = .;
    } > ram
}
