/*
 * mytimerfunctions.h
 *
 *  Created on: 18 Haz 2022
 *      Author: enesb
 */

#ifndef INC_MYTIMERFUNCTIONS_H_
#define INC_MYTIMERFUNCTIONS_H_

#include "stm32f4xx_hal.h"

extern uint8_t isError;

#define TIM_BASE	001
#define	TIM_IC		010
#define	TIM_OC		100

#define TIM_CHANNEL_NONE	0

#define TIM_START	0
#define TIM_STOP	1

void TIM_Init(TIM_HandleTypeDef* htim2, TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t CounterMode, uint32_t Period, uint32_t ClockDivision, uint8_t TimerMode);
void TIM_OC_Config(TIM_HandleTypeDef* htim2, uint32_t Channel, uint32_t OCMode, uint32_t Pulse, uint32_t OCPolarity);
void TIM_IC_Config(TIM_HandleTypeDef* htim2, uint32_t Channel, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICPrescaler);
void TIM_StartStop_IT(uint8_t status, TIM_HandleTypeDef* htim2, uint8_t TimerMode, uint32_t Channel);

#endif /* INC_MYTIMERFUNCTIONS_H_ */
