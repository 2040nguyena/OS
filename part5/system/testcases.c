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

void printFreelist()
{     
      uint cpuid = getcpuid();
      register struct memblock *curr;
      curr = freelist[cpuid].head;

      while(curr != NULL)
      {
            
            kprintf("\naddress: %d", curr);
            kprintf(" length: %d", curr->length);
            kprintf(" address of next: %d\n", curr->next);
            curr = curr->next;
      }
}

void testcases(void)
{
    uchar c;

    kprintf("===TEST BEGIN===\r\n");
    kprintf("0) Test printFreelist\r\n");

    // TODO: Test your operating system!

    c = kgetc();
      switch (c)
      {
      case '0':
            printFreelist();
            getmem(10000);
            printFreelist();
            break;
      case '1':
            printFreelist();
            getmem(10000);
            printFreelist();
            freemem(82800, 10000);
            printFreelist();
            break;
      default:
            break;
      }
      kprintf("\r\n===TEST END===\r\n");
      return;
}