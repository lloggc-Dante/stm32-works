// Key.h
#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

void Key_Init(void);

extern volatile uint8_t Key1Flag;   // 按键1请求标志
extern volatile uint8_t Key2Flag;   // 按键2请求标志

#endif
