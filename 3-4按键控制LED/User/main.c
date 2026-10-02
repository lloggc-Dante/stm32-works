#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"

#define KEY_DEBOUNCE_MS 20U

static void Tick_Init(void)
{
	SysTick->LOAD = (SystemCoreClock / 1000U) - 1U;
	SysTick->VAL = 0U;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
}

static uint32_t Tick_GetMs(void)
{
	static uint32_t milliseconds = 0U;

	if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
	{
		milliseconds++;
	}

	return milliseconds;
}

static uint8_t Key_WasPressed(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
	uint8_t *lastState, uint8_t *stableState, uint32_t *lastChangeTime,
	uint32_t now)
{
	uint8_t currentState = GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);

	if (currentState != *lastState)
	{
		*lastState = currentState;
		*lastChangeTime = now;
	}

	if ((uint32_t)(now - *lastChangeTime) >= KEY_DEBOUNCE_MS &&
		currentState != *stableState)
	{
		*stableState = currentState;
		return (uint8_t)(currentState == 0U);
	}

	return 0U;
}

int main(void)
{
	uint8_t key1LastState = 1U;
	uint8_t key1StableState = 1U;
	uint8_t key2LastState = 1U;
	uint8_t key2StableState = 1U;
	uint32_t key1LastChangeTime = 0U;
	uint32_t key2LastChangeTime = 0U;

	LED_Init();
	Key_Init();
	Tick_Init();

	while (1)
	{
		uint32_t now = Tick_GetMs();

		if (Key_WasPressed(GPIOB, GPIO_Pin_1, &key1LastState,
			&key1StableState, &key1LastChangeTime, now))
		{
			LED1_Turn();
		}

		if (Key_WasPressed(GPIOB, GPIO_Pin_11, &key2LastState,
			&key2StableState, &key2LastChangeTime, now))
		{
			LED2_Turn();
		}
	}
}
