#ifndef SHELL_H
#define SHELL_H

int read(char* buf, int len);

void help();
void hello();
void reboot();
void cancel_reboot();
void version();
void mem();
void loadimg();
void ls_cpio();
void cat_cpio(char* file);
void shell();

#endif