.global activate
activate:
    ldr r1, [r0]
    msr psp, r1
    push {r0-r7, lr}

    ldr r1, =task_delete
    mov lr, r1

    /* Use process stack pointer */
    mrs r1, control
    add r1, #2
    msr control, r1

    pop {r0-r7, pc}

.global yield
yield:
    push {r0-r7, lr}

    /* Use main stack pointer */
    mrs r0, control
    sub r0, #2
    msr control, r0

    pop {r0}
    mrs r1, psp
    str r1, [r0]
    pop {r1-r7, pc}

.global exit
exit:
    /* Use main stack pointer */
    mrs r0, control
    sub r0, #2
    msr control, r0

    pop {r0-r7, pc}
