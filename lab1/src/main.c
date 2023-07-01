#include "uart.h"
#include "shell.h"


void kernel_main(){
    uart_init();
	uart_puts("Basic Shell!\n\r");
	while (1) {
		shell();
	}
}