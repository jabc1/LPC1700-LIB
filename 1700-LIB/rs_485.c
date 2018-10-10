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
	
	
	//由于库文件的GPIO管脚配置函数，不支持GPIO4的管脚配置，所以就是要寄存器的方式配置该管脚功能为串口
	LPC_PINCON->PINSEL9 |= (3 << 24);             
  LPC_PINCON->PINSEL9 |= (3 << 26);   
		   
	UART_ConfigStructInit(&UARTConfigStruct);
	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART3, &UARTConfigStruct);//初始化结构体
	UART_TxCmd(LPC_UART3, ENABLE);//使能发送
	
  UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);//设置接收中断
  NVIC_SetPriority(UART3_IRQn, ((0x01<<3)|0x01));//设置优先级
  NVIC_EnableIRQ(UART3_IRQn);//使能中断
	
	
}
//控制485芯片的接收/发送的管脚
void RS485_control(){
	
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 0;//普通GPIO功能
	PinCfg.Portnum = 2;	//端口号
	PinCfg.Pinnum = 8;//GPIO2_8
	PINSEL_ConfigPin(&PinCfg);
	GPIO_SetDir(2,(1<<8), 1); //设置端口输出模式  
	RS485PORT_control(1);//设置高电平输出,高电平发送数据/低电平接收数据
}



//增加以下代码，是为了使用printf和
/*********************************************************************************************************
** Function name:       _printf
** Descriptions:        向串口发送单个字符，目的是和stdio连接
** input parameters:    ch:   要发送的字符
** output parameters:   无
** Returned value:      发送过的字符
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
