#include "cpio.h"
#include "uart.h"
#include "utli.h"

void lsfile(char* buf){
    long addr = buf;
    char temp[BUF_LEN];
    int namesize;
    int filesize;
    while(1){
        cpio_t *head = (cpio_t*)addr;

        memcpy(head->c_namesize,temp,8);//filename size
        namesize = atoi(temp);
        // uart_puts("namesize : ");
        // print_num(namesize);

        memcpy(head->c_filesize,temp,8);//file content size
        filesize = atoi(temp);
        // uart_puts("filesize : ");
        // print_num(filesize);

        addr += sizeof(cpio_t);
    
        if(namesize==11){
            if(cmpstr((char*)addr,"TRAILER!!!",10))break;
        }

        char *s = addr;
        for(int i = 0 ; i < namesize-1; i++){
            uart_send(*s);
            s++;
        }
        uart_puts("\n\r");

        if(namesize>=2){//align
            if((namesize-2)%4==0){
                addr += namesize;
            }else{
                addr += namesize + (4-(namesize-2)%4);
            }
        }else{
            addr += 2;
        }

        if(filesize>0){
            if(filesize%4==0){
                addr += filesize;
            }  
            else{
                addr += filesize + 4 - (filesize%4);
            }

        }
    }
    
}

void catfile(char* buf, char* target){
    long addr = buf;
    char temp[BUF_LEN];
    int namesize;
    int filesize;
    int istarget = 0;

    while(1){
        cpio_t *head = (cpio_t*)addr;

        memcpy(head->c_namesize,temp,8);//filename size
        namesize = atoi(temp);

        memcpy(head->c_filesize,temp,8);//file content size
        filesize = atoi(temp);

        addr += sizeof(cpio_t);
    
        if(namesize==11){
            if(cmpstr((char*)addr,"TRAILER!!!",10))break;
        }

        char *s = addr;
        if(cmpstr((char*)addr,target,namesize-1)){
            istarget = 1;
        }


        if(namesize>=2){//align
            if((namesize-2)%4==0){
                addr += namesize;
            }else{
                addr += namesize + (4-(namesize-2)%4);
            }
        }else{
            addr += 2;
        }

        if(istarget&&filesize>0){
            char*s = addr;
            for(int i = 0; i < filesize; i++){
                uart_send(*s);
                s++;
            }
            uart_puts("\n\r");
            istarget = 0;
            break;
        }

        if(filesize>0){
            if(filesize%4==0){
                addr += filesize;
            }  
            else{
                addr += filesize + 4 - (filesize%4);
            }

        }
    }
}

