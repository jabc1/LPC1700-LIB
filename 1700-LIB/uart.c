
/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * �ļ����ƣ�uart.c
  * ����˵����������������
  * ��    ����V1.1
  * ��    �ߣ�openmcu666   
  * ��    ��: 20160111
***********************************************************************************************
  * �ļ����ƣ�
  * ����˵����
  * ��    ����
  * ��������: 
  * ��    �ڣ�
  * ����ԭ��
************************************************************************************************/

#include <lpc17xx.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "uart.h"
#include "debug_frmwrk.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"
#include "stdarg.h"

/************************************************************************************************
������:void uart_config(uint32_t Baud_rate)
��������:����0��ʼ���ܽ�����
����:��
����ֵ:��
*************************************************************************************************/
void uart_config0(uint32_t Baud_rate){
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//���ùܽŹ���Ϊ���ڹ���
	PinCfg.Portnum = 0;//���ùܽŶ˿ں�,GPIO0
	PinCfg.Pinnum = 3;//GPIO0_3
		PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	PinCfg.Pinnum = 2;//GPIO0_2
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART0, &UARTConfigStruct);//��ʼ���ṹ��
	UART_TxCmd(LPC_UART0, ENABLE);//ʹ�ܷ���
	
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);//���ý����ж�
  NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//�������ȼ�
  NVIC_EnableIRQ(UART0_IRQn);//�����ն�
	

}

/*********************************************************************************************************
** Function name:       UART0_SendByte
** Descriptions:        ����0��������
** input parameters:    ucdata
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int UART0_SendByte (int ucData)
{
	while (!(LPC_UART0->LSR & 0x20));           /*��bit5 0 Ϊ�����ݣ�1 Ϊ�������*/
    return (LPC_UART0->THR = ucData);
}

//�������´��룬��Ϊ��ʹ��printf��
/*********************************************************************************************************
** Function name:       sendchar
** Descriptions:        �򴮿ڷ��͵����ַ���Ŀ���Ǻ�stdio����
** input parameters:    ch:   Ҫ���͵��ַ�
** output parameters:   ��
** Returned value:      ���͹����ַ�
*********************************************************************************************************/
int sendchar(int ch)
{
     UART0_SendByte(ch);
     return(ch);
}


/************************************************************************************************
������:void uart_config2(uint32_t Baud_rate)
��������:����2��ʼ���ܽ�����
����:��
����ֵ:��
*************************************************************************************************/
void uart_config2(uint32_t Baud_rate){
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;

	PinCfg.Funcnum = 1;//���ùܽŹ���Ϊ���ڹ���
	PinCfg.Portnum = 0;//���ùܽŶ˿ں�,GPIO0
	PinCfg.Pinnum = 10;//GPIO0_10
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;//GPIO0_11
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	UART_ConfigStructInit(&UARTConfigStruct);

	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART2, &UARTConfigStruct);//��ʼ���ṹ��
	UART_TxCmd(LPC_UART2, ENABLE);  //ʹ�ܷ���


	
}
//�������´��룬��Ϊ��ʹ��printf��
/*********************************************************************************************************
** Function name:       _printf
** Descriptions:        �򴮿ڷ��͵����ַ���Ŀ���Ǻ�stdio����
** input parameters:    ch:   Ҫ���͵��ַ�
** output parameters:   ��
** Returned value:      ���͹����ַ�
*********************************************************************************************************/
void  _printf (const  char *format, ...)
{
    static  char  buffer[512 + 1];
            va_list     vArgs;
            char	*tmp;
    va_start(vArgs, format);
    vsprintf((char *)buffer, (char const *)format, vArgs);
    va_end(vArgs);

 
	UARTPuts(LPC_UART2,buffer);
}



