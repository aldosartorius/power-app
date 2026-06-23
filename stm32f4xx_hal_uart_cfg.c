#include "stm32f4xx_hal_uart_cfg.h"     /*hal_uart header*/


//Initialize GPIO structures for PWM Outputs
UART_InitTypeDef UART1 = {0};


void UART_Init(void){  
	
	// Populate UART_InitTypeDef struct
	UART1.UartNumber = UART_1;
	UART1.Mode = UART_MODE_FULL_DUPLEX;
	UART1.OverSampling = UART_OVERSAMPLING_8;
	UART1.BaudRate = 0x5B2;   //Clock 84 MHz, baud rate at 115200 bps, oversamplig 8
  UART1.InterruptEnable = UART_INTERRUPT_ON_RX;    //For Non blocking UART at recive data
	HAL_UART_Init(&UART1);			
}
