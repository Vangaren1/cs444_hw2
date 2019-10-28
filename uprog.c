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

    //call write here

    got = write(ldev, "hi!\n", 4);
    kprintf("write of 4 returned %d\n",got);
    
    // call read here

    kprintf("\nType 10 chars input to test typeahead while looping for delay...\n");
    delay();
    got = read(ldev, buf, 10);  /* should wait for all 10 chars, once fixed */
    kprintf("\nGot %d chars into buf.\n", got);


    return 0;
}

void delay()
{
  int i;

  kprintf("\n Delay is hapenning\n");

  for (i = 0; i < DELAYLOOPCOUNT; i++)
    ;
}
