.section ".text.boot"

.globl _start

_start:
    mrs x1, MPIDR_EL1
    and x1, x1, #0xFF
    cbz x1, _next
_loop:
    wfe
    b _loop

_next:
    // set stack top to the text section's head
    ldr x0, =_start
    mov sp,x0

    // initialize bss section
    ldr x0, =__bss_start
    ldr x1, =__bss_end
    sub x1, x1, x0
    cbz x1, _kernel
_zero:
    //clear to 0
    str xzr, [x0], #8 // [x0]<-0  x0 = x0 + 8
    sub x1, x1, #8
    cbnz x1, _zero

_kernel:
    bl loadkernel
    mov x9, 0x80000
    br x9
    bl _loop

