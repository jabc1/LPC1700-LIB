
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
	uart_config0(115200);//����0��ʼ��
	ADCGPIO_config();
	ADC_config();
	 printf("����LPC1768_ADC���Գ���\r\n");
	 while(1){
		 
		 
		 	ADC_Data = 0;
    for(i = 0;i < 8; i++) 
		{
			 ADC_StartCmd(LPC_ADC,ADC_START_NOW);
      adc_value   = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_5);							              /* �ɼ����� */
      ADC_Data += adc_value;
    }
    ADC_Data = (ADC_Data / 8);  /* ����8�ν����ǲ�����  */
    ADC_Data = (ADC_Data * 3300)/4095;
		printf("ADC value :%dmv \r\n",ADC_Data);
  
	
   }
}



//�жϷ�����������LPC17xx_it.C�ļ���
/******************************************************************************
                           End Of File
******************************************************************************/





