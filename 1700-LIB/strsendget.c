/********************************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ********************************************************************************************
  * �ļ����ƣ�strsendget.c
  * ����˵�����ӿں���
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
************************************************************************************************/
#include <stdio.h>
#include <time.h>
#include <rt_misc.h>

#pragma import(__use_no_semihosting_swi)
//���ļ���Ϊ��ʹ��printf�ļ���scanf�ļ�
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
