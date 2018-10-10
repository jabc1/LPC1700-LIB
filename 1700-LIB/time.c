#include "time.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
void GPIO_config(void){
	
	
	PINSEL_CFG_Type PinCfg;
	
	
	PinCfg.Funcnum = 3;//管脚功能,定时器
	PinCfg.OpenDrain = 0;//正常模式
	PinCfg.Pinmode = 0;//上拉
	PinCfg.Portnum = 1;//端口GPIO1
	PinCfg.Pinnum = 26;//gpio1_26
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	
	

}

void Time_config(void){
	
	
	TIM_TIMERCFG_Type TIM_ConfigStruct;
  TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;
	
	GPIO_config();//定时器管脚初始化
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1000000;//预分频计数时间为1000000uS = 1S


	TIM_CaptureConfigStruct.CaptureChannel = 0;//通道0
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;//上升沿触发
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;//下降沿捕获
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;//中断捕获使能

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);//初始化结构体
	TIM_ConfigCapture(LPC_TIM0, &TIM_CaptureConfigStruct);//初始化结构体
	TIM_ResetCounter(LPC_TIM0);//复位定时器



	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));//设置中断优先级
	NVIC_EnableIRQ(TIMER0_IRQn);//使能定时器0中断
	TIM_Cmd(LPC_TIM0,ENABLE);//使能定时器0
	
}