/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	main.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-05-08
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		����onenet���ϴ����ݺ��������
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//����Э���
#include "onenet.h"

//�����豸
#include "esp8266.h"

//Ӳ������
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"

//C��
#include <string.h>

unsigned char strings[] = {"hello world"};

/*
************************************************************
*	�������ƣ�	Hardware_Init
*
*	�������ܣ�	Ӳ����ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		��ʼ����Ƭ�������Լ�����豸
************************************************************
*/
void Hardware_Init(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�жϿ�������������

	Delay_Init();									//systick��ʼ��	
	
	//Usart1_Init(115200);							//����1����ӡ��Ϣ��
	
	//Usart2_Init(115200);							//����2������ESP8266��
	
	Led_Init();										//LED��ʼ��
	
	Beep_Init();									//��������ʼ��
	
	Key_Init();										//������ʼ��
	

	
	
	Usart_Init(115200, 1);    //��ӡ��Ϣ
	//Usart_Init(115200, 3);    //����ESP8266
	usart3_init(115200);
	
	UsartPrintf(USART1, " Hardware init finished!  \n");
	//printf("���! \n");
	//USART_SendData(USART1, strings[9]);
}

/*
************************************************************
*	�������ƣ�	main
*
*	�������ܣ�	
*
*	��ڲ�����	��
*
*	���ز�����	0
*
*	˵����		
************************************************************
*/
int main(void)
{
	
	unsigned short timeCount = 0;	//���ͼ������
	
	unsigned char *dataPtr = NULL;
	
	Hardware_Init();				//��ʼ����ΧӲ��
	
Led4_Set(LED_OFF);
	DelayXms(2000);
	Led4_Set(LED_ON);
	DelayXms(2000);
	Led4_Set(LED_OFF);
	DelayXms(2000);
	Led4_Set(LED_ON);
	DelayXms(2000);
	Led4_Set(LED_OFF);
	DelayXms(2000);
	Led4_Set(LED_ON);
	
	
	ESP8266_Init();					//��ʼ��ESP8266
	
	while(OneNet_DevLink())			//����OneNET
		DelayXms(500);
	
//	Beep_Set(BEEP_ON);				//������ʾ����ɹ�
//	DelayXms(250);
//	Beep_Set(BEEP_OFF);
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)1);	
	DelayXms(250);
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)0);	
	
	while(1)
	{
		
		switch(Keyboard())
		{
			case KEY0DOWN:
				
				if(led_status.Led4Sta == LED_OFF)
					Led4_Set(LED_ON);
				else
					Led4_Set(LED_OFF);
				
			break;
			
			case KEY1DOWN:
				
				if(led_status.Led5Sta == LED_OFF)
					Led5_Set(LED_ON);
				else
					Led5_Set(LED_OFF);
				
			break;		
			

			
			default:
			break;
		}
		
		if(++timeCount >= 500)									//���ͼ��5s
		{
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
			OneNet_SendData();									//��������
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		
		DelayXms(10);
	
	}

}
