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
	
	PinCfg.Funcnum = 1;//�ܽŹ���PWM
	PinCfg.OpenDrain = 0;//����
	PinCfg.Pinmode = 0;//����ģʽ
	PinCfg.Portnum = 2;//�˿�2
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
	PWMCfgDat.PrescaleValue = 1;//Ԥ��ƵֵΪ1
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMCfgDat);//��ʼ���ṹ��
	
	
	PWM_MatchUpdate(LPC_PWM1, 0, 100, PWM_MATCH_UPDATE_NOW);//���ø������ͣ�ͨ��0��ƥ��ֵ100����������

	PWMMatchCfgDat.IntOnMatch = DISABLE;//ƥ���ж�ʧ��
	PWMMatchCfgDat.MatchChannel = 0;//ƥ��ͨ��0
	PWMMatchCfgDat.ResetOnMatch = ENABLE;//ƥ�临λʹ��
	PWMMatchCfgDat.StopOnMatch = DISABLE;//ƥ��ֹͣʧ��
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfgDat);//��ʼ��ƥ��
	
	
/*
 {
	 
	   MR1--MR2--->pwm2  gpio2_1
		 MR3--MR4--->pwm4  gpio2_3
		 MR5-------->pwm5  gpio2_4
		 MR6-------->pwm6  gpio2_5
	 
	 
 }
*/

	PWM_ChannelConfig(LPC_PWM1, 2, PWM_CHANNEL_DUAL_EDGE);//PWM1_2 ˫����
	PWM_ChannelConfig(LPC_PWM1, 4, PWM_CHANNEL_DUAL_EDGE);//PWM1_4˫����
	
	PWM_ChannelConfig(LPC_PWM1, 5, PWM_CHANNEL_SINGLE_EDGE);//PWM1_5������
  PWM_ChannelConfig(LPC_PWM1, 6, PWM_CHANNEL_SINGLE_EDGE);//PWM1_6������
	
	
	
	PWM_MatchUpdate(LPC_PWM1, 1, 41, PWM_MATCH_UPDATE_NOW);//����MR1
	PWM_MatchUpdate(LPC_PWM1, 2, 78, PWM_MATCH_UPDATE_NOW);//����MR2
	
	PWM_MatchUpdate(LPC_PWM1, 3, 53, PWM_MATCH_UPDATE_NOW);//����MR3
	PWM_MatchUpdate(LPC_PWM1, 4, 27, PWM_MATCH_UPDATE_NOW);//����MR4
	
	PWM_MatchUpdate(LPC_PWM1, 5, 50, PWM_MATCH_UPDATE_NOW);//����MR5
	PWM_MatchUpdate(LPC_PWM1, 6, 50, PWM_MATCH_UPDATE_NOW);//����MR6


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
	
	PWM_ResetCounter(LPC_PWM1);//��λ������
	PWM_CounterCmd(LPC_PWM1, ENABLE);//ʹ�ܼ�����
	PWM_Cmd(LPC_PWM1, ENABLE);//ʹ��PWM1

	
}
	