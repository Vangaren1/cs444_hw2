#include <cpu.h>
#include "tsystm.h"

void k_init(void);

/* k_init() initializes kernel routine */
void k_init()
{
	cli();

	ioinit();

	//call main here
	

	sti();
}
