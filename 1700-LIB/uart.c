
/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * 文件名称：uart.c
  * 功能说明：串口驱动程序
  * 版    本：V1.1
  * 作    者：openmcu666   
  * 日    期: 20160111
***********************************************************************************************
  * 文件名称：
  * 功能说明：
  * 版    本：
  * 更新作者: 
  * 日    期：
  * 更新原因：
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
函数名:void uart_config(uint32_t Baud_rate)
函数功能:串口0初始化管脚配置
参数:无
返回值:无
*************************************************************************************************/
void uart_config0(uint32_t Baud_rate){
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//设置管脚功能为串口功能
	PinCfg.Portnum = 0;//设置管脚端口号,GPIO0
	PinCfg.Pinnum = 3;//GPIO0_3
		PINSEL_ConfigPin(&PinCfg);//初始化结构体
	PinCfg.Pinnum = 2;//GPIO0_2
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART0, &UARTConfigStruct);//初始化结构体
	UART_TxCmd(LPC_UART0, ENABLE);//使能发送
	
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);//设置接收中断
  NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//设置优先级
  NVIC_EnableIRQ(UART0_IRQn);//智能终端
	

}

/*********************************************************************************************************
** Function name:       UART0_SendByte
** Descriptions:        串口0发送数据
** input parameters:    ucdata
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int UART0_SendByte (int ucData)
{
	while (!(LPC_UART0->LSR & 0x20));           /*读bit5 0 为有数据，1 为发送完成*/
    return (LPC_UART0->THR = ucData);
}

//增加以下代码，是为了使用printf和
/*********************************************************************************************************
** Function name:       sendchar
** Descriptions:        向串口发送单个字符，目的是和stdio连接
** input parameters:    ch:   要发送的字符
** output parameters:   无
** Returned value:      发送过的字符
*********************************************************************************************************/
int sendchar(int ch)
{
     UART0_SendByte(ch);
     return(ch);
}


/************************************************************************************************
函数名:void uart_config2(uint32_t Baud_rate)
函数功能:串口2初始化管脚配置
参数:无
返回值:无
*************************************************************************************************/
void uart_config2(uint32_t Baud_rate){
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;

	PinCfg.Funcnum = 1;//设置管脚功能为串口功能
	PinCfg.Portnum = 0;//设置管脚端口号,GPIO0
	PinCfg.Pinnum = 10;//GPIO0_10
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;//GPIO0_11
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	UART_ConfigStructInit(&UARTConfigStruct);

	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART2, &UARTConfigStruct);//初始化结构体
	UART_TxCmd(LPC_UART2, ENABLE);  //使能发送


	
}
//增加以下代码，是为了使用printf和
/*********************************************************************************************************
** Function name:       _printf
** Descriptions:        向串口发送单个字符，目的是和stdio连接
** input parameters:    ch:   要发送的字符
** output parameters:   无
** Returned value:      发送过的字符
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



