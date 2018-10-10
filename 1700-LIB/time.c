#include "time.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
void GPIO_config(void){
	
	
	PINSEL_CFG_Type PinCfg;
	
	
	PinCfg.Funcnum = 3;//�ܽŹ���,��ʱ��
	PinCfg.OpenDrain = 0;//����ģʽ
	PinCfg.Pinmode = 0;//����
	PinCfg.Portnum = 1;//�˿�GPIO1
	PinCfg.Pinnum = 26;//gpio1_26
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	
	

}

void Time_config(void){
	
	
	TIM_TIMERCFG_Type TIM_ConfigStruct;
  TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;
	
	GPIO_config();//��ʱ���ܽų�ʼ��
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1000000;//Ԥ��Ƶ����ʱ��Ϊ1000000uS = 1S


	TIM_CaptureConfigStruct.CaptureChannel = 0;//ͨ��0
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;//�����ش���
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;//�½��ز���
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;//�жϲ���ʹ��

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);//��ʼ���ṹ��
	TIM_ConfigCapture(LPC_TIM0, &TIM_CaptureConfigStruct);//��ʼ���ṹ��
	TIM_ResetCounter(LPC_TIM0);//��λ��ʱ��



	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));//�����ж����ȼ�
	NVIC_EnableIRQ(TIMER0_IRQn);//ʹ�ܶ�ʱ��0�ж�
	TIM_Cmd(LPC_TIM0,ENABLE);//ʹ�ܶ�ʱ��0
	
}