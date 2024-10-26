.extern main
.extern trap_vector

.section .entry
.global _start

_start:
  csrr t0, mhartid
  bnez t0, park

	la gp, _stack_bottom
	csrw satp, zero
  la sp, _stack_top

  la t0, _bss_start
  la t1, _bss_end
  bge t0, t1, init_done

clear_bss:
  sd zero, 0(t0)
  addi t0, t0, 8
  blt t0, t1, clear_bss

init_done:
  la t0, trap_vector
  csrw mtvec, t0

  csrsi mstatus, 0x8

  call main

park:
  wfi
  j park

