#ifdef UART_H
#define UART_H

void uart_init();
void uart_send(unsigned int c);
char uart_recv();
void uart_puts(char *s);
void print_num(int num);
void print_hex(unsigned int num);

#endif