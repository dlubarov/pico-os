#define ASM     1
#include "multiboot.h"

        .text

        .globl  start, _start
start:
_start:
        jmp     multiboot_entry

        /* Align 32 bits boundary. */
        .align  4

        /* Multiboot header. */
multiboot_header:
        /* magic */
        .long   MULTIBOOT_HEADER_MAGIC
        /* flags */
        .long   MULTIBOOT_HEADER_FLAGS
        /* checksum */
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#ifndef __ELF__
        /* header_addr */
        .long   multiboot_header
        /* load_addr */
        .long   _start
        /* load_end_addr */
        .long   _edata
        /* bss_end_addr */
        .long   _end
        /* entry_addr */
        .long   multiboot_entry
#endif /* ! __ELF__ */

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
        call    EXT_C(loader)

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
