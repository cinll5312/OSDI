#include "gpio.h"
#include "uart.h"

/* Auxilary mini UART registers */
#define AUX_ENABLE      ((volatile unsigned int*)(MMIO_BASE+0x00215004))
#define AUX_MU_IO       ((volatile unsigned int*)(MMIO_BASE+0x00215040))
#define AUX_MU_IER      ((volatile unsigned int*)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR      ((volatile unsigned int*)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR      ((volatile unsigned int*)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR      ((volatile unsigned int*)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR      ((volatile unsigned int*)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR      ((volatile unsigned int*)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  ((volatile unsigned int*)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL     ((volatile unsigned int*)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT     ((volatile unsigned int*)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD     ((volatile unsigned int*)(MMIO_BASE+0x00215068))

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    register unsigned int r;

    /* map UART1 to GPIO pins */
    // 1. Change GPIO 14, 15 to alternate function
    r=*GPFSEL1;
    r&=~((7<<12)|(7<<15)); // clear gpio14, gpio15, leave 12~14 15~17bit
    r|=(2<<12)|(2<<15);    // set gpio14, gpio15 mode alt5  
    *GPFSEL1 = r;

    // 2. Disable GPIO pull up/down (Because these GPIO pins use alternate functions, not basic input-output)
    // Set control signal to disable
    *GPPUD = 0;
    // Wait 150 cycles
    r = 150;
    while (r--) {
        asm volatile("nop");
    }
    // Clock the control signal into the GPIO pads
    *GPPUDCLK0 = (1 << 14) | (1 << 15);//enable GPIO 14 15
    // Wait 150 cycles
    r = 150;
    while (r--) {
        asm volatile("nop");
    }
    // Remove the clock
    *GPPUDCLK0 = 0;

    
    /* initialize UART */
    *AUX_ENABLE |=1;       // enable UART1, AUX mini uart
    *AUX_MU_CNTL = 0;
    *AUX_MU_LCR = 3;       // 8 bits
    *AUX_MU_MCR = 0;
    *AUX_MU_IER = 0;
    *AUX_MU_IIR = 0xc6;    // disable interrupts
    *AUX_MU_BAUD = 270;    // 115200 baud
    // 3. Enable TX, RX
    *AUX_MU_CNTL = 3;
}

/**
 * Send a character
 */
void uart_send(unsigned int c) {
    /* wait until we can send */
    do{
        asm volatile("nop");
    }while(!(*AUX_MU_LSR&0x20));//fifo is not empty
    /* write the character to the buffer */
    *AUX_MU_IO=c;
}

/**
 * Receive a character
 */
char uart_recv() {
    char r;
    /* wait until something is in the buffer */
    do{
        asm volatile("nop");
    }while(!(*AUX_MU_LSR&0x01));//fifo hold at least one symbol -> 1
    /* read it and return */
    r=(char)(*AUX_MU_IO);
    /* convert carrige return to newline */
    return r=='\r'?'\n':r;
}

/**
 * Display a string
 */
void uart_puts(char *s) {
    while(*s) {
        /* convert newline to carrige return + newline */
        if(*s=='\n')
            uart_send('\r');
        uart_send(*s++);
    }
}

void print_num(int num){
	int c[64];
	int i = 0;
	if(num==0){
		uart_send('0');
		return;
	}
	while(num>0){
		c[i] = (num%10) + '0';
		num = num / 10;
		i++;
	}
	while(i>=0){
		i--;
		uart_send(c[i]);
	}
}

void print_hex(unsigned int num){
    uart_puts("0x");
    int c[64];
	int i = 0;
	if(num==0){
		uart_send('0');
		return;
	}
	while(num>0){
		c[i] = (num%16) + '0';
        if(c[i]>57){
            c[i]=c[i]+7;
        }
		num = num / 16;
		i++;
	}
	while(i>=0){
		i--;
		uart_send(c[i]);
	}
    uart_puts("\n");
}
