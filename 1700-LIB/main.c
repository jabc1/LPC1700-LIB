
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "systen_delay.h"
#include "lpc17xx_adc.h"
#include "led.h"
#include "key.h"
#include "interrupt.h"
#include "uart.h"
#include "adc.h"

int main(void)
{
	
	uint32_t ADC_Data;
	uint8_t i;	
	uint16_t adc_value;
	uart_config0(115200);//串口0初始化
	ADCGPIO_config();
	ADC_config();
	 printf("这是LPC1768_ADC测试程序\r\n");
	 while(1){
		 
		 
		 	ADC_Data = 0;
    for(i = 0;i < 8; i++) 
		{
			 ADC_StartCmd(LPC_ADC,ADC_START_NOW);
      adc_value   = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_5);							              /* 采集数据 */
      ADC_Data += adc_value;
    }
    ADC_Data = (ADC_Data / 8);  /* 采样8次进行虑波处理  */
    ADC_Data = (ADC_Data * 3300)/4095;
		printf("ADC value :%dmv \r\n",ADC_Data);
  
	
   }
}



//中断服务函数，放在LPC17xx_it.C文件中
/******************************************************************************
                           End Of File
******************************************************************************/





