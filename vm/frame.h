#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdbool.h>
#include "threads/synch.h"
#include "threads/palloc.h"

struct list frame_table; //Implementing frame table as a list 

struct lock frame_table_lock; //Lock for the frame table

//Structure of each frame table entry
struct frame_table_entry 
{
    struct *frame;					//A pointer to the frame in physical memory
    struct supp_ptable_entry *spte;  //A pointer to the supplementary page table which is currently using the frame
    struct thread *thread;  		//The thread which is using the frame
    struct list_elem elem;          //List element to traverse the frame table list

};

void frame_table_init (void);

void frame_allocate(struct supp_ptable_entry *spte, enum palloc_flags *flag);

void frame_add_to_table(struct supp_ptable_entry *spte);

void free_frame(struct *frame);

void evict_frame(enum palloc_flags *flag);

#endif /* vm/frame.h */
