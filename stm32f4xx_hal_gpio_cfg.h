#include "stm32f4xx_hal_gpio.h"

#ifndef STM32F4XX_HAL_GPIO__CFG_H__
#define STM32F4XX_HAL_GPIO__CFG_H__

void GPIO_Init(void);


//Static variables for GPIO structures
//PWM Outpus
extern GPIO_Pin_TypeDef sPWM_Motor1_Enable_PB4;     //TIM3 Channel 1 PWM output
extern GPIO_Pin_TypeDef sPWM_Motor2_Enable_PA7;     //TIM3 Channel 2 PWM output
extern GPIO_Pin_TypeDef sPWM_Motor3_Enable_PC8;     //TIM3 Channel 3 PWM output
extern GPIO_Pin_TypeDef sPWM_Motor4_Enable_PC9;     //TIM3 Channel 4 PWM output
extern GPIO_Pin_TypeDef sPWM_Motor5_Enable_PB8;     //TIM4 Channel 3 PWM output
extern GPIO_Pin_TypeDef sPWM_Motor6_Enable_PB9;     //TIM4 Channel 4 PWM output

//Digital outputs for direction Motor 1
extern GPIO_Pin_TypeDef sPWM_Motor1_IN1_PC10;        //H bridge IN1 signal motor 1(Output) TIM3 Channel 1
extern GPIO_Pin_TypeDef sPWM_Motor1_IN2_PC11;        //H bridge IN2 signal motor 1(Output) TIM3 Channel 1

//Digital outputs for direction Motor 2
extern GPIO_Pin_TypeDef sPWM_Motor2_IN1_PC2;         //H bridge EN1 signal motor 2 (Output) TIM3 Channel 2
extern GPIO_Pin_TypeDef sPWM_Motor2_IN2_PC1;         //H bridge EN2 signal motor 2 (Output) TIM3 Channel 2

//Digital outputs for direction Motor 3
extern GPIO_Pin_TypeDef sPWM_Motor3_IN1_PC3;        //H bridge IN1 signal motor 3 (Output) TIM3 Channel 3
extern GPIO_Pin_TypeDef sPWM_Motor3_IN2_PC0;        //H bridge IN2 signal motor 3 (Output) TIM3 Channel 3

//Digital outputs for direction Motor 4
extern GPIO_Pin_TypeDef sPWM_Motor4_IN1_PA10;       //H bridge EN1 signal motor 4 (Output) TIM3 Channel 4
extern GPIO_Pin_TypeDef sPWM_Motor4_IN2_PC4;        //H bridge EN2 signal motor 4 (Output) TIM3 Channel 4

//Digital outputs for direction Motor 5
extern GPIO_Pin_TypeDef sPWM_Motor5_IN1_PB5;        //H bridge IN1 signal motor 5(Output) TIM4 Channel 3
extern GPIO_Pin_TypeDef sPWM_Motor5_IN2_PB13;       //H bridge IN2 signal motor 5(Output) TIM4 Channel 3

//Digital outputs for direction Motor 6
extern GPIO_Pin_TypeDef sPWM_Motor6_IN1_PB10;       //H bridge EN1 signal motor 6 (Output) TIM4 Channel 4
extern GPIO_Pin_TypeDef sPWM_Motor6_IN2_PB15;       //H bridge EN2 signal motor 6 (Output) TIM4 Channel 4

//UART Comunication
extern GPIO_Pin_TypeDef sUART_Tx_PB6;               //Tx pin for UART1 communication
extern GPIO_Pin_TypeDef sUART_Rx_PB7;               //Rx pin for UART1 comunication (hand held)
extern GPIO_Pin_TypeDef sUART2_Tx_PA2;              //Tx pin for UART2 communication (PC)
extern GPIO_Pin_TypeDef sUART2_Rx_PA3;              //Rx pin for UART2 communication (PC)

#endif
