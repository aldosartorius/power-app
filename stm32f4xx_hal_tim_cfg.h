#include "stm32f4xx_hal_tim.h"

#ifndef STM32F4XX_HAL_TIM__CFG_H__
#define STM32F4XX_HAL_TIM__CFG_H__

//Functions prototype
void TIMERS_Init(void);    //Function for timer initializacion
void OC_PWM_Init(void);    //Function for Output Compare PWM initializacion

//Extern variables for Timers Structure
extern TIM_Base_InitTypeDef sTIMER3;     //Timer 3 for PWM Signals, channels 1, 2, 3, and 4
extern TIM_Base_InitTypeDef sTIMER4;     //Timer 4 for PWM Signals, channels 3 and 4
extern TIM_Base_InitTypeDef sTIMER2;     //Timer 2 for delay 


//Extern variables for Timers Output Compare Structure for PWM
extern TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_1_PWM_Motor1;  //TIM 3 Channel 1 Output compare structure
extern TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_2_PWM_Motor2;  //TIM 3 Channel 2 Output compare structure
extern TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_3_PWM_Motor3;  //TIM 3 Channel 3 Output compare structure
extern TIM_OC_InitTypeDef sOC_TIMER3_CHANNEL_4_PWM_Motor4;  //TIM 3 Channel 4 Output compare structure
extern TIM_OC_InitTypeDef sOC_TIMER4_CHANNEL_3_PWM_Motor5;  //TIM 4 Channel 3 Output compare structure
extern TIM_OC_InitTypeDef sOC_TIMER4_CHANNEL_4_PWM_Motor6;  //TIM 4 Channel 4 Output compare structure


#endif
