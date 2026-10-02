#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // LED：PA1/PA2/PA3 推挽输出
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 按键：PB0/PB11 上拉输入
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    LED1_OFF();
    LED2_OFF();
    LED3_OFF();

    uint8_t RunFlag = 0;  										// 0=停止，1=流水灯运行
	uint8_t Step = 0;      										// 流水灯步骤 0~5
	uint8_t RedFlag = 0;   										// 0=红灯灭，1=红灯单独亮

	while (1)
	{
		uint8_t KeyNum = Key_GetNum();

		if (KeyNum == 1)
		{
			if (RunFlag == 1)          						 // ① 流水灯运行中：停止并全灭
			{
				RunFlag = 0;
				RedFlag = 0;
				LED1_OFF();
				LED2_OFF();
				LED3_OFF();
			}
			else                         						// ② 停止状态：翻转红灯
			{				
				RedFlag = !RedFlag;    						  // 0变1、1变0
				if (RedFlag) LED1_ON();
				else         LED1_OFF();
			}
		}

		if (KeyNum == 2)                 							// 按键2：启动流水灯
		{
			RunFlag = 1;
			RedFlag = 0;
			Step = 0;
			LED1_OFF(); LED2_OFF(); LED3_OFF();
		}

		if (RunFlag)                  					   // 流水灯每轮走一小步
		{
			switch (Step)
			{
				case 0: LED1_ON();  break;
				case 1: LED1_OFF(); break;
				case 2: LED2_ON();  break;
				case 3: LED2_OFF(); break;
				case 4: LED3_ON();  break;
				case 5: LED3_OFF(); break;
			}
			Step++;
			if (Step >= 6) Step = 0;
			Delay_ms(200);
		}
	}
}
