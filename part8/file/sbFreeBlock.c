/* sbFreeBlock.c - sbFreeBlock */
/* Copyright (C) 2008, Marquette University.  All rights reserved. */
/*                                                                 */
/* Modified by                                                     */
/*                                                                 */
/* and                                                             */
/*                                                                 */
/*                                                                 */

/**
 * COSC 3250 - Project 10
 * Explain briefly the functionality of the program.
 * @authors Justin Nguyen David Santiago
 * Instructor Sabirat Rubya
 * TA-BOT:MAILTO ducan.nguyen@marquette.edu david.santiago@marquette.edu
 */

#include <kernel.h>
#include <device.h>
#include <memory.h>
#include <disk.h>
#include <file.h>

devcall swizzle(int diskfd, struct freeblock *freeblk){

    // TODO: Temporarily replace any pointers on the freeblock
    //   with the disk block number of the struct the pointer is referencing. 
    //   Then, seek to the freeblock disk block number and write to the disk.
    //   Remember to reset the pointers to there original memory address before returning.

    struct freeblock *free2 = freeblk->fr_next; //copy the data

    //if free2 is null
    //  set freeblock's fr_next to 0
    //else
    //  set freeblock's fr_next to be freeblock's fr_next's blockname
    // 
    if(free2 == NULL)
    {
        freeblk->fr_next = 0;
    }
    else
    {
        freeblk->fr_next = (struct freeblock *)freeblk->fr_next->fr_blocknum;
    }

    seek(diskfd, freeblk->fr_blocknum);
    if(SYSERR == write(diskfd, freeblk, sizeof(struct freeblock))) {   //write(where, what, length)
        return SYSERR;
    }
    //reset the freeblock's fr_next to its copy
    freeblk->fr_next = free2;
    return OK;
}

devcall swizzleSuperBlock(int diskfd, struct superblock *psuper){

    // TODO: Temporarily replace any pointers on the superblock
    //   with the disk block number of the struct the pointer is referencing. 
    //   Then, seek to the superblock disk block number and write to the disk.
    //   Remember to reset the pointers to there original memory address before returning.

    struct freeblock *swizzle = psuper->sb_freelst;
    struct dirblock *swizzle2 = psuper->sb_dirlst;

    //overwrite sb_freelist to be freelist's blocknum
    //overwrite sb_dirlist to be sb_dirlist's blocknum
    //

    psuper->sb_freelst = (struct freeblock *)swizzle->fr_blocknum;
    psuper->sb_dirlst = (struct dirblock *)swizzle2->db_blocknum;

    seek(diskfd, psuper->sb_blocknum);
    if(SYSERR == write(diskfd, psuper, sizeof(struct superblock)))
    {
        return SYSERR;
    }
    //revert copies
    psuper->sb_freelst = swizzle;
    psuper->sb_dirlst = swizzle2;
    return OK;
}

/*------------------------------------------------------------------------
 * sbFreeBlock - Add a block back into the free list of disk blocks.
 *------------------------------------------------------------------------
 */
devcall sbFreeBlock(struct superblock *psuper, int block)
{
    // TODO: Add the block back into the filesystem's list of
    //  free blocks.  Use the superblock's locks to guarantee
    //  mutually exclusive access to the free list, and write
    //  the changed free list segment(s) back to disk.

    int diskfd;
    struct dentry *phw;

    //error check if superblock is null
    //
    if(psuper == NULL)
    {
        return SYSERR;
    }

    phw = psuper->sb_disk; //found in file.h

    //errorcheck != null
    if(phw == NULL)
    {
        return SYSERR;
    }
    //
    //errorcheck block we got as a param (! <= 0 && !> total blocks on disk)
    //
    if(block <= 0 || block > 256)
    {
        return SYSERR;
    }
    diskfd = phw - devtab;
    //wait 
    //
    wait(psuper->sb_freelock);
    //first collector node
    struct freeblock *freeblk = psuper->sb_freelst;

    //CASE1: if the disk is completely full
    //  free up 1 block, make it a collector node
    //
    //while loop to get to the last collector node
    //  freeblock fr_next
    //
    if(freeblk == NULL)
    {
        freeblk = (struct freeblock *)malloc(sizeof(struct freeblock));
        freeblk->fr_blocknum = block; 
        freeblk->fr_count = 0;
        psuper->sb_freelst=freeblk; //set the block that we just freed to be the only collector node
        //freeblk->fr_count = 0;
        freeblk->fr_next = NULL;

        if(SYSERR == swizzleSuperBlock(diskfd, psuper))
        {
            signal(psuper->sb_freelock);
            return SYSERR;
        };
        if(SYSERR == swizzle(diskfd, freeblk))
        {
            signal(psuper->sb_freelock);
            return SYSERR;
        };

        signal(psuper->sb_freelock);
        return OK;
    }
    else 
    {
        while(freeblk->fr_next != NULL)
        {
            freeblk = freeblk->fr_next;
        }
        //CASE3: Find the last collector node just to find that it is full (in terms of having enough available blocks), 
    //       so create a new collector node, DONE 
    //       add the block to that node, 
    //then link that collector node to previous collector node. DONE
        if(freeblk->fr_count == 61) 
        {
            //Create a new collector node and connect it with the previous one
            struct freeblock *freeblk2 = (struct freeblock *)malloc(sizeof(struct freeblock));
            freeblk2->fr_blocknum = block;
            freeblk2->fr_count = 0;
            freeblk2->fr_next = NULL;
            freeblk->fr_next = freeblk2;

            
            if(SYSERR == swizzle(diskfd, freeblk2))
            {
                signal(psuper->sb_freelock);
                return SYSERR;
            };
            signal(psuper->sb_freelock);
            return OK;
    
        }
        //CASE2: Find the last colletor node and add the block to the last collector 
        freeblk->fr_free[freeblk->fr_count] = block;
        freeblk->fr_count++;
        if(SYSERR == swizzle(diskfd, freeblk))
        {
            signal(psuper->sb_freelock);
            return SYSERR;
        };
        signal(psuper->sb_freelock);
        return OK;
    }
    return SYSERR;
}
