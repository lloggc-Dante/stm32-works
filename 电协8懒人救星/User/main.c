#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD0, AD1, AD2, AD3;	//定义AD值变量
uint16_t target;      			// 官方目标亮度
uint8_t  confirmCnt;  			// 确认计数
uint16_t currentCCR;
uint16_t STEP = 50;

//映射函数//
uint16_t Light_MapToCCR(uint16_t light)
{
    #define LIGHT_LO  1715    // 亮端点
    #define LIGHT_HI  3500    // 暗端点
    #define CCR_MAX   1000

    // 限幅：超出端点时钳住
    if (light <= LIGHT_LO) return 1000;   
    if (light >= LIGHT_HI) return 0;   

    // 区间拉伸
    return ( (uint32_t)(LIGHT_HI - light) * 1000 ) / 1785;  //显式转化防止溢出
}
//映射函数//

int main(void)
{
    OLED_Init();
	AD_Init();
	PWM_Init();	
	// ... OLED、ADC 初始化 ... //

    target = Light_GetAvg();   

    while (1)
    {
        uint16_t avg = Light_GetAvg();

        // 由于avg、target 都是无符号数，直接相减可能出问题，
        // 所以先转成有符号数再求绝对值
        int16_t diff = (int16_t)avg - (int16_t)target;
        if (diff < 0) diff = -diff;

        if (diff <= 200)
        {
             confirmCnt = 0;   		
        }
        else
        {
             confirmCnt ++;	 
			 Delay_ms(200);
            if (confirmCnt >= 10)   		//计数超过10改变 target
			{								
				target = avg;   			// 采纳新亮度
                confirmCnt =0;   			// 计数收尾
            }
		}
		
		OLED_ShowNum(1,1,target,4);
		OLED_ShowNum(2,1,avg,4);
		// OLED 上同时显示 avg 和 target 两个数
		
		if(currentCCR != Light_MapToCCR(target))
		{
			if (currentCCR < Light_MapToCCR(target))
			{
				if(Light_MapToCCR(target) - currentCCR <50)
				{	
					PWM_SetCompare1(Light_MapToCCR(target));
					currentCCR = Light_MapToCCR(target);
					Delay_ms(100);
				}
				else
				{
					currentCCR += STEP;
					PWM_SetCompare1(currentCCR);
					Delay_ms(100);
				}
			}
			if (currentCCR > Light_MapToCCR(target))
			{
				if(currentCCR - Light_MapToCCR(target) <50)
				{	
					PWM_SetCompare1(Light_MapToCCR(target));
					currentCCR = Light_MapToCCR(target);
					Delay_ms(100);
				}
				else
				{
					currentCCR -= STEP;
					PWM_SetCompare1(currentCCR);
					Delay_ms(100);
				}
			}
		}
		
	}

        
}
