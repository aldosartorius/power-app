#include "stm32f4xx_hal_gpio_cfg.h"     /*hal_gpio header*/


//Initialize GPIO structures for PWM Outputs

//PWM Outpus

 GPIO_Pin_TypeDef sPWM_Motor1_Enable_PB4 = {0};     //TIM3 Channel 1 PWM output
 GPIO_Pin_TypeDef sPWM_Motor2_Enable_PA7 = {0};     //TIM3 Channel 2 PWM output
 GPIO_Pin_TypeDef sPWM_Motor3_Enable_PC8 = {0};     //TIM3 Channel 3 PWM output
 GPIO_Pin_TypeDef sPWM_Motor4_Enable_PC9 = {0};     //TIM3 Channel 4 PWM output
 GPIO_Pin_TypeDef sPWM_Motor5_Enable_PB8 = {0};     //TIM4 Channel 3 PWM output 
 GPIO_Pin_TypeDef sPWM_Motor6_Enable_PB9 = {0};     //TIM4 Channel 4 PWM output

//Digital outputs for direction Motor 1
GPIO_Pin_TypeDef sPWM_Motor1_IN1_PC10 ={0};        //H bridge IN1 signal motor 1(Output) TIM3 Channel 1
GPIO_Pin_TypeDef sPWM_Motor1_IN2_PC11 ={0};        //H bridge IN2 signal motor 1(Output) TIM3 Channel 1

//Digital outputs for direction Motor 2
GPIO_Pin_TypeDef sPWM_Motor2_IN1_PC2 ={0};         //H bridge EN1 signal motor 2 (Output) TIM3 Channel 2
GPIO_Pin_TypeDef sPWM_Motor2_IN2_PC1 ={0};         //H bridge EN2 signal motor 2 (Output) TIM3 Channel 2

//Digital outputs for direction Motor 3
GPIO_Pin_TypeDef sPWM_Motor3_IN1_PC3 ={0};        //H bridge IN1 signal motor 3 (Output) TIM3 Channel 3
GPIO_Pin_TypeDef sPWM_Motor3_IN2_PC0 ={0};        //H bridge IN2 signal motor 3 (Output) TIM3 Channel 3

//Digital outputs for direction Motor 4
GPIO_Pin_TypeDef sPWM_Motor4_IN1_PA10 ={0};       //H bridge EN1 signal motor 4 (Output) TIM3 Channel 4
GPIO_Pin_TypeDef sPWM_Motor4_IN2_PC4 ={0};        //H bridge EN2 signal motor 4 (Output) TIM3 Channel 4

//Digital outputs for direction Motor 5
GPIO_Pin_TypeDef sPWM_Motor5_IN1_PB5 ={0};        //H bridge IN1 signal motor 5(Output) TIM4 Channel 3
GPIO_Pin_TypeDef sPWM_Motor5_IN2_PB13 ={0};       //H bridge IN2 signal motor 5(Output) TIM4 Channel 3

//Digital outputs for direction Motor 6
GPIO_Pin_TypeDef sPWM_Motor6_IN1_PB10 ={0};       //H bridge EN1 signal motor 6 (Output) TIM4 Channel 4
GPIO_Pin_TypeDef sPWM_Motor6_IN2_PB15 ={0};       //H bridge EN2 signal motor 6 (Output) TIM4 Channel 4

//UART Comunication
GPIO_Pin_TypeDef sUART_Tx_PB6 = {0};              //Tx pin for UART1 communication
GPIO_Pin_TypeDef sUART_Rx_PB7 = {0};              //Rx pin for UART1 comunication


void GPIO_Init(void){  
	
				//******************************Configure PWM pins for each motor*****************************
        //TIM3 CHANNEL 1 (Motor 1)
        //Port B, Pin 4 as Alternate Function mode and Alternate function set as AF2 (TIM3 channel 1)
        sPWM_Motor1_Enable_PB4.Port = GPIO_PORT_B;
        sPWM_Motor1_Enable_PB4.Pin = GPIO_PIN_4;
        sPWM_Motor1_Enable_PB4.Mode = GPIO_MODE_AF_PP;
	      sPWM_Motor1_Enable_PB4.OutputType = GPIO_OUTPUT_PUSHPULL;
        sPWM_Motor1_Enable_PB4.Alternate = AF2;
        //Initialize Port B pin 4 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor1_Enable_PB4); 
	
				 //TIM3 CHANNEL 2 (Motor 2)
        //Port A, Pin 7 as Alternate Function mode and Alternate function set as AF2 (TIM3 channel 2)
        sPWM_Motor2_Enable_PA7.Port = GPIO_PORT_A;
        sPWM_Motor2_Enable_PA7.Pin = GPIO_PIN_7;
        sPWM_Motor2_Enable_PA7.Mode = GPIO_MODE_AF_PP;
				sPWM_Motor2_Enable_PA7.OutputType = GPIO_OUTPUT_PUSHPULL;
        sPWM_Motor2_Enable_PA7.Alternate = AF2;
        //Initialize Port A pin 7 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor2_Enable_PA7); 
	 
        //TIM3 CHANNEL 3 (Motor 3)
        //Port C, Pin 8 as Alternate Function mode and Alternate function set as AF2 (TIM3 channel 3)
        sPWM_Motor3_Enable_PC8.Port = GPIO_PORT_C;
        sPWM_Motor3_Enable_PC8.Pin = GPIO_PIN_8;
        sPWM_Motor3_Enable_PC8.Mode = GPIO_MODE_AF_PP;
				sPWM_Motor3_Enable_PC8.OutputType = GPIO_OUTPUT_PUSHPULL;
        sPWM_Motor3_Enable_PC8.Alternate = AF2;
        //Initialize Port C pin 8 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor3_Enable_PC8); 


				//TIM3 CHANNEL 4 (Motor 4)
        //Port C, Pin 9 as Alternate Function mode and Alternate function set as AF2 (TIM3 channel 4)
        sPWM_Motor4_Enable_PC9.Port = GPIO_PORT_C;
        sPWM_Motor4_Enable_PC9.Pin = GPIO_PIN_9;
        sPWM_Motor4_Enable_PC9.Mode = GPIO_MODE_AF_PP;
				sPWM_Motor4_Enable_PC9.OutputType = GPIO_OUTPUT_PUSHPULL;
        sPWM_Motor4_Enable_PC9.Alternate = AF2;
        //Initialize Port C pin 9 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor4_Enable_PC9); 

        //TIM4 CHANNEL 3 (Motor 5)
        //Port B, Pin 8 as Alternate Function mode and Alternate function set as AF2 (TIM4 channel 3)
        sPWM_Motor5_Enable_PB8.Port = GPIO_PORT_B;
        sPWM_Motor5_Enable_PB8.Pin = GPIO_PIN_8;
        sPWM_Motor5_Enable_PB8.Mode = GPIO_MODE_AF_PP;
				sPWM_Motor5_Enable_PB8.OutputType = GPIO_OUTPUT_PUSHPULL;
        sPWM_Motor5_Enable_PB8.Alternate = AF2;
        //Initialize Port B pin 8 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor5_Enable_PB8); 

				//TIM4 CHANNEL 4 (Motor 6)
        //Port B, Pin 9 as Alternate Function mode and Alternate function set as AF2 (TIM4 channel 4)
        sPWM_Motor6_Enable_PB9.Port = GPIO_PORT_B;
        sPWM_Motor6_Enable_PB9.Pin = GPIO_PIN_9;
        sPWM_Motor6_Enable_PB9.Mode = GPIO_MODE_AF_PP;
				sPWM_Motor6_Enable_PB9.OutputType = GPIO_OUTPUT_PUSHPULL;
        sPWM_Motor6_Enable_PB9.Alternate = AF2;
        //Initialize Port B pin 9 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor6_Enable_PB9); 
	
	
	      //******************************Configure PWM IN1 and IN2 for each motor pins******************
	
	      //*******************************************************
				//********************Motor 1****************************
				//*******************************************************
				//Motor 1 EN1 signal
        //Port C, Pin 10 as digital push-pull output
        sPWM_Motor1_IN1_PC10.Port = GPIO_PORT_C;
        sPWM_Motor1_IN1_PC10.Pin = GPIO_PIN_10;
        sPWM_Motor1_IN1_PC10.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor1_IN1_PC10.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 10 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor1_IN1_PC10); 
				
				//Motor 1 EN2 signal
        //Port C, Pin 11 as digital push-pull output
        sPWM_Motor1_IN2_PC11.Port = GPIO_PORT_C;
        sPWM_Motor1_IN2_PC11.Pin = GPIO_PIN_11;
        sPWM_Motor1_IN2_PC11.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor1_IN2_PC11.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 11 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor1_IN2_PC11); 
				
				
				//*******************************************************
				//********************Motor 2****************************
				//*******************************************************
				//Motor 2 EN1 signal
        //Port C, Pin 2 as digital push-pull output
        sPWM_Motor2_IN1_PC2.Port = GPIO_PORT_C;
        sPWM_Motor2_IN1_PC2.Pin = GPIO_PIN_2;
        sPWM_Motor2_IN1_PC2.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor2_IN1_PC2.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 2 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor2_IN1_PC2); 
				
				//Motor 2 EN2 signal
        //Port C, Pin 1 as digital push-pull output
        sPWM_Motor2_IN2_PC1.Port = GPIO_PORT_C;
        sPWM_Motor2_IN2_PC1.Pin = GPIO_PIN_1;
        sPWM_Motor2_IN2_PC1.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor2_IN2_PC1.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 1 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor2_IN2_PC1); 
				
				
				//*******************************************************
				//********************Motor 3****************************
				//*******************************************************
				//Motor 3 EN1 signal
        //Port C, Pin 3 as digital push-pull output
        sPWM_Motor3_IN1_PC3.Port = GPIO_PORT_C;
        sPWM_Motor3_IN1_PC3.Pin = GPIO_PIN_3;
        sPWM_Motor3_IN1_PC3.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor3_IN1_PC3.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 3 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor3_IN1_PC3); 
				
				//Motor 3 EN2 signal
        //Port C, Pin 0 as digital push-pull output
        sPWM_Motor3_IN2_PC0.Port = GPIO_PORT_C;
        sPWM_Motor3_IN2_PC0.Pin = GPIO_PIN_0;
        sPWM_Motor3_IN2_PC0.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor3_IN2_PC0.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 0 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor3_IN2_PC0); 
				
				
				//*******************************************************
				//********************Motor 4****************************
				//*******************************************************
				//Motor 4 EN1 signal
        //Port A, Pin 10 as digital push-pull output
        sPWM_Motor4_IN1_PA10.Port = GPIO_PORT_A;
        sPWM_Motor4_IN1_PA10.Pin = GPIO_PIN_10;
        sPWM_Motor4_IN1_PA10.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor4_IN1_PA10.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port A pin 10 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor4_IN1_PA10); 
				
				//Motor 4 EN2 signal
        //Port C, Pin 4 as digital push-pull output
        sPWM_Motor4_IN2_PC4.Port = GPIO_PORT_C;
        sPWM_Motor4_IN2_PC4.Pin = GPIO_PIN_4;
        sPWM_Motor4_IN2_PC4.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor4_IN2_PC4.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port C pin 4 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor4_IN2_PC4); 
				
				
				//*******************************************************
				//********************Motor 5****************************
				//*******************************************************
				//Motor 5 EN1 signal
        //Port B, Pin 5 as digital push-pull output
        sPWM_Motor5_IN1_PB5.Port = GPIO_PORT_B;
        sPWM_Motor5_IN1_PB5.Pin = GPIO_PIN_5;
        sPWM_Motor5_IN1_PB5.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor5_IN1_PB5.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port B pin 5 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor5_IN1_PB5); 
				
				//Motor 5 EN2 signal
        //Port B, Pin 13 as digital push-pull output
        sPWM_Motor5_IN2_PB13.Port = GPIO_PORT_B;
        sPWM_Motor5_IN2_PB13.Pin = GPIO_PIN_13;
        sPWM_Motor5_IN2_PB13.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor5_IN2_PB13.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port B pin 13 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor5_IN2_PB13); 
				
				//******************************************************
				//*******************Motor 6****************************
				//******************************************************
				//Motor 6 EN1 signa
        //Port B, Pin 10 as digital push-pull output
        sPWM_Motor6_IN1_PB10.Port = GPIO_PORT_B;
        sPWM_Motor6_IN1_PB10.Pin = GPIO_PIN_10;
        sPWM_Motor6_IN1_PB10.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor6_IN1_PB10.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port B pin 10 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor6_IN1_PB10); 
				
				//Motor 6 EN2 signal
        //Port B, Pin 15 as digital push-pull output
        sPWM_Motor6_IN2_PB15.Port = GPIO_PORT_B;
        sPWM_Motor6_IN2_PB15.Pin = GPIO_PIN_15;
        sPWM_Motor6_IN2_PB15.Mode = GPIO_MODE_OUTPUT_PP;
	      sPWM_Motor6_IN2_PB15.OutputType = GPIO_OUTPUT_PUSHPULL;
        //Initialize Port B pin 15 using HAL function
        HAL_GPIO_Pin_Init(&sPWM_Motor6_IN2_PB15);  
			
			  //******************************************************
			  //************Configure pins for UART transmition*******
				//******************************************************
				
				//UART1 Tx
        //Port B, Pin 6 as alternate function 7
        sUART_Tx_PB6.Port = GPIO_PORT_B;
        sUART_Tx_PB6.Pin = GPIO_PIN_6;
        sUART_Tx_PB6.Mode = GPIO_MODE_AF_PP;
				sUART_Tx_PB6.OutputType = GPIO_OUTPUT_PUSHPULL;
        sUART_Tx_PB6.Alternate = AF7;
        //Initialize Port B pin 6 using HAL function
        HAL_GPIO_Pin_Init(&sUART_Tx_PB6); 
				
				//UART1 Rx
        //Port B, Pin 7 as alternate function 7
        sUART_Rx_PB7.Port = GPIO_PORT_B;
        sUART_Rx_PB7.Pin = GPIO_PIN_7;
				sUART_Rx_PB7.Mode = GPIO_MODE_INPUT;
        sUART_Rx_PB7.Mode = GPIO_MODE_AF_PP;
        sUART_Rx_PB7.Alternate = AF7;
        //Initialize Port B pin 6 using HAL function
        HAL_GPIO_Pin_Init(&sUART_Rx_PB7); 
				
}
