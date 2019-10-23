#include <cpu.h>
#include "tsystm.h"

void k_init(void);

/* k_init() initializes kernel routine */
void k_init()
{
	cli();

	ioinit();

	desc->flags = GATE_P|GATE_DPL_KERNEL|GATE_TRAPGATE;
	//call main here
	main();

	sti();
}


void syscallc(int user_eax, int arg1, char* arg2, int arg3)
{
	user_eax = syswrite(arg1, arg2, arg3);
}