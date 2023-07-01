#include "mailbox.h"
#include "uart.h"

int mailbox_call(unsigned int *msg, unsigned char channel) {
    unsigned long r = ((unsigned long)msg & 0xFFFFFFF0) | (channel & 0xF);
    while ((*MAILBOX_STATUS) & MAILBOX_FULL);
    *MAILBOX_WRITE = r;
    while (1) {
        while ((*MAILBOX_STATUS) & MAILBOX_EMPTY);
        if ((*MAILBOX_READ) == r){
            return msg[1] == REQUEST_SUCCEED;
        }
    }
}
unsigned int get_board_revision(){
  unsigned int __attribute__((aligned(16))) mailbox[7];
//   unsigned int mailbox[7];
  mailbox[0] = 7 * 4; // buffer size in bytes
  mailbox[1] = REQUEST_CODE;
  // tags begin
  mailbox[2] = GET_BOARD_REVISION; // tag identifier
  mailbox[3] = 4; // maximum of request and response value buffer's length.
  mailbox[4] = TAG_REQUEST_CODE;
  mailbox[5] = 0; // value buffer
  // tags end
  mailbox[6] = END_TAG;

  mailbox_call(mailbox, 8); 
//   printf("0x%x\n", mailbox[5]); 
  return mailbox[5];
}

void get_arm_memory(){
  unsigned int __attribute__((aligned(16))) mailbox[8];
  mailbox[0] = 8 * 4; // buffer size in bytes
  mailbox[1] = REQUEST_CODE;
  // tags begin
  mailbox[2] = GET_ARM_MEMORY; // tag identifier
  mailbox[3] = 8; // maximum of request and response value buffer's length.
  mailbox[4] = TAG_REQUEST_CODE;
  mailbox[5] = 0; // value buffer
  mailbox[6] = 0;
  // tags end
  mailbox[7] = END_TAG;

  mailbox_call(mailbox, 8); 
 
  uart_puts("base address : ");
  print_hex(mailbox[6]);
  // uart_puts("\n");
  uart_puts("offset : ");
  print_hex(mailbox[0]);
}