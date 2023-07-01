#ifndef MM_H
#define MM_H

//end of our heap we could allocate
#define MALLOC_SIZE 0x2000
//top of our heap
extern volatile unsigned int _brk;
unsigned int base;



mm_info[MALLOC_SIZE];


void *simple_malloc(int size);
void mm_init();

#endif