.global activate
activate:
    msr psp, r0
    push {r0-r7, lr}

    /* Use process stack pointer */
    mrs r1, control
    add r1, #2
    msr control, r1

    ldr r2, [r0]
    movs pc, r2
    pop {r0-r7, pc}

.global yield
yield:
    push {r0-r7, lr}

    /* Use main stack pointer */
    mrs r0, control
    sub r0, #2
    msr control, r0

    pop {r0-r7, pc}
