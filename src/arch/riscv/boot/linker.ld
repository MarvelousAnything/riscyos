OUTPUT_ARCH(riscv)
ENTRY(_start)


SECTIONS {
  . = 0x80000000;

  .text : {
    *(.entry)
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    PROVIDE(_bss_start = .);
    *(.bss*)
    *(COMMON)
    . = ALIGN(8);
    PROVIDE(_bss_end = .);
  }

  . = ALIGN(16);
  PROVIDE(_stack_top = .);         /* Define the top of the stack */
  . += 16K;                        /* Allocate 16KB for the stack */
  PROVIDE(_stack_bottom = .);      /* Define the bottom of the stack */

  _end = .;
}
