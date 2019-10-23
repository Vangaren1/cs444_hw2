#include <stdio.h>
#include "io_public.h"

#define BUFLEN 80
#define MILLION 1000000
#define DELAYLOOPCOUNT (400 * MILLION)

extern void debug_log(char *msg);
void delay(void);

int main(void)
{
	  char buf[BUFLEN];
  	int got, i;
    int ldev = TTY1;

  	// Kernel handle this part
    kprintf("Debugging a simple write...\n");
    got = write(ldev, "hi!\n", 4);

  	return 0;
}

// void debug_log(char *msg)
// {
//   strcpy(debug_record, msg);
//   debug_record += strlen(msg);
// }

void delay()
{
  int i;

  kprintf("\n Delay is hapenning\n");

  for (i = 0; i < DELAYLOOPCOUNT; i++)
    ;
}
