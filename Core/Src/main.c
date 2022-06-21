#include "main.h"
#include "mytimerfunctions.h"

//	Frequency Defines
#define FREQ	16000000
#define	PERIOD	(double)1/FREQ

//	Error Detection
#define OK		0
#define	ERROR	1

uint8_t isError;

//	Timer Struct
TIM_HandleTypeDef hTIMStruct;

//	Registers to Calculate Frequency
uint32_t callback_val;
uint32_t stp = 16000000;

uint32_t capture_val1, capture_val2;

double frequency_of_input_signal;	//	Calculation Frequency

uint32_t test;

void CLK_Init(void);

int main(void){

	HAL_Init();

	CLK_Init();

	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Timer Initialize Funtion
	TIM_Init(&hTIMStruct, 				//	Struct
			 TIM2, 						//	Instance
			 0, 						//	Prescaler
			 TIM_COUNTERMODE_UP, 		//	Counter Mode
			 4294967295, 				//	Period
			 TIM_CLOCKDIVISION_DIV1,	//	Clock Division
			 TIM_OC | TIM_IC			//	Initialize Mode
			 );

	// Timer OC Config Function
	TIM_OC_Config(&hTIMStruct, 			//	Struct
				  TIM_CHANNEL_1, 		//	Channel
				  TIM_OCMODE_TOGGLE, 	//	OCMode
				  stp, 					//	Pulse
				  TIM_OCPOLARITY_HIGH	//	OCPolarity
				  );

	// Timer IC Config Function
	TIM_IC_Config(&hTIMStruct, 						//	Struct
				  TIM_CHANNEL_2, 					//	Channel
				  TIM_INPUTCHANNELPOLARITY_RISING, 	//	IC Polarity
				  TIM_ICSELECTION_DIRECTTI, 		//	IC Selection
				  TIM_ICPSC_DIV1					//	IC Prescaler
				  );

	HAL_TIM_MspPostInit(&hTIMStruct);   //  GPIO Configuration

	//	Timer Interrupt Start Function
	TIM_StartStop_IT(TIM_START, &hTIMStruct, TIM_OC, TIM_CHANNEL_1);  // Timer Output Compare Start
	TIM_StartStop_IT(TIM_START, &hTIMStruct, TIM_IC, TIM_CHANNEL_2);  // Timer Input Capture Start

	while(1)
		;

	return 0;
}

void CLK_Init(void){

	RCC_OscInitTypeDef	OSCStruct;

	OSCStruct.OscillatorType	= RCC_OSCILLATORTYPE_HSI;
	OSCStruct.HSIState 			= RCC_HSI_ON;

	if(HAL_RCC_OscConfig(&OSCStruct) != HAL_OK)
		isError = ERROR;

	RCC_ClkInitTypeDef	RCCStruct;

	RCCStruct.ClockType 		= RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCCStruct.SYSCLKSource		= RCC_SYSCLKSOURCE_HSI;
	RCCStruct.AHBCLKDivider		= RCC_SYSCLK_DIV1;
	RCCStruct.APB1CLKDivider	= RCC_HCLK_DIV1;
	RCCStruct.APB2CLKDivider	= RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&RCCStruct, FLASH_LATENCY_0) != HAL_OK)
		isError = ERROR;
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){

	callback_val = __HAL_TIM_GET_COMPARE(&hTIMStruct, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&hTIMStruct, TIM_CHANNEL_1, callback_val + stp);

}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){

	test ++;

	static uint8_t captured_times;
	uint32_t difference;
	double period_of_input_signal;

	if(captured_times == 0){
		capture_val1 = __HAL_TIM_GET_COMPARE(&hTIMStruct, TIM_CHANNEL_2);
		captured_times++;
	}
	else if(captured_times == 1){
		capture_val2 = __HAL_TIM_GET_COMPARE(&hTIMStruct, TIM_CHANNEL_2);
		captured_times = 0;

		difference = capture_val2 - capture_val1;

		period_of_input_signal = (double)difference * (PERIOD);
		frequency_of_input_signal = 1 / period_of_input_signal;
	}

}
