# Mark Thompson
# hw2 
# file: cst0.s

# modified from $pclibsrc/startup0.s

# init user stack
# call _main
# call _exit


movl $0x3ffff0, %esp
movl $0, %ebp
call _main
call _exit
int $3
