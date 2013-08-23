MEMORY
{
   rom(RX)   : ORIGIN = 0x00000000, LENGTH = 0x8000
   ram(WAIL) : ORIGIN = 0x10000000, LENGTH = 0x2000
}

ENTRY(public_function)

SECTIONS
{
  .text : { *(.text) } > rom
  _data_start = .;
  .data : { *(.data) } > ram AT> rom
  _data_end = .;
  .bss  : { *(.bss) }  > ram
  _bss_end = .;
}
