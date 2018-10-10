#ifndef _RS_485_H_
#define _RS_485_H_
#include "lpc17xx.h"
#include "lpc17xx_gpio.h"

void RS485_control();
#define RS485PORT_control(x) ((x) ? GPIO_SetValue(2, (1<<8)) :  GPIO_ClearValue(2,(1<<8)));
void RS485_config(uint32_t Baud_rate);
void  RS485_printf(const  char *format, ...);
#endif

