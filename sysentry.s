# Mark Thompson
# Homework 2
# File: sysentry.s


.globl _syscallc, _syscall
.text

_syscall:   pushl %edx        # push the values of eax to edx to stack
            pushl %ecx
            pushl %ebx
            pushl %eax
            call _syscallc    # call c trap routine in tunix.c
            addl $4, %esp     # value of %eax
            popl %ebx         # pop the values of ebx to edx from stack
            popl %ecx
            popl %edx
            iret
