/**
 * @file freemem.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * @ingroup memory_mgmt
 *
 * Frees a block of heap-allocated memory.
 *
 * @param memptr
 *      Pointer to memory block allocated with memget().
 *
 * @param nbytes
 *      Length of memory block, in bytes.  (Same value passed to memget().)
 *
 * @return
 *      ::OK on success; ::SYSERR on failure.  This function can only fail
 *      because of memory corruption or specifying an invalid memory block.
 */
syscall freemem(void *memptr, ulong nbytes)
{
    register struct memblock *block, *next, *prev;
    irqmask im;
    ulong top;

    /* make sure block is in heap */
    if ((0 == nbytes)
        || ((ulong)memptr < (ulong)memheap)
        || ((ulong)memptr > (ulong)platform.maxaddr))
    {
        return SYSERR;
    }

    block = (struct memblock *)memptr;
    nbytes = (ulong)roundmb(nbytes);

    im = disable();

	/* TODO:
     *      - Determine correct freelist to return to
     *        based on block address
     *      - Acquire memory lock (memlock) //DONE
     *      - Find where the memory block should 
     *        go back onto the freelist (based on address) //DONE
     *      - Find top of previous memblock
     *      - Make sure block is not overlapping on prev or next blocks
     *      - Coalesce (combine) with previous block if adjacent
     *      - Coalesce (combine) with next block if adjacent
     */
    int i;
    uint cpuid;
    for(i = 0; i < NCORES; i++){
        if((ulong)memptr >= freelist[i].base && (ulong)memptr <= freelist[i].base + freelist[i].bound)
        {
            cpuid = i;
        }
    }
    lock_acquire(freelist[cpuid].memlock);
    prev = (memblk *) &freelist[cpuid];
    next = freelist[cpuid].head;

    while( next != NULL && next < block)
    {
        prev = next;
        next = next->next;
    }
        if((ulong)block < ((ulong)prev + prev->length))
        {
            lock_release(freelist[cpuid].memlock);
            restore(im);
            return SYSERR;
        }
        else if(((ulong)memptr + nbytes) > (ulong)next)
        {
            lock_release(freelist[cpuid].memlock);
            restore(im);
            return SYSERR;
        }
    
        else if((ulong)block > ((ulong)prev + prev->length) && ((ulong)block + nbytes) < (ulong)next)
        {
            prev->next = block;
            block->next = next; //DO I NEED THIS
            block->length = nbytes;
            lock_release(freelist[cpuid].memlock);
            restore(im);
            return OK;
        }
        else if((ulong)block == ((ulong)prev + prev->length) && ((ulong)block + nbytes) < (ulong)next)
        {
            prev->length = prev->length + block->length;
           // prev->next = block->next; //No need this line
            lock_release(freelist[cpuid].memlock);
            restore(im);
            return OK;
        }
        else if((ulong)block > ((ulong)prev + prev->length) && ((ulong)block + nbytes) == ((ulong)next))
        {
            block->length = next->length + block->length;
            prev->next = block; 
            block->next = next->next; 
            lock_release(freelist[cpuid].memlock);
            restore(im);
            return OK;
        }
        else if((ulong)block == ((ulong)prev + prev->length) && ((ulong)block + nbytes) == (ulong)next)
        {
            prev->length = prev->length + block->length + next->length;
            prev->next = next->next;
            lock_release(freelist[cpuid].memlock);
            restore(im);
            return OK;

        }
        // else if(memptr < (memblk *)((ulong)prev + prev->length))
        // {
        //     lock_release(freelist[cpuid].memlock);
        //     restore(im);
        //     return SYSERR;
        // }
        // else if(((ulong)memptr + nbytes) > (memblk *)((ulong)next))
        // {
        //     lock_release(freelist[cpuid].memlock);
        //     restore(im);
        //     return SYSERR;
        // }
      
    


	restore(im);
    return OK;
}
