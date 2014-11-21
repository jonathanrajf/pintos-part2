#include "vm/frame.h"
#include <stdio.h>
#include "vm/page.h"
#include "devices/timer.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/palloc.h"
#include "threads/synch.h"
#include "threads/vaddr.h"

/* Initialize the frame table and the frame table lock */
void frame_table_init (void) 
{
	list_init(&frame_table); //Initialise the frame table which is a list
	lock_init(&frame_table_lock); //Initialise the frame lock
 
}

/* Tries to allocate a frame. Panics the kernel if there are no more frames to allocate */

void frame_allocate(struct supp_ptable_entry *spte, enum palloc_flags *flag) 
{
	if((flags & PAL_USER)==0)
	{
		return NULL;
	}
	
	void *frame = palloc_get_page(flag);
	
	if(frame)
	{
		frame_add_to_table(*spte);
	}
	
	if(!frame)
	{
		PANIC("NO MORE FRAMES TO ALLOCATE");
	}
}

void frame_add_to_table(struct supp_ptable_entry *spte)
{
	struct frame_table_entry *fte = malloc(sizeof(struct frame_table_entry));
	
	//Allocate all the values for the page table entry
	fte->frame = frame;				
	fte->spte = spte;
	fte->thread = thread_current();
	
	//Push this entry at the back of the frame table
	lock_acquire(&frame_table_lock);
	list_push_back(&frame_table, fte->elem);
	lock_release(&frame_table_lock);
	
}
/* Locks P's frame into memory, if it has one.
   Upon return, p->frame will not change until P is unlocked. */
/*
void
frame_lock (struct page *p) 
{
}
*/

/* Releases frame F for use by another page.
   F must be locked for use by the current process.
   Any data in F is lost. */
/*
void
frame_free (struct frame *f)
{
}
*/

/* Unlocks frame F, allowing it to be evicted.
   F must be locked for use by the current process. */
/*
void
frame_unlock (struct frame *f) 
{
}
*/
