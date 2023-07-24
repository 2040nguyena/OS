/**
 * @file recv.c
 * @provides recv.
 *
 * $Id: receive.c 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * recv - wait for a mesage and return it
 * @return message
 */

message recv(void)
{
	register pcb *ppcb;
	int senderpid = -1;
	message msg;
	ppcb = &proctab[currpid[getcpuid()]];
	
	/* TODO:
 	* - Remember to acquire lock and release lock when interacitng with the msg structure
 	* - Check for Message. If no message, put in blocking state and reschedule
 	*   			If there is message, retrive message
 	* - Now, check queue for wating send processes,
 	*   If stuff in queue  collect message for next time recv is called and ready send process
 	*   else, reset message flag
 	*   return collected message
 	*/	
	lock_acquire(ppcb->msg_var.core_com_lock);
	if(ppcb->msg_var.hasMessage == FALSE)
	{
		msg = ppcb->msg_var.msgin;
		//return msg;
		ppcb->state = PRRECV;
		lock_release(ppcb->msg_var.core_com_lock);
		resched();
		lock_acquire(ppcb->msg_var.core_com_lock);
	}
	msg = ppcb->msg_var.msgin;
		
	if(!isempty(ppcb->msg_var.msgqueue))
	{
		senderpid = dequeue(ppcb->msg_var.msgqueue);
		ppcb->msg_var.msgin = proctab[senderpid].msg_var.msgout;
		//msg = ppcb->msg_var.msgout; //Do I need this?????
		proctab[senderpid].msg_var.msgout = EMPTY;
		lock_release(ppcb->msg_var.core_com_lock);
		ready(senderpid, RESCHED_NO, proctab[senderpid].core_affinity);
		return msg;
	}
	else
	{
		ppcb->msg_var.hasMessage = FALSE;
		lock_release(ppcb->msg_var.core_com_lock);
		return msg;
	}

	return msg;
}
