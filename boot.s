/* #define ASM 1 */
/* #include "multiboot.h" */

# Declare constants used for creating a multiboot header.
.set ALIGN,     1<<0             # align loaded modules on page boundaries
.set MEMINFO,   1<<1             # provide memory map
.set VIDINFO,   1<<2             # provide video info
.set FLAGS,     ALIGN | MEMINFO | VIDINFO  # this is the Multiboot 'flag' field
.set MAGIC,     0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM,  -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot
.set MODE_TYPE, 0
.set WIDTH,     640
.set HEIGHT,    480
.set DEPTH,     0
.set STACK_SIZE, 0x4000

        .text

        .globl  start, _start
start:
_start:
        jmp     multiboot_entry

        /* Align 32 bits boundary. */
        .align  4

multiboot_header:
        .long   MAGIC
        .long   FLAGS
        .long   CHECKSUM
        .long   0, 0, 0, 0, 0
        .long   MODE_TYPE
        .long   WIDTH
        .long   HEIGHT
        .long   DEPTH

multiboot_entry:
        /* Initialize the stack pointer. */
        movl    $(stack + STACK_SIZE), %esp

        /* Reset EFLAGS. */
        pushl   $0
        popf

        /* Push the pointer to the Multiboot information structure. */
        pushl   %ebx
        /* Push the magic value. */
        pushl   %eax

        /* Now enter the C main function... */
        call    loader

        /* Halt. */
        // TODO: add back?
        /*pushl   $halt_message
        call    EXT_C(kprintf)*/

loop:   hlt
        jmp     loop

halt_message:
        .asciz  "Halted."

        /* Our stack area. */
        .comm   stack, STACK_SIZE
