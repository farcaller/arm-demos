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
    .text : ALIGN(4)
    {
        FILL(0xff)

        KEEP(*(.isr_vector))
        KEEP(*(.isr_vector_nvic))

        . = ALIGN(4);
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data)) ;
        LONG(  SIZEOF(.data));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        __bss_section_table_end = .;
        __section_table_end = . ;
    } > rom

    .text : ALIGN(4)
    {
        *(.text*)
        *(.rodata .rodata.*)
        . = ALIGN(4);

    } > rom

    .data : ALIGN(4)
    {
        FILL(0xff)
        _data = . ;
        *(vtable)
        *(.data*)
        . = ALIGN(4) ;
        _edata = . ;
    } > ram AT>rom

    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > ram
}
