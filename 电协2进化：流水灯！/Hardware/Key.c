// Key.c
#include "stm32f10x.h"
#include "Key.h"

volatile uint8_t Key1Flag = 0;
volatile uint8_t Key2Flag = 0;

void Key_Init(void)
{
    // ① 开 GPIOB 和 AFIO 时钟（AFIO 必须开，否则中断线配置无效）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // ② PB0、PB11 上拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // ③ 选择 EXTI 中断线对应的 GPIO 引脚
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);

    // ④ 配置 EXTI：中断模式、下降沿触发、使能
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line    = EXTI_Line0 | EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  // 按下：高→低
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // ⑤ NVIC：分组 + 两个通道
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;       // PB0 独占 Line0
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;   // PB11 属于 10~15
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

// 按键1：Line0 中断函数
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        Key1Flag = 1;                          // 只置标志
        EXTI_ClearITPendingBit(EXTI_Line0);    // 必须清中断标志，否则反复进
    }
}

// 按键2：Line11，与 10~15 共用一个函数，必须先判断是哪条线
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line11) == SET)
    {
        Key2Flag = 1;
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
}
