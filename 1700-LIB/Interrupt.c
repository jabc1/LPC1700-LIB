
/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * 文件名称：interrupt.c
  * 功能说明：外部中断驱动程序
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


#include "interrupt.h"
#include <lpc17xx.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
/************************************************************************************************
KEY硬件接口:

INIT0---------------->P2.10
KEY1----------------->P2.11
KEY2----------------->P2.12

五向按键:
JOY_SEL-------------->P2.25
JOY_DOWN------------->P2.26
JOY_LEFT------------->P2.27
JOY_RIGHT------------>P2.28
JOY_UP--------------->P2.29
*************************************************************************************************/

/************************************************************************************************
函数名: KEY_Config(void)
函数功能:外部中断初始化管脚配置
参数:无
返回值:无
*************************************************************************************************/
void Interrupt_Config(void){
	
	
	EXTI_InitTypeDef EXTI_config; 
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//外部中断功能
	PinCfg.Portnum = 2;	//端口号
  PinCfg.Pinnum = 10;//GPIO2.10
	PINSEL_ConfigPin(&PinCfg);	

	
	EXTI_config.EXTI_Line=EXTI_EINT0;//中断线0
	EXTI_config.EXTI_Mode=EXTI_MODE_EDGE_SENSITIVE;//边沿触发
	EXTI_config.EXTI_polarity=EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;//下降沿触发
  EXTI_Config(&EXTI_config);
	NVIC_EnableIRQ(EINT0_IRQn); //使能中断

}