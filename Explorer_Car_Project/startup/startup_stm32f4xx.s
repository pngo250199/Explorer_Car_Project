/**
 * STM32F411 Startup Code
 * Minimal startup for bare-metal development
 */

.syntax unified
.cpu cortex-m4
.thumb

.global Reset_Handler
.global _estack

/* Vector Table */
.section .isr_vector,"a",%progbits
.align 2

ISR_Vector:
    .word _estack                  /* Initial stack pointer */
    .word Reset_Handler            /* Reset handler */
    .word Default_Handler          /* NMI handler */
    .word Default_Handler          /* Hard fault handler */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* SVCall handler */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* Reserved */
    .word Default_Handler          /* PendSV handler */
    .word Default_Handler          /* SysTick handler */

.section .text,"ax",%progbits
.thumb_func
.type Reset_Handler, %function
.globl Reset_Handler

Reset_Handler:
    /* Copy initialized data from FLASH to RAM */
    movw r0, #:lower16:_sdata
    movt r0, #:upper16:_sdata
    movw r1, #:lower16:_edata
    movt r1, #:upper16:_edata
    movw r2, #:lower16:_sidata
    movt r2, #:upper16:_sidata
    
    cmp r0, r1
    beq zero_bss

copy_loop:
    ldr r3, [r2], #4
    str r3, [r0], #4
    cmp r0, r1
    bne copy_loop

    /* Zero out uninitialized data (BSS) */
zero_bss:
    movw r0, #:lower16:__bss_start__
    movt r0, #:upper16:__bss_start__
    movw r1, #:lower16:__bss_end__
    movt r1, #:upper16:__bss_end__
    
    cmp r0, r1
    beq call_main
    
    movs r2, #0

zero_loop:
    str r2, [r0], #4
    cmp r0, r1
    bne zero_loop

call_main:
    /* Call main */
    bl main
    
    /* Infinite loop if main returns */
    b .

.thumb_func
.type Default_Handler, %function
.weak Default_Handler
.globl Default_Handler

Default_Handler:
    b Default_Handler

.end


