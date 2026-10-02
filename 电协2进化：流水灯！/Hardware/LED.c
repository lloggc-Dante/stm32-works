// LED.c（低电平点亮版本）
#include "stm32f10x.h"
#include "LED.h"

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);  // 输出高 = 初始全灭
}

void LED_ShowPos(uint8_t Pos)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);  // 先全灭（输出高）
    if (Pos == 0)      GPIO_ResetBits(GPIOA, GPIO_Pin_1);       // 输出低 = 亮
    else if (Pos == 1) GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    else               GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}
