#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;					//结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
				
	GPIO_Init(GPIOA, &GPIO_InitStructure);					
	
	GPIO_SetBits(GPIOA,GPIO_Pin_6);				        	//默认关
	
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0 )
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}
}

