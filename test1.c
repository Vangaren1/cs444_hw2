#include <stdio.h>
#include "io_public.h"
#include "tty_public.h"

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

  	/* Kernel handle this part */
    /* Write */
    kprintf("Debugging a simple write...\n");
    got = write(ldev, "hi!\n", 4);
    kprintf("write of 4 returned %d\n", got);
    kprintf("trying longer write\n");
    write(ldev, "abcdefghi", 9);
    kprintf("write of 9 returned, doing delay...\n",got);

    /* Looping */
    debug_log("...");  
    delay();
    debug_log("...");  

    for (i = 0; i < 80; i++)
        buf[i] = 'A'+ i/2;
    kprintf("\nTrying write of buf...\n");
    write(ldev, buf, 80);
    kprintf("\nwrite of 80 done\n");

    /* Looping */
    debug_log("...");
    delay();
    debug_log("...");

    /* Read */
    kprintf("\nTrying read...\n");
    read(ldev, buf, 10);
    kprintf("\nReturned from read, trying write of buf...\n");
    write(ldev, buf, 10);

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
