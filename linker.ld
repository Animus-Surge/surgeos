/*
 * SurgeOS kernel linker script
 */

/* ELF */
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

/* Set entry label */
ENTRY(_boot)

LOAD_OFFSET = 0;

/* Kernel physical address */
PHYS_BASE = 0x100000;

SECTIONS
{
  . = PHYS_BASE + SIZEOF_HEADERS;
  . = ALIGN(4K);


  .text : AT(ADDR(.text) - LOAD_OFFSET)
  {
    KEEP(*(.multiboot))
    *(.text)
    *(.text.*)
  }

  .rodata : AT(ADDR(.rodata) - LOAD_OFFSET)
  {
    . = ALIGN(4K);
    *(.rodata)
  }

  .data : AT(ADDR(.data) - LOAD_OFFSET)
  {
    . = ALIGN(4K);
    *(.data)
  }

  .bss : AT(ADDR(.bss) - LOAD_OFFSET)
  {
    . = ALIGN(4K);
    *(COMMON)
    *(.bss)
  }

  /* Kernel end */
  . = ALIGN(4K);
  _end = .;
  __end = .;
}
