/**
 * @file testcases.c
 * @provides testcases
 *
 *
 * Modified by:	
 *
 * TA-BOT:MAILTO 
 *
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <xinu.h>

void printpid(int times)
{
    int i = 0;
    uint cpuid = getcpuid();

    enable();
    for (i = 0; i < times; i++)
    {
        kprintf("This is process %d\r\n", currpid[cpuid]);
        udelay(1);
    }
}

void printpidHigh(int times)
{
    int i = 0;
    uint cpuid = getcpuid();

    enable();
    for (i = 0; i < times; i++)
    {
        kprintf("This is process from high queue %d\r\n", currpid[cpuid]);
        udelay(1);
    }
}

void printpidMed(int times)
{
    int i = 0;
    uint cpuid = getcpuid();

    enable();
    for (i = 0; i < times; i++)
    {
        kprintf("This is process from medium queue %d\r\n", currpid[cpuid]);
        udelay(1);
    }
}

void printpidLow(int times)
{
    int i = 0;
    uint cpuid = getcpuid();

    enable();
    for (i = 0; i < times; i++)
    {
        kprintf("This is process from low queue %d\r\n", currpid[cpuid]);
        udelay(1);
    }
}

/**
 * testcases - called after initialization completes to test things.
 */
void testcases(void)
{
    uchar c;

    kprintf("===TEST BEGIN===\r\n");
    kprintf("0) Test priority scheduling\r\n");
    kprintf("\'A\') Aging / Starvation testcase\r\n");
    kprintf("\'P\') Preemption testcase\r\n");

    // TODO: Test your operating system!

    c = kgetc();
    switch (c)
    {
    case '0':
        // Run 3 processes with varying priorities
        ready(create
              ((void *)printpid, INITSTK, PRIORITY_HIGH, "PRINTER-A", 1,
               5), RESCHED_NO, 0);
        ready(create
              ((void *)printpid, INITSTK, PRIORITY_MED, "PRINTER-B", 1,
               5), RESCHED_NO, 0);
        ready(create
              ((void *)printpid, INITSTK, PRIORITY_LOW, "PRINTER-C", 1,
               5), RESCHED_YES, 0);

        break;

    case 'a':
    case 'A':
#if AGING
        // AGING TESTCASE
        kprintf("AGING is enabled.\r\n");

        // TODO: Create a testcase that demonstrates aging 
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-A", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-B", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-C", 1,
               20), RESCHED_YES, 0);

        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-D", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-E", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-F", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-G", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidMed, INITSTK, PRIORITY_MED, "PRINTER-H", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidLow, INITSTK, PRIORITY_LOW, "PRINTER-I", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_MED, "PRINTER-J", 1,
               20), RESCHED_YES, 0);
        ready(create
              ((void *)printpidLow, INITSTK, PRIORITY_LOW, "PRINTER-K", 1,
               20), RESCHED_YES, 0);
       

#else
        // STARVING TESTCASE
        kprintf("\r\nAGING is not currently enabled.\r\n");

        // TODO: Create a testcase that demonstrates starvation
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-A", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-B", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-C", 1,
               5), RESCHED_YES, 0);

        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-D", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-E", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-F", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-G", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidMed, INITSTK, PRIORITY_MED, "PRINTER-H", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidLow, INITSTK, PRIORITY_LOW, "PRINTER-I", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_MED, "PRINTER-J", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidLow, INITSTK, PRIORITY_LOW, "PRINTER-K", 1,
               5), RESCHED_YES, 0);
       



#endif
        break;

    case 'p':
    case 'P':
#if PREEMPT
        // PREEMPTION TESTCASE
        kprintf("\r\nPreemption is enabled.\r\n");

        // TODO: Create a testcase that demonstrates preemption
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-A", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-B", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-C", 1,
               5), RESCHED_YES, 0);

        ready(create
              ((void *)printpidHigh, INITSTK, PRIORITY_HIGH, "PRINTER-D", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidMed, INITSTK, PRIORITY_MED, "PRINTER-E", 1,
               5), RESCHED_YES, 0);
        ready(create
              ((void *)printpidLow, INITSTK, PRIORITY_LOW, "PRINTER-F", 1,
               5), RESCHED_YES, 0);

#else
        kprintf("\r\nPreemption is not currently enabled...\r\n");
#endif
        break;

    default:
        break;
    }

    kprintf("\r\n===TEST END===\r\n");
    return;
}
