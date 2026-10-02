// Key.c
#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"

/* ============ 按键引脚：接线不同时只改这里 ============ */
#define KEY_UP_PORT    GPIOB
#define KEY_UP_PIN     GPIO_Pin_11    // 加挡按键（默认 PB0）
#define KEY_DOWN_PORT  GPIOB
#define KEY_DOWN_PIN   GPIO_Pin_0   // 减挡按键（默认 PB1）
/* =================================================== */

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;   // 上拉，按键另一端接 GND
    GPIO_InitStructure.GPIO_Pin   = KEY_UP_PIN | KEY_DOWN_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
    uint8_t n = 0;

    if (GPIO_ReadInputDataBit(KEY_UP_PORT, KEY_UP_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(KEY_UP_PORT, KEY_UP_PIN) == 0);
        Delay_ms(20);
        n = 1;
    }

    if (GPIO_ReadInputDataBit(KEY_DOWN_PORT, KEY_DOWN_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(KEY_DOWN_PORT, KEY_DOWN_PIN) == 0);
        Delay_ms(20);
        n = 2;
    }

    return n;
}
