
/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * 文件名称：RTC.c
  * 功能说明：RTC驱动程序
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
	***********************************************************************************************/
#include "lpc17xx.h"
#include "lpc17xx_rtc.h"
#include "rtc.h"

void RTC_config(void){
	
	RTC_DeInit(LPC_RTC);//复位RTC时钟
 
  //设置RTC
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_SECOND, 45);//秒
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_MINUTE, 55);//分
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_HOUR, 9);//时
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_DAYOFMONTH, 28);//某个月的某一天
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_MONTH, 4);//月份
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_YEAR, 2018);//设置年份

	RTC_CntIncrIntConfig (LPC_RTC, RTC_TIMETYPE_SECOND, ENABLE);//设置秒递增中断，一秒一次中断
	RTC_Cmd(LPC_RTC, ENABLE);//使能RTC
  NVIC_SetPriority(RTC_IRQn, ((0x01<<3)|0x01));//设置优先级
  NVIC_EnableIRQ(RTC_IRQn);//使能中断

	
}