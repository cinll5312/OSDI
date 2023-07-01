#include "uart.h"
#include "shell.h"
#include "mailbox.h"
#include "reboot.h"
#include "cpio.h"
#include "utli.h"



int read(char *buf, int len) {
  char c;
  int i;
  
  for (i = 0; i < len; i++) {
    c = uart_recv();
    // if (c == 127) { i--; continue; }//del
    uart_send(c);
    if (c == '\n') {
      c = '\n';
    //   uart_send('\r');
      break;
    }
    buf[i] = c;
  }
  buf[i] = '\0';
  return i;
}


void help(){
	uart_puts("help     : print this menu\n\r");
	uart_puts("hello    : print Hello World!\n\r");
	uart_puts("reboot   : reset the device\n\r");
	uart_puts("version  : print raspi version\n\r");
	uart_puts("memory   : print memory\n\r");
	uart_puts("loadimg  : reload img\n\r");
  	uart_puts("ls       : list files\n\r");
	uart_puts("cat      : show file content\n\r");
}


void hello(){
	uart_puts("Hello World\n");
}

void reboot(){
	reset(100);
	uart_puts("reboot!\n\r");
}

void cancel_reboot(){
	cancel_reset();
}

void version(){
	unsigned int v = get_board_revision();
	uart_puts("Version : ");
	print_hex(v);
}

void mem(){
	get_arm_memory();
}

void loadimg(){
	long load_addr;
	load_addr = 0x60000;//jump to bootloader
	asm volatile(
		"mov x9, 0x60000\n\r"
		"br x9\n\r"::
	);
}

void ls_cpio(){
	lsfile((char*)INITRAMFS);
}

void cat_cpio(char* file){
	catfile((char*)INITRAMFS,file);
}



void shell() {
	char buf[BUF_LEN];
	// uart_puts(buf);
	// char buf1[BUF_LEN];
	// char* buf_ptr = buf1;
	// memset(buf_ptr,"A",BUF_LEN);
	// uart_printf("%s %s\n",buf1,buf);
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
		}else if(cmpstr(buf,"loadimg",sizeof("loadimg"))){
			loadimg();
		}else if(cmpstr(buf,"ls",sizeof("ls"))){
			ls_cpio();
		}else if(cmpstr(buf,"cat",3)){//do not compare '\0' in cat
			char* file = &buf[4];
			cat_cpio(file);
		}else{
			// uart_puts(buf);
			// uart_printf("ret %d\n",ret);
			uart_puts("command not found\n");
		}
	}
}