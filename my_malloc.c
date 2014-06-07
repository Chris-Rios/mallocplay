#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
static char big_block[BLOCKSIZE];

/* return a pointer to the memory buffer requested*/
void* my_malloc(unsigned int size,char* file, int line)
{
	static int 		initialized = 0;
	static struct MemEntry *root;/*root for small half*/
	static struct MemEntry *broot;/*root for big half*/
	struct MemEntry *p;
	struct MemEntry *succ;
	if(size==0)
	{
		fprintf(stderr,"Error:malloc attempt of size 0 in:%s,line:%d\n",file,line);
		exit(EXIT_FAILURE);
	}
	
	if(!initialized)	/* 1st time called*/
	{
		// create a root chunk at the beginning of the memory block
		root = (struct MemEntry*)big_block;
		root->prev = root->succ = 0;
		root->size = BLOCKSIZE-2500 - sizeof(struct MemEntry);
		root->isfree = 1;
		initialized = 1;
		root->marker='i';/*marker for memory that I allocated*/ 
		broot = (struct MemEntry*)(big_block+2500);
		broot->prev = broot->succ = 0;
		broot->size = BLOCKSIZE -2500- sizeof(struct MemEntry);
		broot->isfree = 1;
		broot->marker='i';/*marker for memory that I allocated*/ 
	}
	
	if(size<300)
	{
		p = root;
	do
	{
		if(p->size < size)
		{
			// the current chunk is smaller, go to the next chunk
			p = p->succ;
		}
		else if(!p->isfree)
		{
			// this chunk was taken, go to the next
			p = p->succ;
		}
		else if(p->size < (size + sizeof(struct MemEntry)))
		{
			// this chunk is free and large enough to hold data, 
			// but there's not enough memory to hold the HEADER of the next chunk
			// don't create any more chunks after this one
			p->marker='i';
			p->isfree = 0;
			return (char*)p + sizeof(struct MemEntry);
		}
		else
		{
			// take the needed memory and create the header of the next chunk
			succ = (struct MemEntry*)((char*)p + sizeof(struct MemEntry) + size);
			succ->prev = p;
			succ->succ = p->succ;
			//begin add
			if(p->succ != 0)
				p->succ->prev = succ;
			p->succ = succ;
			//end add
			
			succ->size = p->size - sizeof(struct MemEntry) - size;
			succ->isfree=1;
			succ->marker='o';
			p->size = size;
			p->marker='i';
			p->isfree = 0;
			return (char*)p + sizeof(struct MemEntry);
		}
	} while(p != 0);
}
else
{
	p = broot;
		do
	{
		if(p->size < size)
		{
			// the current chunk is smaller, go to the next chunk
			p = p->succ;
		}
		else if(!p->isfree)
		{
			// this chunk was taken, go to the next
			p = p->succ;
		}
		else if(p->size < (size + sizeof(struct MemEntry)))
		{
			// this chunk is free and large enough to hold data, 
			// but there's not enough memory to hold the HEADER of the next chunk
			// don't create any more chunks after this one
			p->marker='i';
			p->isfree = 0;
			return (char*)p + sizeof(struct MemEntry);
		}
		else
		{
			// take the needed memory and create the header of the next chunk
			succ = (struct MemEntry*)((char*)p + sizeof(struct MemEntry) + size);
			succ->prev = p;
			succ->succ = p->succ;
			//begin add
			if(p->succ != 0)
				p->succ->prev = succ;
			p->succ = succ;
			//end add
			
			succ->size = p->size - sizeof(struct MemEntry) - size;
			succ->isfree=1;
			succ->marker='o';
			p->size = size;
			p->marker='i';
			p->isfree = 0;
			return (char*)p + sizeof(struct MemEntry);
		}
	} while(p != 0);
}
	fprintf(stderr,"Error:memory full in:%s,line:%d\n",file,line);
	exit(EXIT_FAILURE);
	return 0;
}


// free a memory buffer pointed to by p

void my_free(void *p,char* file, int line )
{
	
	int block_loc;
	int buff_loc;
	struct MemEntry *ptr;
	struct MemEntry *prev;
	struct MemEntry *succ;
	char* free_check =(char*)p;
	if(&big_block[0]>free_check||&big_block[BLOCKSIZE-1]<free_check)/*checks if the address of the pointer being freed is in the range of my memory*/
	{
		fprintf(stderr,"Error:pointer was never allocated by malloc:in: %s at line %d\n",file,line);
		exit(EXIT_FAILURE);
	}
	if(free_check[-8]!='i')/*checks for something being freed twice*/
	{
		fprintf(stderr,"Error: Pointer has already been freed or is not the correct pointer given from malloc in: %s LINE:%d\n",file,line);
		exit(EXIT_FAILURE);
	}
	ptr = (struct MemEntry*)((char*)p - sizeof(struct MemEntry));
	if((prev = ptr->prev) != 0 && prev->isfree)
	{
		// the previous chunk is free, so
		// merge this chunk with the previous chunk
		prev->size += sizeof(struct MemEntry) + ptr->size;
		//begin add
		ptr->isfree=1;
		ptr->marker ='o'; /*marker set to off position*/
		prev->succ = ptr->succ;
		if(ptr->succ != 0)
			ptr->succ->prev = prev;
		//end add
	}
	else
	{
		ptr->isfree = 1;
		ptr->marker ='o';
		prev = ptr;	// used for the step below
	}
	
	if((succ = ptr->succ) != 0 && succ->isfree)
	{
		// the next chunk is free, merge with it
		prev->size += sizeof(struct MemEntry) + succ->size;
		prev->isfree = 1;
		//begin add
		prev->succ = succ->succ;
		if(succ->succ != 0)
			succ->succ->prev=prev;
		//end add
	}
	p=NULL;
}
 
