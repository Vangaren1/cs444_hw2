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
    // got = write(ldev, "hi!\n", 4);
    // kprintf("Write of 4 returned %d\n", got);
    // kprintf("Debugging a longer write\n", got);
    // write(ldev, "abcdefghi", 9);
    // kprintf("Write of 9 returned, doing delay...\n", got);
    // debug_log("^^^^^^^^^^^^");         /* delay process beginned */
    // delay();
    // debug_log("vvvvvvvvvvvv");        /* delay process ended */

    // for (i = 0; i < 80; i++)
    //   buf[i] = 'A' + i/2;

    // kprintf("\n Trying write of buf...\n");
    // write(ldev, buf, 80);
    // kprintf("\n write of 80 done\n");
    // debug_log("^^^^^^^^^^^^");
    // delay();
    // debug_log("vvvvvvvvvvvv");

    // kprintf("\n Trying read...\n");
    // read(ldev, buf, 10);
    // kprintf("\n Returned from read, trying write of buf...\n");
    // write(ldev, buf, 10);

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
