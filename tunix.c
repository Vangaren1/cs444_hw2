#include <cpu.h>
#include "tsystm.h"
#include "tsyscall.h"

extern IntHandler syscall; /* the assembler envelope routine    */
extern void ustart(void), finale(void);

void kprintf(char *, ...);
void debug_set_trap_gate(int n, IntHandler *inthand_addr, int debug);
void set_trap_gate(int n, IntHandler *inthand_addr);
void syscallc(int user_eax, int devcode, char *buff, int bufflen);
int sysexit(int);
void shutdown(void);
void debug_log(char*msg);

#define MAXCALL = 6

/* system call dispatch table */
static  struct sysent {
       short   sy_narg;        			/* total number of arguments */
       int     (*sy_call)(int, ...);    /* handler */
} sysent[MAXCALL];

void k_init(void);

/* k_init() initializes kernel routine */
void k_init()
{
	cli();

	ioinit();

	set_trap_gate(0x80, &syscall);

	/* Calling system call */
	
	sysent[TREAD].sy_call = (int (*)(int, ...))sysread;
	sysent[TWRITE].sy_call = (int (*)(int, ...))syswrite;
	sysent[TEXIT].sy_call = (int (*)(int, ...))sysexit;
	
	/* set the argument number of each function from tsyscall.h */
	sysent[TEXIT].sy_narg = 1;    
	sysent[TREAD].sy_narg = 4;
	sysent[TIOCTL].sy_narg = 3;
	sysent[TWRITE].sy_narg = 3;

	//call main here
	main();

	sti();
	ustart();
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
void set_trap_gate(int n, IntHandler *inthand_addr)
{
  debug_set_trap_gate(n, inthand_addr, 0);
}

/* write the nth idt descriptor as an interrupt gate to inthand_addr */
void debug_set_trap_gate(int n, IntHandler *inthand_addr, int debug)
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

/* Exit system call function implementation */
int sysexit(int exit_code)
{ 
    kprintf("\n EXIT CODE IS %d\n", exit_code);
	shutdown();
	return 0;    
}

/* Program shutdown implementation */
void shutdown()
{
  kprintf("SHUTTING THE SYSTEM DOWN!\n");
  kprintf("Debug log from run:\n");
  kprintf("Marking kernel events as follows:\n");
  kprintf("  ^a   COM2 input interrupt, a received\n");
  kprintf("  ~    COM2 output interrupt, ordinary char output\n");
  kprintf("  ~e   COM2 output interrupt, echo output\n");
  kprintf("  ~s   COM2 output interrupt, shutdown TX ints\n");
  kprintf("%s", debug_log_area);	/* the debug log from memory */
  kprintf("\nLEAVE KERNEL!\n\n");
  finale();		/* trap to Tutor */
}

void debug_log(char*msg)
{
   strcpy(debug_record, msg);
   debug_record  +=strlen(msg);
}

