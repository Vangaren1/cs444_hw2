#include <cpu.h>
#include "tsystm.h"
#include "tsyscall.h"

extern IntHandler syscall /* the assembler envelope routine    */

void kprintf(char *, ...);
void debug_set_trap_gate(int n, const IntHandler *inthand_addr, int debug);
void set_trap_gate(int n, IntHandler *inthand_addr);
void syscallc(int user_eax, int devcode, char *buff, int bufflen)

void k_init(void);

/* k_init() initializes kernel routine */
void k_init()
{
	cli();

	ioinit();

	set_trap_gate(0x80, &syscall);

	//call main here
	main();

	sti();
}

/* Rename the arguments */
void syscallc(int user_eax, int devcode, char *buff, int bufflen)
{
	int nargs;
  	int syscall_no = user_eax;

	switch(nargs = sysent[syscall_no].sy_narg)
	{
		case 1: // system exit
			user_eax = nargs = sysent[syscall_no].sy_call(devcode);
			break;

		case 3: // sys call write and read
			user_eax = nargs = sysent[syscall_no].sy_call(devcode, buff, bufflen);

			break;
		default:
			kprintf("bad syscall argument %d, syscall #%d\n", nargs, syscall_no);
	}

}


// modified from set_intr_gate in $pclibsrc/cpu.c

/* non-debug version */
void set_trap_gate(int n, const IntHandler *inthand_addr)
{
  debug_set_trap_gate(n, inthand_addr, 0);
}

/* write the nth idt descriptor as an interrupt gate to inthand_addr */
void debug_set_trap_gate(int n, const IntHandler *inthand_addr, int debug)
{
	char *idt_addr;            
	Gate_descriptor *idt, *desc;
	unsigned int limit = 0;

	if (debug)
	printf("Calling locate_idt to do sidt instruction...\n");
	locate_idt(&limit,&idt_addr);

	idt = (Gate_descriptor *)idt_addr - KERNEL_BASE_LA; 

	if (debug)
	printf("Found idt at %x, lim %x\n",idt, limit);
	desc = &idt[n];               /* select nth descriptor in idt table */

	/* fill in descriptor */
	if (debug)
	printf("Filling in desc at %x with addr %x\n",(unsigned int)desc,
	       (unsigned int)inthand_addr);
	desc->selector = KERNEL_CS;   /* CS seg selector for int. handler */
	desc->addr_hi = ((unsigned int)inthand_addr)>>16; /* CS seg offset of inthand  */
	desc->addr_lo = ((unsigned int)inthand_addr)&0xffff;
	desc->flags = GATE_P|GATE_DPL_KERNEL|GATE_TRAPGATE;/* valid, interrupt */
	desc->zero = 0;
}
