#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

//映射函数//
uint16_t Distance_MapToCCR(uint16_t avg)
{
    #define MAX  3500   // 远端点
    #define MIN  170    // 近端点

    // 限幅：超出端点时钳住
    if (avg <= MIN ) return 100;   
    if (avg >= MAX) return 500;   

    // 区间拉伸
    return ( (uint32_t)(avg - MIN) * 400 ) /3330 + 100;  //显式转化防止溢出
}
	//映射函数//

int main(void)
{
	LED_Init();
    OLED_Init();
	AD_Init();
	Buzzer_Init();
	// ... OLED ADC Buzzer LED初始化 ... //

    while (1)
    {
        uint16_t avg = Distance_GetAvg();
		
		OLED_ShowString(2,1,"avg:");
		OLED_ShowNum(2,5,avg,4);
		// OLED监测	
		
		if(avg >= 3500){
			LED1_ON();
			LED2_OFF();
			Buzzer_OFF();
			
		}
		else{
			LED1_OFF();
			LED2_Turn();
			Buzzer_Turn();
			Delay_ms(Distance_MapToCCR(avg));
		}
	}
}
