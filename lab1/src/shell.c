#include "uart.h"
#include "shell.h"
#include "mailbox.h"
#include "reboot.h"
#define BUF_LEN 64

int read(char *buf, int len) {
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


int cmpstr(const char* s1, const char* s2, int len){
	for(int i = 0; i < len; i++){
		if(s1[i] != s2[i]){
			return 0;
		}
		else if(s1[i]=='\0')break;
	}
	return 1;
}


void help(){
	uart_puts("help     : print this menu\n\r");
	uart_puts("hello    : print Hello World!\n\r");
	uart_puts("reboot   : reset the device\n\r");
	uart_puts("version  : print raspi version\n\r");
	uart_puts("memory   : print memory\n\r");
	
  	
}


void hello(){
	uart_puts("Hello World\n");
}

void reboot(){
	reset(100);
	uart_puts("reboot!\n\r");
	// int i = 0;
	// int tick = 0;
	// static char buf[BUF_LEN];
	// read(buf, BUF_LEN);
	// while(buf[i]!='\n'){
	// 	int a = (int)buf[i];
	// 	uart_send(a);
	// 	tick = tick*10;
	// 	tick += (int)buf[i] - '0';
	// 	i++;
	// }
	// uart_puts("\n");
	// print_num(tick);
	// reset(tick);
}

void cancel_reboot(){
	cancel_reset();
}

void version(){
	unsigned int v = get_board_revision();
	print_hex(v);
}

void mem(){
	unsigned int m = get_arm_memory();
	print_hex(m);
}


void shell() {
	static char buf[BUF_LEN];
	int ret;
	
	while(1){
		uart_puts("# ");
    	ret = read(buf, BUF_LEN);
		if(cmpstr(buf, "help",sizeof("help"))){
			help();
		}else if(cmpstr(buf,"hello",sizeof("hello"))){
			hello();
		}else if(cmpstr(buf,"reboot",sizeof("reboot"))){
			reboot();
		}else if(cmpstr(buf,"cancel_reboot",sizeof("cancel_reboot"))){
			cancel_reboot();
		}else if(cmpstr(buf,"version",sizeof("version"))){
			version();
		}else if(cmpstr(buf,"memory",sizeof("memory"))){
			mem();
		}else{
			uart_puts(buf);
			uart_puts(" command not found\n");
		}
	}
}