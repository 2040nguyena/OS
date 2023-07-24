/**
 * @file send.c
 * @provides send
 *
 * $Id: send.c 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  Al rights resered. */

/**
 * COSC 3250 - Project 8
 * Explain briefly the functionality of the program.
 * @author David Santiago, Justin Nguyen
 * Instructor Sabirat Rubya
 * TA-BOT:MAILTO david.santiago@marquette.edu, ducan.nguyen@marquette.edu
 */

#include <xinu.h>

/**
 * Send a message to another thread
 * @param pid proc id of recipient
 * @param msg contents of message
 * @return OK on sucess, SYSERR on failure
 */
syscall send(int pid, message msg)
{
	register pcb *spcb;
	register pcb *rpcb;
	
	/*TODO:
 	* - PID Error checking
 	* - Acquire receving process lock (remember to release when appropriate!
 	* - Retrieving Process Error Checking
 	* - If receiving process has message, block sending process and put msg in msgout and call resched
 	* - Else, deposit message, change message flag and, if receiving process is blocking, ready it.
 	* - return ok.
 	*/
 	rpcb = &proctab[pid];
	spcb = &proctab[currpid[getcpuid()]]; //initializing rpcb and spcb
	lock_acquire(rpcb->msg_var.core_com_lock);

	//ERROR checking
	if(isbadpid(pid))
	{
		lock_release(rpcb->msg_var.core_com_lock);
		return SYSERR;
	}
	if(rpcb->state == PRFREE)
	{
		lock_release(rpcb->msg_var.core_com_lock);
		return SYSERR;
	}

	if(rpcb->msg_var.hasMessage == TRUE)
	{
		spcb->state = PRSEND; //block
		spcb->msg_var.msgout = msg;
		enqueue(currpid[getcpuid()], rpcb->msg_var.msgqueue);
		lock_release(rpcb->msg_var.core_com_lock);
		resched();
		return OK;
	}
	else
	{
		rpcb->msg_var.msgin = msg; //deposit message
		rpcb->msg_var.hasMessage = TRUE; //Change the message flag
		if(rpcb->state = PRRECV)
		{
			lock_release(rpcb->msg_var.core_com_lock);
			ready(pid, RESCHED_YES, rpcb->core_affinity);
			return OK;
		}
		else
		{
			lock_release(rpcb->msg_var.core_com_lock);
			return OK;
		}
		
	}
	return OK;
}
