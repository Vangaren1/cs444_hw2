#include <cpu.h>
#include "tsystm.h"

void k_init(void);

/* k_init() initialize kernel routine */
void k_init()
{
	cli();

	ioinit();

	sti();
}