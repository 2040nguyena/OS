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

// void printFreelist()
// {     
//       uint cpuid = getcpuid();
//       register struct memblock *curr;
//       curr = freelist[cpuid].head;

//       while(curr != NULL)
//       {
            
//             kprintf("\naddress: %d", curr);
//             kprintf(" length: %d", curr->length);
//             kprintf(" address of next: %d\n", curr->next);
//             curr = curr->next;
//       }
// }
int apid;
int testpid, testpid1, testpid2, testpid3;
void receiveMsg(void)
{
      int msg = recv();
      kprintf("The message is %d", msg);
}

void receiveMultipleMsg()
{
      message msg = recv();
      kprintf("The message is %d\r\n", msg);
      msg = recv();
      kprintf("The message is %d\r\n", msg);
      msg = recv();
      kprintf("The message is %d\r\n", msg);
}

void killtest(int pid, int core)
{
      ready(create((void *)kill, INITSTK,PRIORITY_HIGH, "KILL",1, pid), RESCHED_YES, core);
      kill(pid);
      //kill(currpid[getcpuid()]);
}


void testcases(void)
{
    uchar c;

    kprintf("===TEST BEGIN===\r\n");
    kprintf("0) Test recv and send using helper function\r\n");
    kprintf("1) Test send and recv\r\n");
    kprintf("2) Test sendnow and recv now\r\n");
    kprintf("3) Test multiple messages\r\n");

    

    // TODO: Test your operating system!

    c = kgetc();
      switch (c)
      {
      case '0':
            testpid = create((void *) receiveMsg, INITSTK, PRIORITY_LOW, "RECV", 0);
            apid = 0;
            pcb *ppcb = &proctab[apid];
            ppcb->core_affinity = 0;
            syscall result = sendnow(0, 5);
            kprintf("Result: %d\r\n", result);
            if((TRUE == ppcb->msg_var.hasMessage) && (5 == ppcb->msg_var.msgin))
                  kprintf("Message corectly sent.\r\n");
            else
                  kprintf("Recv process hasMessage == %d, msgin = %d\r\n", 
                          ppcb->msg_var.hasMessage, ppcb->msg_var.msgin);
            kill(0);

      case '1':
            testpid = create((void *)send, INITSTK, PRIORITY_HIGH, "PRINTER-A", 2,
               currpid[getcpuid()],2);
            ready(testpid, RESCHED_YES, 0);
            message msg1 = recv();

            kprintf("Message corectly sent: %d\r\n", msg1);
            killtest(testpid,0);
            break;
      
      case '2':
            testpid = create
              ((void *)sendnow, INITSTK, PRIORITY_HIGH, "PRINTER-A", 2,
               currpid[getcpuid()],3);
            ready(testpid, RESCHED_YES, 0);

               message msg2 = recvnow();

               kprintf("Message corectly sent: %d\r\n", msg2);
               killtest(testpid, 0);
            break;
      
      case '3':
            testpid1 = create
              ((void *)send, INITSTK, PRIORITY_HIGH, "PRINTER-A", 2,
               currpid[getcpuid()],2);
            testpid2 = create
              ((void *)send, INITSTK, PRIORITY_HIGH, "PRINTER-B", 2,
               currpid[getcpuid()],3);
            testpid3 = create
              ((void *)send, INITSTK, PRIORITY_HIGH, "PRINTER-C", 2,
               currpid[getcpuid()],4);
            ready(testpid1,RESCHED_YES,0);
            ready(testpid2,RESCHED_YES,1);
            ready(testpid3, RESCHED_YES,2);

            receiveMultipleMsg();
            killtest(testpid1, 0);
            killtest(testpid2, 1);
            killtest(testpid3, 2);

      default:
            break;
      }
      kprintf("\r\n===TEST END===\r\n");
      return;
}