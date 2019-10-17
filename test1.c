#include <stdio.h>
#include "io_public.h"

#define BUFLEN 80

int main(void)
{
	char buf[BUFLEN];
  	int got, i, lib_console_dev, ldev;

  	/* Determine the SAPC's "console" device, the serial port for user i/o */
  	lib_console_dev = sys_get_console_dev();  /* SAPC support lib fn */
 	switch(lib_console_dev) {
  	case COM1: ldev = TTY0;	/* convert to our dev #'s */
    	break;
  	case COM2: ldev = TTY1;
    	break;
  	default: printf("Unknown console device\n");
    	return 1;
  	}

	kprintf("Running with device TTY%d\n",ldev);
	/* Now have a usable device to talk to with i/o package-- */

    ioinit();  /* Initialize devices */
  	kprintf("\nTrying simple write(4 chars)...\n");
  	got = write(ldev,"hi!\n",4);
  	kprintf("write of 4 returned %d\n",got);
	//delay();  /* time for output to finish, once write-behind is working */

	kprintf("Trying longer write (9 chars)\n");
	got = write(ldev, "abcdefghi", 9);
	kprintf("write of 9 returned %d\n",got);
	//delay();  /* time for output to finish, once write-behind is working */

	for (i = 0; i < BUFLEN; i++)
	    buf[i] = 'A'+ i/2;
	kprintf("\nTrying write of %d-char string...\n", BUFLEN);
	got = write(ldev, buf, BUFLEN);
  	kprintf("\nwrite returned %d\n", got);
  	//delay();

  	kprintf("\nType 10 chars input to test typeahead while looping for delay...\n");
  	//delay();
  	got = read(ldev, buf, 10);	/* should wait for all 10 chars, once fixed */
  	kprintf("\nGot %d chars into buf. Trying write of buf...\n", got);
  	write(ldev, buf, got);

  	kprintf("\nTrying another 10 chars read right away...\n");
  	got = read(ldev, buf, 10);	/* should wait for input, once fixed */
  	kprintf("\nGot %d chars on second read\n",got);
  	if (got == 0) 
    	kprintf("nothing in buffer\n");	/* expected result until fixed */
  	else 
    	write(ldev, buf, got);	/* should write 10 chars once fixed */

  	return 0;
}
