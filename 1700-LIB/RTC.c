
/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * �ļ����ƣ�RTC.c
  * ����˵����RTC��������
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
	***********************************************************************************************/
#include "lpc17xx.h"
#include "lpc17xx_rtc.h"
#include "rtc.h"

void RTC_config(void){
	
	RTC_DeInit(LPC_RTC);//��λRTCʱ��
 
  //����RTC
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_SECOND, 45);//��
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_MINUTE, 55);//��
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_HOUR, 9);//ʱ
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_DAYOFMONTH, 28);//ĳ���µ�ĳһ��
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_MONTH, 4);//�·�
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_YEAR, 2018);//�������

	RTC_CntIncrIntConfig (LPC_RTC, RTC_TIMETYPE_SECOND, ENABLE);//����������жϣ�һ��һ���ж�
	RTC_Cmd(LPC_RTC, ENABLE);//ʹ��RTC
  NVIC_SetPriority(RTC_IRQn, ((0x01<<3)|0x01));//�������ȼ�
  NVIC_EnableIRQ(RTC_IRQn);//ʹ���ж�

	
}