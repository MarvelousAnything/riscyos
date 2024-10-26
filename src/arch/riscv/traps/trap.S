.section .text
.global trap_vector

trap_vector:
  addi sp, sp, -256          /* Make space on the stack */
  sd ra, 248(sp)             /* Save return address */
  sd sp, 240(sp)             /* Save stack pointer */
  sd gp, 232(sp)
  sd tp, 224(sp)
  sd t0, 216(sp)
  sd t1, 208(sp)
  sd t2, 200(sp)
  sd s0, 192(sp)
  sd s1, 184(sp)
  sd a0, 176(sp)
  sd a1, 168(sp)
  sd a2, 160(sp)
  sd a3, 152(sp)
  sd a4, 144(sp)
  sd a5, 136(sp)
  sd a6, 128(sp)
  sd a7, 120(sp)
  sd s2, 112(sp)
  sd s3, 104(sp)
  sd s4, 96(sp)
  sd s5, 88(sp)
  sd s6, 80(sp)
  sd s7, 72(sp)
  sd s8, 64(sp)
  sd s9, 56(sp)
  sd s10, 48(sp)
  sd s11, 40(sp)
  sd t3, 32(sp)
  sd t4, 24(sp)
  sd t5, 16(sp)
  sd t6, 8(sp)

  csrr t0, mcause
  li t1, 0xB
  beq t0, t1, handle_syscall

  /* Call the trap handler in C */
  call trap_handler

restore_context:
  ld ra, 248(sp)
  ld sp, 240(sp)
  ld gp, 232(sp)
  ld tp, 224(sp)
  ld t0, 216(sp)
  ld t1, 208(sp)
  ld t2, 200(sp)
  ld s0, 192(sp)
  ld s1, 184(sp)
  ld a0, 176(sp)
  ld a1, 168(sp)
  ld a2, 160(sp)
  ld a3, 152(sp)
  ld a4, 144(sp)
  ld a5, 136(sp)
  ld a6, 128(sp)
  ld a7, 120(sp)
  ld s2, 112(sp)
  ld s3, 104(sp)
  ld s4, 96(sp)
  ld s5, 88(sp)
  ld s6, 80(sp)
  ld s7, 72(sp)
  ld s8, 64(sp)
  ld s9, 56(sp)
  ld s10, 48(sp)
  ld s11, 40(sp)
  ld t3, 32(sp)
  ld t4, 24(sp)
  ld t5, 16(sp)
  ld t6, 8(sp)
  addi sp, sp, 256           /* Restore stack pointer */

  mret                        /* Return from trap */

handle_syscall:
  call syscall_handler
  j restore_context

  .size trap_vector, .-trap_vector
