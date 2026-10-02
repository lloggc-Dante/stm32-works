#include "stm32f10x.h"
#include "Delay.h"
#include "Servo.h"
#include "Pot.h"

int main(void)
{
    Servo_Init();
    Pot_Init();

    while (1)
    {
        uint32_t Sum = 0;
        uint8_t i;
        for (i = 0; i < 5; i++)
        {
            Sum += Pot_GetValue();
        }
        uint16_t Adc = Sum / 5;                       // 0~4095，平均降噪

        uint8_t Angle = (uint32_t)Adc * 180 / 4095;   // 映射到 0~180°
        Servo_SetAngle(Angle);

        Delay_ms(20);
    }
}
