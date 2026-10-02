#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

int main(void)
{
    OLED_Init();

    OLED_ShowString(1, 1, "Logic");
	OLED_ShowChinese(40,0,0);
	OLED_ShowChinese(60,0,1);
	OLED_ShowChinese(80,0,2);
	OLED_ShowChinese(100,0,3);
	OLED_ShowChinese(0,2,4);
	OLED_ShowChinese(20,2,5);
	OLED_ShowChinese(40,2,6);
	OLED_ShowChinese(60,2,7);
	OLED_ShowChinese(80,2,8);
	OLED_ShowChinese(100,2,9);
	OLED_ShowChinese(0,4,10);
	OLED_ShowChinese(20,4,11);
	OLED_ShowChinese(36,4,12);

    while (1)
    {
    }
}
