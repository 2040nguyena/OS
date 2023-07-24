/**
 * @file testcases.c
 * @provides testcases
 *
 * $Id: testcases.c 175 2008-01-30 01:18:27Z brylow $
 *
 * Modified by:
 *
 * and
 *
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <xinu.h>

devcall putc(int dev, char c) { return 0; }


/**
 * testcases - called after initialization completes to test things.
 */
void testcases(void)
{
    int c;

    kprintf("===TEST BEGIN===\r\n");

    c = kgetc();
    switch (c)
    {

    case 'a':
    kprintf("kputc test\r\n");
    kputc(c);
    break;

    case 'b':
    kprintf("kungetc and kgetc test\r\n");
    kungetc(c);
    c = kgetc();
    kprintf("\n%c",c);
   // kputc(kgetc());
    break;

    case 'c':
    kprintf("kungetc and kcheckc test\r\n");
    kungetc(c);
    if(kcheckc()){
        kprintf("there is something in here\r\n");
    }
    else{
        kprintf("there's nothing in here\r\n");
    }

     //TODO: Test your operating system!

    default:
	kprintf("Hello Xinu World!\r\n");
    }


    kprintf("\r\n===TEST END===\r\n");
    return;
}
