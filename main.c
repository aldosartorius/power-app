/****************************************************************************
* @Title                 :   Armdroid Robot PWM Test
* @Filename              :   Armdroid_Robot_PWM_Test.c
* @Author                :   Aldo R. Sartorius Castellanos
* Origin Date            :   16/04/2021
* @Version               :   1.1.0
* Compiler               :   Keil
* Target                 :   STM32F401RE401 Microcontroller
* Notes                  :   None
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  16/04/21   1.0.0   Aldo Sartorius   PWM channels add.
*  16/04/21   1.1.0   Aldo Sartorius   Direction pines add
*  20/04/21   1.2.0   Aldo Sartorius   add UART non blocking receive functionality for Hand held
*  06/09/23   1.2.1   Aldo Sartorius   add Clock_Init() function to operate at 84 Mhz
*  17/10/23   1.3.0   Aldo Sartorius   change static volatile char char_HAND_HELD to volatile char char_HAND_HELD to operate without debbugger
*  01/11/23   1.3.1   Aldo Sartorius   Modify Clock_Init() function to operate at 84 Mhz correctly and verified with osciloscope and UART Transmition 
*  21/12/23   1.3.2   Aldo Sartorius   Modify Motor5_Fordward() and Motor5_Backward() functions in order to rotate the wrist
*****************************************************************************/

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal_gpio_cfg.h"     //hal_gpio_cfg header
#include "stm32f4xx_hal_tim_cfg.h"      //hal_tim_cfg header*/
#include "stm32f4xx_hal_uart_cfg.h"     //hal_uart_cfg header*/
#include "main_cfg.h"              // Device header

//static uint8_t  char_to_transmit= 'A';

int main(void){
	
    Clock_Init();    //Function for clock initializacion at 84 Mhz
		GPIO_Init();     //Function for GPIO ports initializacion 
		TIMERS_Init();   //Function for timer initializacion
	  OC_PWM_Init();   //Function for Output Compare PWM initializacion
	  PWM_Disabled();  //This function initialize all bridges disables and duty cycle at 0%
	  UART_Init();     //Enable UART communication
		
		while(1){
			
			Robot_Move_Teach_Pendant();
			
				}
		
}

void PWM_Disabled(void){
		//Motor 1 initial direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor1_IN1_PC10, GPIO_PIN_RESET);
		HAL_GPIO_Pin_Write(&sPWM_Motor1_IN2_PC11, GPIO_PIN_RESET);
	
		//Motor 2 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor2_IN1_PC2, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor2_IN2_PC1, GPIO_PIN_RESET);

    //Motor 3 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor3_IN1_PC3, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor3_IN2_PC0, GPIO_PIN_RESET);

    //Motor 4 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor4_IN1_PA10, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor4_IN2_PC4, GPIO_PIN_RESET);

    //Motor 5 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor5_IN1_PB5, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor5_IN2_PB13, GPIO_PIN_RESET);
		
		//Motor 6 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor6_IN1_PB10, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor6_IN2_PB15, GPIO_PIN_RESET);
	
		//Set duty cycle en each PWM signal
		//Set duty cycle en each PWM signal
		HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_1_PWM_Motor1, (double)0.00);
		HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_2_PWM_Motor2, (double)0.00);
		HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_3_PWM_Motor3, (double)0.00);
		HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4, (double)0.00);
		HAL_TIM_PWM_Duty(&sTIMER4, &sOC_TIMER4_CHANNEL_3_PWM_Motor5, (double)0.00);
		HAL_TIM_PWM_Duty(&sTIMER4, &sOC_TIMER4_CHANNEL_4_PWM_Motor6, (double)0.00);
			
}

//Interrupt Hanspeed
void USART1_IRQHandler(void){
		
		char_HAND_HELD = HAL_UART_Rx(&UART1);
	  Uart_Receive_Flag = 1;
	  //Robot_Move_Teach_Pendant();

} 

void Motor1_Fordward(void){

	  //Motor 1  direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor1_IN1_PC10, GPIO_PIN_SET);
		HAL_GPIO_Pin_Write(&sPWM_Motor1_IN2_PC11, GPIO_PIN_RESET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_1_PWM_Motor1, (double)speed);
}

void Motor1_Backward(void){

	  //Motor 1  direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor1_IN1_PC10, GPIO_PIN_RESET);
		HAL_GPIO_Pin_Write(&sPWM_Motor1_IN2_PC11, GPIO_PIN_SET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_1_PWM_Motor1, (double)speed);
}

void Motor2_Fordward(void){

	  //Motor 2 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor2_IN1_PC2, GPIO_PIN_SET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor2_IN2_PC1, GPIO_PIN_RESET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_2_PWM_Motor2, (double)speed);
}

void Motor2_Backward(void){

	  //Motor 2 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor2_IN1_PC2, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor2_IN2_PC1, GPIO_PIN_SET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_2_PWM_Motor2, (double)speed);
}


void Motor3_Fordward(void){

	  //Motor 3 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor3_IN1_PC3, GPIO_PIN_SET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor3_IN2_PC0, GPIO_PIN_RESET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_3_PWM_Motor3, (double)speed);
}

void Motor3_Backward(void){

	   //Motor 3 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor3_IN1_PC3, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor3_IN2_PC0, GPIO_PIN_SET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_3_PWM_Motor3, (double)speed);
}


void Motor4_Fordward(void){

	  //Motor 4 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor4_IN1_PA10, GPIO_PIN_SET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor4_IN2_PC4, GPIO_PIN_RESET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4, (double)speed);
}

void Motor4_Backward(void){

	  //Motor 4 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor4_IN1_PA10, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor4_IN2_PC4, GPIO_PIN_SET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4, (double)speed);
}

void Motor5_Fordward(void){
	
	  //Motor 4 direction Backward
		//HAL_GPIO_Pin_Write(&sPWM_Motor4_IN1_PA10, GPIO_PIN_RESET);
	  //HAL_GPIO_Pin_Write(&sPWM_Motor4_IN2_PC4, GPIO_PIN_SET);
	
	  //Motor 5 direction fordward
	  HAL_GPIO_Pin_Write(&sPWM_Motor5_IN1_PB5, GPIO_PIN_SET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor5_IN2_PB13, GPIO_PIN_RESET);
	 
	  //Set duty cycle
  	//HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4, (double)speed);

	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER4, &sOC_TIMER4_CHANNEL_3_PWM_Motor5, (double)speed);
	
	
}

void Motor5_Backward(void){
	
	 //Motor 4 direction fordward
	 // HAL_GPIO_Pin_Write(&sPWM_Motor4_IN1_PA10, GPIO_PIN_SET);
	 //HAL_GPIO_Pin_Write(&sPWM_Motor4_IN2_PC4, GPIO_PIN_RESET);
	
	  //Motor 5 direction backward
	  HAL_GPIO_Pin_Write(&sPWM_Motor5_IN1_PB5, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor5_IN2_PB13, GPIO_PIN_SET);
	 
	  //Set duty cycle
		//HAL_TIM_PWM_Duty(&sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4, (double)speed);

	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER4, &sOC_TIMER4_CHANNEL_3_PWM_Motor5, (double)speed);
	
}

void Motor6_Fordward(void){

	 //Motor 6 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor6_IN1_PB10, GPIO_PIN_SET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor6_IN2_PB15, GPIO_PIN_RESET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER4, &sOC_TIMER4_CHANNEL_4_PWM_Motor6, (double)speed);
}

void Motor6_Backward(void){

	  //Motor 6 direction 
	  HAL_GPIO_Pin_Write(&sPWM_Motor6_IN1_PB10, GPIO_PIN_RESET);
	  HAL_GPIO_Pin_Write(&sPWM_Motor6_IN2_PB15, GPIO_PIN_SET);
	 
	  //Set duty cycle
  	HAL_TIM_PWM_Duty(&sTIMER4, &sOC_TIMER4_CHANNEL_4_PWM_Motor6, (double)speed);
}


void Robot_Move_Teach_Pendant(void){
	
	
	if(Uart_Receive_Flag == 1){
				
		Uart_Receive_Flag = 0;
		switch (char_HAND_HELD){
		
			case 'A':
					Motor1_Fordward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'B':
					Motor1_Backward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'C':
					Motor2_Fordward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'D':
					Motor2_Backward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'E':
					Motor3_Fordward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'F':
					Motor3_Backward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'G':
					Motor4_Fordward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'H':
					Motor4_Backward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'I':
					Motor5_Fordward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'J':
					Motor5_Backward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'K':
					Motor6_Fordward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			case 'L':
					Motor6_Backward();
					HAL_TIM_msDelay(&sTIMER2, MotorOnTimeMiliseconds);
					PWM_Disabled();
					char_HAND_HELD = ' ';
		      break;
			
			default:
					char_HAND_HELD = ' ';
		      break;
		}
	}
}

void Clock_Init(void){

			// Conf clock : 84 MHz using HSI 16MHz crystal w/ PLL M= 16, N= 336, P=4, AHB preescaler = 1, APB1 preescaler = 2, APB2 PRESSCALES =1 */

			RCC->CR |=  ((uint32_t)0x0000001 << 0);   //enable HSI clock (uint32_t)0x0000001 (CR:bit 0)
			while( !(RCC->CR & (0x1<<1)));            //wait for the HSIREADY flag  (CR:bit 1)
	
			RCC->APB1ENR |= (1 << 28);      			    //Power interface clock enable (APB1ENB:bit 28)

			RCC->CFGR |= (0 << 7);      			    		//set prescale AHB1 = HCLK (CFGR:bits 7:4) sin preescaler
			RCC->CFGR |= (0x4 << 10);                 //set APB low speed prescaler to /2 (APB1) (CFGR:bits 12:10)  42 Mhz
      RCC->CFGR |= (0 << 15);                   //set ABP high speed prescaper to /1 (ABP2) (CFGR:bits 15:13) 84 Mhz

			//Set M, N and P dividers
			RCC->PLLCFGR &= (~(0x3FU) << 0);
			RCC->PLLCFGR |=  (0x10U << 0);                     //set PLLM division factor by 16d (vco input frecuency 1 MHz) (PLLCFGR:bits 0:5)
			
	    RCC->PLLCFGR &= ~((0x1FFU <<6));
	    RCC->PLLCFGR |= (0x150U <<6);              //set PLLN multiplication factor by 336d (vco output frecuency 336 MHz) (PLLCFGR:bits 6:14)
			
			RCC->PLLCFGR &= ~(0x3U <<16);
			RCC->PLLCFGR |= (0x01 <<16); 	            //set PLLP main PLL division factor 4 (PLLCFGR:bits 16:17)

			//Enable PLL 
			RCC->CR |= (0x1 <<24);                    //enable the PLL (CR:bits 24)
			while( !(RCC->CR & (0x1 << 25)));         //wait for the PLLRDY flag
	
			FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10 ) | (2 << 0);  //Define latency

			
			//Select PLL as system clock source
			RCC->CFGR &= ~(3U << 0);                  //(CFG:bits 0:1)
			RCC->CFGR |= (0x2 << 0);                  // PLL as a system clock (CFG:bits 0:1)


			while( !(RCC->CFGR & (0x2 << 2)));        //wait for system clock switch status to PLL as used as system clock source (CFG:bits 2:3)
			SystemCoreClockUpdate();
}


