MEMORY
{
   rom(RX)   : ORIGIN = 0x00000000, LENGTH = 0x8000
   ram(WAIL) : ORIGIN = 0x10000000, LENGTH = 0x2000
}

ENTRY(public_function)

SECTIONS
{
  .text : { *(.text) } > rom
  .data :
  {
    _data_start = .;
    *(.data)
    _data_end = .;
  } > ram AT> rom
  .bss :
  {
    *(.bss)
    _bss_end = .;
  }  > ram
}
