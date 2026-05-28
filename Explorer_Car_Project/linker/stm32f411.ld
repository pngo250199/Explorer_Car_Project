/* STM32F411 linker script for Explorer_Car project */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* True top of RAM — ARM SP loads this value at reset */
_estack = ORIGIN(RAM) + LENGTH(RAM);   /* = 0x20020000 */

ENTRY(Reset_Handler)

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.glue_7) *(.glue_7t)
        . = ALIGN(4);
    } > FLASH

    _etext  = .;
    _sidata = LOADADDR(.data);    /* moved here — before .data */

    .data : AT(_etext)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
        _ebss = .;
    } > RAM

    /* Heap only — stack lives at top of RAM naturally */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        _sheap = .;
        . = . + 0x2000;         /* 8KB heap */
        _eheap = .;
        end = .;
        PROVIDE(end = .);
        . = ALIGN(8);
    } > RAM

    _sidata     = LOADADDR(.data);
    _end        = end;

    /DISCARD/ :
    {
        *(.note.GNU-stack)
        *(.gnu_debuglink)
        *(.gnu.lto_*)
    }
}

PROVIDE(__StackTop   = _estack);
PROVIDE(__HeapBase   = _sheap);
PROVIDE(__HeapLimit  = _eheap);
PROVIDE(__DataStart  = _sdata);
PROVIDE(__DataEnd    = _edata);
PROVIDE(__BSSStart   = __bss_start__);
PROVIDE(__BSSEnd     = __bss_end__);