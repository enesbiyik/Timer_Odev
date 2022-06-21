/*
 * mytimerfunctions.c
 *
 *  Created on: 18 Haz 2022
 *      Author: enesb
 */
#include "mytimerfunctions.h"

void TIM_Init(TIM_HandleTypeDef* htim2, TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t CounterMode, uint32_t Period, uint32_t ClockDivision, uint8_t TimerMode){

	 htim2->Instance = TIMx;
	 htim2->Init.Prescaler = Prescaler;
	 htim2->Init.CounterMode = CounterMode;
	 htim2->Init.Period = Period;
	 htim2->Init.ClockDivision = ClockDivision;


	 if(TIM_BASE & TimerMode){
		 if (HAL_TIM_Base_Init(htim2) != HAL_OK)
		   {
			 isError = ERROR;
		   }
	 }
	 if(TIM_OC & TimerMode){
		 if (HAL_TIM_OC_Init(htim2) != HAL_OK)
		   {
			 isError = ERROR;;
		   }
	 }
	 if(TIM_IC & TimerMode){
		 if (HAL_TIM_IC_Init(htim2) != HAL_OK)
		   {
			 isError = ERROR;
		   }
	 }
}

void TIM_OC_Config(TIM_HandleTypeDef* htim2, uint32_t Channel, uint32_t OCMode, uint32_t Pulse, uint32_t OCPolarity){

	TIM_OC_InitTypeDef	TIMOCStruct = {0};

	TIMOCStruct.OCMode 		= OCMode;
	TIMOCStruct.Pulse		= Pulse;
	TIMOCStruct.OCPolarity	= OCPolarity;

	if(HAL_TIM_OC_ConfigChannel(htim2, &TIMOCStruct, Channel) != HAL_OK)
		isError = ERROR;
}

void TIM_IC_Config(TIM_HandleTypeDef* htim2, uint32_t Channel, uint32_t ICPolarity, uint32_t ICSelection, uint32_t ICPrescaler){

	TIM_IC_InitTypeDef	TIMICStruct = {0};

	TIMICStruct.ICPolarity 	= ICPolarity;
	TIMICStruct.ICSelection	= ICSelection;
	TIMICStruct.ICPrescaler	= ICPrescaler;

	if(HAL_TIM_IC_ConfigChannel(htim2, &TIMICStruct, Channel) != HAL_OK)
		isError = ERROR;
}

void TIM_StartStop_IT(uint8_t status, TIM_HandleTypeDef* htim2, uint8_t TimerMode, uint32_t Channel){

	if(status == TIM_START){
		if(TimerMode == TIM_BASE){
			if(HAL_TIM_Base_Start_IT(htim2) != HAL_OK)
						isError = ERROR;
		}
		if(TimerMode == TIM_OC){
			if(HAL_TIM_OC_Start_IT(htim2, Channel) != HAL_OK)
				isError = ERROR;
		}
		if(TimerMode == TIM_IC){
			if(HAL_TIM_IC_Start_IT(htim2, Channel) != HAL_OK )
				isError = ERROR;
		}
	}
	else{
		if(TimerMode == TIM_BASE){
			if(HAL_TIM_Base_Stop_IT(htim2) != HAL_OK)
				isError = ERROR;
		}
		if(TimerMode == TIM_OC){
			if(HAL_TIM_OC_Stop_IT(htim2, Channel) != HAL_OK)
				isError = ERROR;
		}
		if(TimerMode == TIM_IC){
			if(HAL_TIM_IC_Stop_IT(htim2, Channel) != HAL_OK )
				isError = ERROR;
		}
	}

}

