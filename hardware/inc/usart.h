#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"

//C库
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


#define USART_DEBUG		USART1		//调试打印所使用的串口组


/******************************************正点原子**************************************************/

#define USART3_MAX_RECV_LEN		600					//最大接收缓存字节数
#define USART3_MAX_SEND_LEN		600					//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.
extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern vu16 USART3_RX_STA;   						//接收数据状态
void usart3_init(u32 bound);				//串口3初始化 
void u3_printf(char* fmt,...);
/************************************************************************************************/


void Usart_Init(unsigned int baud, unsigned char id);

void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif
