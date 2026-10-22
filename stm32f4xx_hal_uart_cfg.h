#include "stm32f4xx_hal_uart.h"

#ifndef STM32F4XX_HAL_UART__CFG_H__
#define STM32F4XX_HAL_UART__CFG_H__

void UART_Init(void);

extern UART_InitTypeDef UART1;   /* hand held */
extern UART_InitTypeDef UART2;   /* PC        */

#endif
