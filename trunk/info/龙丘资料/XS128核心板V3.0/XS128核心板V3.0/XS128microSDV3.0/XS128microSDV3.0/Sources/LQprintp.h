#ifndef _LQPRINTF_H
#define _LQPRINTF_H
unsigned char uart_getkey(void);
void uart_init(void);
void uart_putchar(unsigned char ch);
void putstr(char ch[]);
//unsigned char TERMIO_GetChar(void);
void printp( char * , ...);
#endif