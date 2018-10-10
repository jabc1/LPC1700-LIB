#include "pwm.h"
#include "lpc17xx.h"
#include "lpc17xx_pwm.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
void GPIO_config(void){
	int temp=0;
	PWM_TIMERCFG_Type PWMCfgDat;
	PWM_MATCHCFG_Type PWMMatchCfgDat;
	PINSEL_CFG_Type PinCfg;	
	
	PinCfg.Funcnum = 1;//管脚功能PWM
	PinCfg.OpenDrain = 0;//上拉
	PinCfg.Pinmode = 0;//正常模式
	PinCfg.Portnum = 2;//端口2
	for (temp = 0; temp <= 6; temp++){
	PinCfg.Pinnum = temp;//GPIO0_GPIO6
	PINSEL_ConfigPin(&PinCfg);
	}
}
	
	
	
void pwm_config(void){
	
	
	 int temp;
	PWM_TIMERCFG_Type PWMCfgDat;
	PWM_MATCHCFG_Type PWMMatchCfgDat;
	
	PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;
	PWMCfgDat.PrescaleValue = 1;//预分频值为1
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMCfgDat);//初始化结构体
	
	
	PWM_MatchUpdate(LPC_PWM1, 0, 100, PWM_MATCH_UPDATE_NOW);//设置更新类型，通道0，匹配值100，立即更新

	PWMMatchCfgDat.IntOnMatch = DISABLE;//匹配中断失能
	PWMMatchCfgDat.MatchChannel = 0;//匹配通道0
	PWMMatchCfgDat.ResetOnMatch = ENABLE;//匹配复位使能
	PWMMatchCfgDat.StopOnMatch = DISABLE;//匹配停止失能
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfgDat);//初始化匹配
	
	
/*
 {
	 
	   MR1--MR2--->pwm2  gpio2_1
		 MR3--MR4--->pwm4  gpio2_3
		 MR5-------->pwm5  gpio2_4
		 MR6-------->pwm6  gpio2_5
	 
	 
 }
*/

	PWM_ChannelConfig(LPC_PWM1, 2, PWM_CHANNEL_DUAL_EDGE);//PWM1_2 双边沿
	PWM_ChannelConfig(LPC_PWM1, 4, PWM_CHANNEL_DUAL_EDGE);//PWM1_4双边沿
	
	PWM_ChannelConfig(LPC_PWM1, 5, PWM_CHANNEL_SINGLE_EDGE);//PWM1_5单边沿
  PWM_ChannelConfig(LPC_PWM1, 6, PWM_CHANNEL_SINGLE_EDGE);//PWM1_6单边沿
	
	
	
	PWM_MatchUpdate(LPC_PWM1, 1, 41, PWM_MATCH_UPDATE_NOW);//设置MR1
	PWM_MatchUpdate(LPC_PWM1, 2, 78, PWM_MATCH_UPDATE_NOW);//设置MR2
	
	PWM_MatchUpdate(LPC_PWM1, 3, 53, PWM_MATCH_UPDATE_NOW);//设置MR3
	PWM_MatchUpdate(LPC_PWM1, 4, 27, PWM_MATCH_UPDATE_NOW);//设置MR4
	
	PWM_MatchUpdate(LPC_PWM1, 5, 50, PWM_MATCH_UPDATE_NOW);//设置MR5
	PWM_MatchUpdate(LPC_PWM1, 6, 50, PWM_MATCH_UPDATE_NOW);//设置MR6


	for (temp = 1; temp <6; temp++)
	{
	
		PWMMatchCfgDat.IntOnMatch = DISABLE;
		PWMMatchCfgDat.MatchChannel = temp;
		PWMMatchCfgDat.ResetOnMatch = DISABLE;
		PWMMatchCfgDat.StopOnMatch = DISABLE;
		PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfgDat);
	}

	PWM_ChannelCmd(LPC_PWM1, 2, ENABLE);//gpio2_1
	PWM_ChannelCmd(LPC_PWM1, 4, ENABLE);//gpio2_3
	PWM_ChannelCmd(LPC_PWM1, 5, ENABLE);//gpio2_4
	PWM_ChannelCmd(LPC_PWM1, 6, ENABLE);//gpio2_5
	
	PWM_ResetCounter(LPC_PWM1);//复位计数器
	PWM_CounterCmd(LPC_PWM1, ENABLE);//使能计数器
	PWM_Cmd(LPC_PWM1, ENABLE);//使能PWM1

	
}
	