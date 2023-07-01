#include "uart.h"
#include "mailbox.h"
#include "reboot.h"

#define BUF_LEN 64
#define new_img  ((volatile unsigned int*)(0x80000))


int _read(char *buf, int len);
int _cmpstr(const char* s1, const char* s2, int len);

// void move_kernel(){
//     uart_init();
//     extern unsigned int __bss_end;
//     volatile unsigned int* base = 0x80000;
//     volatile unsigned int* new = 0x60000;
//     unsigned int diff = __bss_end - 0x80000;
//     print_num(diff);
//     while(diff--){
//         *new = *base;
//         new++;
//         base++;
//     }
//     uart_puts("move complete\n");
// }

int loadkernel(){
    uart_init();
	char c;
    char* new_img_ptr = new_img;
    static char buf[BUF_LEN];
    int img_size = 0;
    int i = 0;
    extern unsigned int __bss_end;
    volatile unsigned int* base = 0x80000;
    volatile unsigned int* new = 0x60000;
    unsigned int diff = __bss_end - 0x80000;

    uart_puts("\n\r");
    uart_puts("Here is Bootloader\n\r");
    uart_puts("\n\r");
    while(1){
        // uart_puts("# ");
        _read(buf, BUF_LEN);
        if(_cmpstr(buf,"loadimg",sizeof("loadimg"))){
            int k;
            for (i = 0; i < 4; i++) {
                img_size <<= 8;
                k = (int)uart_recv_int();
                img_size |= k;
            }
            // print_num(img_size);
            break;
        }else if(_cmpstr(buf,"noloadimg",sizeof("noloadimg"))){
            img_size = 0;
            break;
        }if(_cmpstr(buf,"first",sizeof("first"))){
            print_num(diff);
            // while(diff--){
            //     *new = *base;
            //     new++;
            //     base++;
            // }
            // asm volatile("mov x9, 0x80000\n\r"
            //               "br x9\n\r"::
            // );
            // int k;
            // for (i = 0; i < 4; i++) {
            //     img_size <<= 8;
            //     k = (int)uart_recv_int();
            //     img_size |= k;
            // }
            // print_num(img_size);
            break;
        }else{
            uart_puts("Here is Bootloader, send new img\n\r");
        }
        
    }
    while(i<=img_size&&img_size!=0){
        i++;
        c = uart_recv_int();
        *new_img_ptr = c;
        new_img_ptr++;
    }
}



int _read(char *buf, int len) {
  char c;
  int i;
  for (i = 0; i < len; i++) {
    c = uart_recv();
    if (c == 127) { i--; continue; }//del
    uart_send(c);
    if (c == '\n') {
      c = '\n';
      uart_send('\r');
      break;
    }
    buf[i] = c;
  }
  buf[i] = '\0';
  return i;
}


int _cmpstr(const char* s1, const char* s2, int len){
	for(int i = 0; i < len; i++){
		if(s1[i] != s2[i]){
			return 0;
		}
		else if(s1[i]=='\0')break;
	}
	return 1;
}