/****************************************************************************
* @Filename  : system.h
* @Notes     : Clock (84 MHz from HSI+PLL), 1 ms SysTick time base and
*              independent hardware watchdog (IWDG). Register level, CMSIS.
*****************************************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H

#define IWDG_ENABLE 1   /* set to 0 while single-stepping if preferred */

void Clock_Init(void);                 /* unchanged from v1.3.2          */
void SysTick_Init_1ms(void);
unsigned long Millis(void);
void IWDG_Init_100ms(void);
void IWDG_Kick(void);

#endif
