#ifndef __AD_H
#define __AD_H

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);
uint16_t Distance_GetAvg(void);				//消抖

#endif
