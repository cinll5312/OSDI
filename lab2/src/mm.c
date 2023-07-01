#include "mm.h"



void mm_init(){
    base = _brk;
    for(int i = 0; i < MALLOC_SIZE; i++){
        mm_info[i] = 0;
    }
}


void *simple_malloc(int size){
    if(size>MALLOC_SIZE)return (char*)0;

    for(int i = _brk-base; i < size;i++){
        mm_info[i] = 1;
    }

    char* temp = (char*)&_brk;
    _brk += size;

    return (void*)temp;
}