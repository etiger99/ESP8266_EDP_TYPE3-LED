#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"

//C��
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


#define USART_DEBUG		USART1		//���Դ�ӡ��ʹ�õĴ�����


/******************************************����ԭ��**************************************************/

#define USART3_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART3_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART3_RX_EN 			1					//0,������;1,����.
extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16 USART3_RX_STA;   						//��������״̬
void usart3_init(u32 bound);				//����3��ʼ�� 
void u3_printf(char* fmt,...);
/************************************************************************************************/


void Usart_Init(unsigned int baud, unsigned char id);

void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif
