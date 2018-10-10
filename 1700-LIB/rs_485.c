#include "rs_485.h" 
#include "lpc17xx_uart.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "debug_frmwrk.h"
#include "lpc17xx_nvic.h"
void RS485_config(uint32_t Baud_rate){
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	
	
	//���ڿ��ļ���GPIO�ܽ����ú�������֧��GPIO4�Ĺܽ����ã����Ծ���Ҫ�Ĵ����ķ�ʽ���øùܽŹ���Ϊ����
	LPC_PINCON->PINSEL9 |= (3 << 24);             
  LPC_PINCON->PINSEL9 |= (3 << 26);   
		   
	UART_ConfigStructInit(&UARTConfigStruct);
	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART3, &UARTConfigStruct);//��ʼ���ṹ��
	UART_TxCmd(LPC_UART3, ENABLE);//ʹ�ܷ���
	
  UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);//���ý����ж�
  NVIC_SetPriority(UART3_IRQn, ((0x01<<3)|0x01));//�������ȼ�
  NVIC_EnableIRQ(UART3_IRQn);//ʹ���ж�
	
	
}
//����485оƬ�Ľ���/���͵Ĺܽ�
void RS485_control(){
	
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 0;//��ͨGPIO����
	PinCfg.Portnum = 2;	//�˿ں�
	PinCfg.Pinnum = 8;//GPIO2_8
	PINSEL_ConfigPin(&PinCfg);
	GPIO_SetDir(2,(1<<8), 1); //���ö˿����ģʽ  
	RS485PORT_control(1);//���øߵ�ƽ���,�ߵ�ƽ��������/�͵�ƽ��������
}



//�������´��룬��Ϊ��ʹ��printf��
/*********************************************************************************************************
** Function name:       _printf
** Descriptions:        �򴮿ڷ��͵����ַ���Ŀ���Ǻ�stdio����
** input parameters:    ch:   Ҫ���͵��ַ�
** output parameters:   ��
** Returned value:      ���͹����ַ�
*********************************************************************************************************/
void  RS485_printf(const  char *format, ...)
{
    static  char  buffer[512 + 1];
            va_list     vArgs;
            char	*tmp;
    va_start(vArgs, format);
    vsprintf((char *)buffer, (char const *)format, vArgs);
    va_end(vArgs);

    UARTPuts(LPC_UART3,buffer);
}
