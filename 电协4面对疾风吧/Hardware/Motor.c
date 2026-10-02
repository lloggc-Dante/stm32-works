// Motor.c（PWMA = PA2 / TIM2_CH3 版本）
#include "stm32f10x.h"
#include "Motor.h"

void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    // TIM2 在 APB1

    GPIO_InitTypeDef GPIO_InitStructure;

    // PA4=AIN1、PA5=AIN2：推挽输出
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PA2=PWMA：复用推挽输出（TIM2_CH3）
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 时基：72MHz/72 = 1MHz，周期 100 → PWM 频率 10kHz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period            = 100 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler         = 72 - 1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // PWM1 模式，通道 3
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 0;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);    // 通道 3

    TIM_Cmd(TIM2, ENABLE);
}

void Motor_SetLevel(uint8_t Level)
{
    const uint8_t Duty[5] = {0, 25, 50, 75, 100};

    // 固定正转：AIN1=1，AIN2=0
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);

    TIM_SetCompare3(TIM2, Duty[Level]);         // 通道 3
}
