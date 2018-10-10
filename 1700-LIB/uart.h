#ifndef _UART_H_
#define _UART_H_

#include <lpc17xx.h>
void uart_config0(uint32_t Baud_rate);
void uart_config2(uint32_t Baud_rate);
void  _printf (const  char *format, ...);

int UART0_GetChar (void) ;
#endif


