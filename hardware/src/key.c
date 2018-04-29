/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	key.c
	*
	*	作者： 		张继瑞
	*
	*	日期： 		2016-11-23
	*
	*	版本： 		V1.0
	*
	*	说明： 		按键IO初始化，按键功能判断
	*
	*	修改记录：	
	************************************************************
	************************************************************
	************************************************************
**/

//按键头文件
#include "key.h"
#include "led.h"
//硬件驱动
#include "delay.h"


io key0 = {GPIOE,GPIO_Pin_4};
io key1 = {GPIOE,GPIO_Pin_3};	
io key2 = {GPIOA,GPIO_Pin_0};   //key_up, WK_UP

/*
************************************************************
*	函数名称：	Key_Init
*
*	函数功能：	按键IO初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		SW2-PD2		SW3-PC11	SW4-PC12	SW5-PC13	
*				按下为低电平		释放为高电平
************************************************************
*/
void Key_Init(void)
{

	GPIO_InitTypeDef gpio_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOD, ENABLE);	//打开GPIOC、GPIOD的时钟
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;									//设置为上拉输入模式
	gpio_initstruct.GPIO_Pin = key0.PIN | key1.PIN | GPIO_Pin_13;			//初始化Pin11、12、13
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;								//承载的最大频率
	GPIO_Init(key0.PORT, &gpio_initstruct);											//初始化GPIOC
	
	gpio_initstruct.GPIO_Pin = key2.PIN;
	GPIO_Init(key2.PORT, &gpio_initstruct);											//初始化GPIOD

}

/*
************************************************************
*	函数名称：	KeyScan
*
*	函数功能：	按键电平扫描
*
*	入口参数：	GPIOX：需要扫描的GPIO组	NUM：该GPIO组内的编号
*
*	返回参数：	IO电平状态
*
*	说明：		
************************************************************
*/
_Bool KeyScan(GPIO_TypeDef* GPIOX, unsigned int NUM)
{
	
	if(GPIOX == key0.PORT)
	{
		if(!GPIO_ReadInputDataBit(key0.PORT, key0.PIN ))	//按下  为低
		{
			Led4_Set(LED_ON);
			return KEYDOWN;
		}
		else									//弹起  为高
		{
			return KEYUP;
		}
	}
	else if(GPIOX == key1.PORT)
	{
		if(!GPIO_ReadInputDataBit(key1.PORT, key1.PIN))	//按下  为低
		{
			return KEYDOWN;
		}
		else									//弹起  为高
		{
			return KEYUP;
		}
	}
	
	return KEYUP;								//默认返回按键释放
	
}

/*
************************************************************
*	函数名称：	Keyboard
*
*	函数功能：	按键功能检测
*
*	入口参数：	
*
*	返回参数：	按键动作
*
*	说明：		分单击、双击、长安
************************************************************
*/
unsigned char Keyboard(void)
{
	
	static unsigned char keyStatus = 0;
	
	if(KeyScan(key0.PORT, key0.PIN) == KEYDOWN)
	{
		keyStatus |= 0x01;							//标记KEY0按下
		
		while(KeyScan(key0.PORT, key0.PIN) != KEYUP)		//等待释放
			return KEYNONE;
	}
	else
	{
		if(keyStatus & 0x01)
		{
			keyStatus &= 0xfe;						//标记KEY0释放
			return KEY0DOWN;
		}
	}
	
	if(KeyScan(key1.PORT, key1.PIN) == KEYDOWN)
	{
		keyStatus |= 0x02;							//标记KEY1按下
		
		while(KeyScan(key1.PORT, key1.PIN) != KEYUP)		//等待释放
			return KEYNONE;
	}
	else
	{
		if(keyStatus & 0x02)
		{
			keyStatus &= 0xfd;						//标记KEY1释放
			return KEY1DOWN;
		}
	}
	
	if(KeyScan(key2.PORT, key2.PIN) == KEYDOWN)
	{
		keyStatus |= 0x04;							//标记KEY2按下
		
		while(KeyScan(key2.PORT, key2.PIN) != KEYUP)		//等待释放
			return KEYNONE;
	}
	else
	{
		if(keyStatus & 0x04)
		{
			keyStatus &= 0xfb;						//标记KEY2释放
			return KEY2DOWN;
		}
	}
	
	if(KeyScan(GPIOD, KEY3) == KEYDOWN)
	{
		keyStatus |= 0x08;							//标记KEY3按下
		
		while(KeyScan(GPIOD, KEY3) != KEYUP)		//等待释放
			return KEYNONE;
	}
	else
	{
		if(keyStatus & 0x08)
		{
			keyStatus &= 0xf7;						//标记KEY3释放
			return KEY3DOWN;
		}
	}
	
	return KEYNONE;
	
}
