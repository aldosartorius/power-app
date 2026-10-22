/****************************************************************************
* @Title                 :   Armdroid 2001 power-app
* @Filename              :   main.c
* @Author                :   Aldo R. Sartorius Castellanos
* Origin Date            :   16/04/2021
* @Version               :   2.0.0
* Compiler               :   Keil
* Target                 :   STM32F401RE (power MCU)
* Notes                  :   Uses HAL_STM32F401 (HAL_GPIO, HAL_TIM, HAL_UART)
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description
*  16/04/21   1.0.0   Aldo Sartorius   PWM channels add.
*  16/04/21   1.1.0   Aldo Sartorius   Direction pines add
*  20/04/21   1.2.0   Aldo Sartorius   add UART non blocking receive functionality for Hand held
*  06/09/23   1.2.1   Aldo Sartorius   add Clock_Init() function to operate at 84 Mhz
*  17/10/23   1.3.0   Aldo Sartorius   char_HAND_HELD no longer static (operate without debugger)
*  01/11/23   1.3.1   Aldo Sartorius   Clock_Init() verified at 84 MHz (oscilloscope + UART)
*  21/12/23   1.3.2   Aldo Sartorius   Motor5 functions rotate the wrist (coupled M4/M5)
*  22/10/26   2.0.0   Aldo Sartorius   PC PWM frame on USART2 (14 B, CRC-8/SMBUS),
*                                      hand held manual override, 30 ms comm watchdog,
*                                      non-blocking jog, IWDG, modular structure
*****************************************************************************/

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio_cfg.h"
#include "stm32f4xx_hal_tim_cfg.h"
#include "stm32f4xx_hal_uart_cfg.h"
#include "system.h"
#include "ringbuf.h"
#include "pc_frame.h"
#include "arbiter.h"
#include "motor.h"

static RingBuf_t       g_rxHandheld;   /* USART1 ISR -> main loop */
static RingBuf_t       g_rxPc;         /* USART2 ISR -> main loop */
static PcFrameParser_t g_pcParser;
static Arbiter_t       g_arbiter;

int main(void){

    unsigned long last_ms;
    unsigned char byte;

    Clock_Init();          /* 84 MHz                                */
    GPIO_Init();
    TIMERS_Init();
    OC_PWM_Init();
    Motor_Init();          /* bridges off, duty 0 %                 */

    RingBuf_Init(&g_rxHandheld);
    RingBuf_Init(&g_rxPc);
    PcFrame_Init(&g_pcParser);
    Arbiter_Init(&g_arbiter);

    SysTick_Init_1ms();
    UART_Init();           /* RX interrupts start filling the FIFOs */
    IWDG_Init_100ms();

    last_ms = Millis();

    while(1){

        /* 1. Hand held characters (manual override) */
        while (RingBuf_Get(&g_rxHandheld, &byte)) {
            Arbiter_OnHandheldChar(&g_arbiter, byte);
        }

        /* 2. PC frames */
        while (RingBuf_Get(&g_rxPc, &byte)) {
            if (PcFrame_Feed(&g_pcParser, byte)) {
                Arbiter_OnPcFrame(&g_arbiter, g_pcParser.cmd);
            }
        }

        /* 3. Time base: watchdog and jog timers, catching up if needed */
        while (last_ms != Millis()) {
            last_ms++;
            Arbiter_Tick1ms(&g_arbiter);
        }

        /* 4. Outputs */
        Motor_Apply(g_arbiter.out);

        IWDG_Kick();
    }
}

/* Hand held - USART1 */
void USART1_IRQHandler(void){
    RingBuf_Put(&g_rxHandheld, (unsigned char)HAL_UART_Rx(&UART1));
}

/* PC / Simulink - USART2 */
void USART2_IRQHandler(void){
    RingBuf_Put(&g_rxPc, (unsigned char)HAL_UART_Rx(&UART2));
}
