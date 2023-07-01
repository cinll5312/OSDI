#ifdef SHELL_H
#define SHELL_H

int read(char* buf, int len);
int cmpstr(const char* s1, const char* s2, int len);
void help();
void hello();
void reboot();
void cancel_reboot();
void version();
void mem();
void shell();

#endif