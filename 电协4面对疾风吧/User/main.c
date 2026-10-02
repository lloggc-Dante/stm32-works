#include "stm32f10x.h"
#include "Delay.h"
#include "Motor.h"
#include "Key.h"

int main(void)
{
    Motor_Init();
    Key_Init();

    uint8_t Level = 0;              // 上电默认 0 挡（停止）
    Motor_SetLevel(Level);

    while (1)
    {
        uint8_t KeyNum = Key_GetNum();

        if (KeyNum == 1 && Level < 4)   // 加挡，到 4 挡封顶
        {
            Level++;
        }
        if (KeyNum == 2 && Level > 0)   // 减挡，到 0 挡封底
        {
            Level--;
        }

        Motor_SetLevel(Level);
    }
}
