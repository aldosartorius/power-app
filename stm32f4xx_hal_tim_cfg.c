#include "stm32f4xx_hal_tim_cfg.h"     /*hal_tim header*/


//Initialize structures for timers
TIM_Base_InitTypeDef sTIMER3 = {0};     //PWM Signals
TIM_Base_InitTypeDef sTIMER4 = {0};     //PWM Signals
TIM_Base_InitTypeDef sTIMER2 = {0};     //Delay

//Initialize structures for Output compare PWM mode
TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_1_PWM_Motor1 = {0};  //TIM 3 Channel 1 Output compare structure
TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_2_PWM_Motor2 = {0};  //TIM 3 Channel 2 Output compare structure
TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_3_PWM_Motor3 = {0};  //TIM 3 Channel 3 Output compare structure
TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_4_PWM_Motor4 = {0};  //TIM 3 Channel 4 Output compare structure
TIM_OC_InitTypeDef sOC_TIMER4_CHANNEL_3_PWM_Motor5 = {0};  //TIM 4 Channel 3 Output compare structure
TIM_OC_InitTypeDef sOC_TIMER4_CHANNEL_4_PWM_Motor6 = {0};  //TIM 4 Channel 4 Output compare structure


void TIMERS_Init(void){  
	
			//******************************************TIM 2 (Delay)***************************************
			//Configure Timer 2 for 1 ms Delay (CPU running at 84 Mhz)
			sTIMER2.Timer = TIM_2;              //Timer 2
			sTIMER2.Prescaler = (uint16_t)839;  //PSC register
			sTIMER2.Period = (uint16_t)99;      //ARR register
			//Initialize Timer 2 using HAL
			HAL_TIM_Init(&sTIMER2);
			
	
			//Extern variables to define de frequency of PWMs (Hertz)
			uint16_t TIM3_CO_PWM_Frequency = (uint16_t)15000;
			uint16_t TIM4_CO_PWM_Frequency = (uint16_t)15000;


			//*******************TIM 3 PWM signals **********************************************************
			//Populate TIM_Base_InitTypeDef structure
			sTIMER3.Timer = TIM_3;
			sTIMER3.Prescaler = (uint16_t)0;
			sTIMER3.Period =  (uint16_t)((SystemCoreClock/TIM3_CO_PWM_Frequency)-1); //Period_in_clock_cycles PWM period ((SystemCoreClock)/(Frecuency_Hz))-1  
	    //Initialize Timer 3 using HAL		
	    HAL_TIM_Init(&sTIMER3);

	
			//*******************TIM 4 PWM signals **********************************************************
			//Populate TIM_Base_InitTypeDef structure
			sTIMER4.Timer = TIM_4;
			sTIMER4.Prescaler = (uint16_t)0;
			sTIMER4.Period =  (uint16_t)((SystemCoreClock/TIM4_CO_PWM_Frequency)-1); //Period_in_clock_cycles PWM period ((SystemCoreClock)/(Frecuency_Hz))-1  
			//Initialize Timer 4 using HAL
			HAL_TIM_Init(&sTIMER4);
}

void OC_PWM_Init(void){

	   	//Populate TIM_OC_InitTypeDef structure for TIM 3 Channels 1, 2, 3 and 4 as Output compare mode (PWM)
			sOC_TIMER3_CHANNEL_1_PWM_Motor1.OCChannel = TIM_CHANNEL_1;
			sOC_TIMER3_CHANNEL_1_PWM_Motor1.OCMode = TIM_OCMODE_PWM1;

			sOC_TIMER3_CHANNEL_2_PWM_Motor2.OCChannel = TIM_CHANNEL_2;
			sOC_TIMER3_CHANNEL_2_PWM_Motor2.OCMode = TIM_OCMODE_PWM1;

			sOC_TIMER3_CHANNEL_3_PWM_Motor3.OCChannel = TIM_CHANNEL_3;
			sOC_TIMER3_CHANNEL_3_PWM_Motor3.OCMode = TIM_OCMODE_PWM1;
	
	
			sOC_TIMER3_CHANNEL_4_PWM_Motor4.OCChannel = TIM_CHANNEL_4;
			sOC_TIMER3_CHANNEL_4_PWM_Motor4.OCMode = TIM_OCMODE_PWM1;

	  	//Populate TIM_OC_InitTypeDef structure for TIM 4 Channels 3 and 4 as Output compare mode (PWM)
			sOC_TIMER4_CHANNEL_3_PWM_Motor5.OCChannel = TIM_CHANNEL_3;
			sOC_TIMER4_CHANNEL_3_PWM_Motor5.OCMode = TIM_OCMODE_PWM1;

			sOC_TIMER4_CHANNEL_4_PWM_Motor6.OCChannel = TIM_CHANNEL_4;
			sOC_TIMER4_CHANNEL_4_PWM_Motor6.OCMode = TIM_OCMODE_PWM1;
	
	
			//PWM Initializacion using HAL
			HAL_TIM_PWM_Init(&sTIMER3, &sOC_TIMER3_CHANNEL_1_PWM_Motor1);
			HAL_TIM_PWM_Init(&sTIMER3, &sOC_TIMER3_CHANNEL_2_PWM_Motor2);
			HAL_TIM_PWM_Init(&sTIMER3, &sOC_TIMER3_CHANNEL_3_PWM_Motor3);
		  HAL_TIM_PWM_Init(&sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4);
			HAL_TIM_PWM_Init(&sTIMER4, &sOC_TIMER4_CHANNEL_3_PWM_Motor5);
		  HAL_TIM_PWM_Init(&sTIMER4, &sOC_TIMER4_CHANNEL_4_PWM_Motor6);
			//*********************************************************************************   
}
	
