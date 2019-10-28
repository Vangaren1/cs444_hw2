# Mark Thompson
# hw2 
# file: cst0.s

# modified from $pclibsrc/startup0.s

# init user stack
# call _main
# call _exit

.globl _ustart
.text
			
_ustart:	
		movl $0x3ffff0, %esp         #reinit the stack
		movl $0, %ebp                # and frame pointer
		call _main                   #call main in the uprog.c
        pushl %eax                   #push the retval=exit_code on stack
        call _exit                   # call sysycall exit