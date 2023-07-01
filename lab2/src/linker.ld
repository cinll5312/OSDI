SECTIONS
{
    . = 0x80000;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    
    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }
 
    __bss_start = .;
    .bss :
    {
        *(.bss)
    }
    __bss_end = .;

    _brk = __bss_end + 0x10000;
   
}
__bootloader_ = 0x60000;