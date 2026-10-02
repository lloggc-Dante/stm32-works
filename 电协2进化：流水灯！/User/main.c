#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

int main(void)
{
    LED_Init();
    Key_Init();

    uint8_t Pos       = 0;   // 当前亮灯位置 0/1/2
    uint8_t Direction = 0;   // 0=正向，1=反向（上电方向任意，取0）
    uint8_t FreqLevel = 0;   // 0:2Hz  1:1Hz  2:0.5Hz（上电默认2Hz）
    const uint16_t IntervalTable[3] = {500, 1000, 2000};

    while (1)
    {
        /* 按键1：消抖后换向 */
        if (Key1Flag)
        {
            Delay_ms(20);
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0);  // 等松手
            Delay_ms(20);
            Direction = !Direction;
            Key1Flag = 0;
        }

        /* 按键2：消抖后循环换档 2→1→0.5→2Hz */
        if (Key2Flag)
        {
            Delay_ms(20);
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);
            Delay_ms(20);
            FreqLevel = (FreqLevel + 1) % 3;
            Key2Flag = 0;
        }

        /* 流水灯：显示当前位置 → 推进位置 → 按当前频率延时 */
        LED_ShowPos(Pos);
        if (Direction == 0) Pos = (Pos + 1) % 3;   // 正向 +1
        else                Pos = (Pos + 2) % 3;   // 反向 -1（+2 等价 -1）
        Delay_ms(IntervalTable[FreqLevel]);
    }
}
