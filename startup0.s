# asm startup file
# very first module in load
.globl _finale
.text

	movl $0x3ffff0, %esp   # set user program stack
	call _startupc         # call C startup, which calls user main

_finale: int $3                 # return to Tutor
