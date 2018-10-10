
#include "lpc17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"

void ADCGPIO_config(void){
	
 PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 3;//GPIO管脚设置ADC功能
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 31;//GPIO1_31
	PinCfg.Portnum = 1;
	PINSEL_ConfigPin(&PinCfg);

}
void ADC_config(void){
	
		ADC_Init(LPC_ADC, 200000);//初始化ADC
	
	  ADC_IntConfig(LPC_ADC,ADC_ADINTEN5,ENABLE);
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_5,ENABLE);

	
	
}