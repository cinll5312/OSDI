#include "uart.h"
#include "shell.h"
#include "mm.h"

void kernel_main(){
	// uart_puts("Basic Shell\n\r");
	char* string = simple_malloc(8);

    uart_init();
	while (1) {
		shell();
	}
}