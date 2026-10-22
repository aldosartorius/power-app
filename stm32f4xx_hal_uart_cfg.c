#include "stm32f4xx_hal_uart_cfg.h"     /*hal_uart header*/

UART_InitTypeDef UART1 = {0};   /* Hand held  - PB6/PB7 - APB2 (84 MHz) */
UART_InitTypeDef UART2 = {0};   /* PC/Simulink - PA2/PA3 - APB1 (42 MHz) */

void UART_Init(void){

	/* USART1: hand held, 1-char protocol */
	UART1.UartNumber = UART_1;
	UART1.Mode = UART_MODE_FULL_DUPLEX;
	UART1.OverSampling = UART_OVERSAMPLING_8;
	UART1.BaudRate = 0x5B2;   /* PCLK2 84 MHz, OVER8: 91 + 2/8 -> 115068 bps (-0.11 %) */
	UART1.InterruptEnable = UART_INTERRUPT_ON_RX;
	HAL_UART_Init(&UART1);

	/* USART2: PC, 14-byte PWM frame.
	   USART2 hangs from APB1 = 42 MHz, so BRR is NOT the USART1 value. */
	UART2.UartNumber = UART_2;
	UART2.Mode = UART_MODE_FULL_DUPLEX;
	UART2.OverSampling = UART_OVERSAMPLING_8;
	UART2.BaudRate = 0x2D5;   /* PCLK1 42 MHz, OVER8: 45 + 5/8 -> 115068 bps (-0.11 %) */
	UART2.InterruptEnable = UART_INTERRUPT_ON_RX;
	HAL_UART_Init(&UART2);
}
