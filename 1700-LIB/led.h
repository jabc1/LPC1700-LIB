#ifndef _LED_H_
#define _LED_H_
#include <lpc17xx.h>

void LED_Configuration(void);



#define LED4_ON(x) ((x) ? GPIO_SetValue(2, (1<<0)) :  GPIO_ClearValue(2,(1<<0)));
#define LED5_ON(x) ((x) ? GPIO_SetValue(2, (1<<1)):   GPIO_ClearValue(2,(1<<1)));
#define LED6_ON(x) ((x) ? GPIO_SetValue(2, (1<<2)):   GPIO_ClearValue(2,(1<<2)));
#define LED7_ON(x) ((x) ? GPIO_SetValue(2, (1<<3)) :  GPIO_ClearValue(2,(1<<3)));
#define LED8_ON(x) ((x) ? GPIO_SetValue(2, (1<<4)) :  GPIO_ClearValue(2,(1<<4)));
#define LED9_ON(x) ((x) ? GPIO_SetValue(2, (1<<5)) :  GPIO_ClearValue(2,(1<<5)));
#define LED10_ON(x)((x) ? GPIO_SetValue(2, (1<<6)) :  GPIO_ClearValue(2,(1<<6)));
#define LED11_ON(x)((x) ? GPIO_SetValue(2, (1<<7)):   GPIO_ClearValue(2,(1<<7)));

#endif

