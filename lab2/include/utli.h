#ifndef UTLI_H
#define UTLI_H

#define BUF_LEN 64
#define NULL 0
typedef unsigned long        size_t;
//for simple malloc
#define memptr unsigned
memptr free_mem_ptr;
memptr free_mem_end_ptr;

// va_list for printf
typedef __builtin_va_list va_list;
#define va_start(v, l)	__builtin_va_start(v, l)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v, T)	__builtin_va_arg(v, T)
#define va_copy(d, s)	__builtin_va_copy(d, s)

// vsprintf
#define SIGN	1		/* unsigned/signed, must be 1 */
#define LEFT	2		/* left justified */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define ZEROPAD	16		/* pad with zero, must be 16 == '0' - ' ' */
#define SMALL	32		/* use lowercase in hex (must be 32 == 0x20) */
#define SPECIAL	64		/* prefix hex with "0x", octal with "0" */

#define __do_div(n, base) ({ \
int __res; \
__res = ((unsigned long) n) % (unsigned) base; \
n = ((unsigned long) n) / (unsigned) base; \
__res; })

static inline int isdigit(int ch);
static inline int ishex(int ch);
static int skip_atoi(const char **s);
int atoi(char* s);
static char *number(char *str, long num, int base, int size, int precision, int type);
size_t strnlen(const char *s, size_t maxlen);
int uart_vsprintf(char *buf, const char *fmt, va_list args);
void *memset(void *s, int c, size_t count);
int cmpstr(const char* s1, const char* s2, int len);
void *memcpy(void *str1, const void *str2, size_t n);
int char2int(char* buf, int len);

#endif