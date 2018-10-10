/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * 文件名称：strsendget.c
  * 功能说明：接口函数
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
#include <stdio.h>
#include <time.h>
#include <rt_misc.h>

#pragma import(__use_no_semihosting_swi)
//该文件是为了使用printf文件和scanf文件
extern int  sendchar(int ch);  /* in Serial.c */
extern long timeval;           /* in Time.c   */


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int ch, FILE *f) {
  return (sendchar(ch));
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  sendchar (ch);
}


void _sys_exit(int return_code) {
  while (1);    /* endless loop */
}
