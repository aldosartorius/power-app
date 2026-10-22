/****************************************************************************
* @Filename  : motor.h
* @Notes     : H-bridge driver on top of HAL_GPIO / HAL_TIM. ISO C90.
*              cmd > 0 : IN1=1 IN2=0 (forward)   duty = cmd/10000
*              cmd < 0 : IN1=0 IN2=1 (backward)  duty = -cmd/10000
*              cmd = 0 : IN1=0 IN2=0 (coast), duty 0 - same as v1.x stop
*****************************************************************************/
#ifndef MOTOR_H
#define MOTOR_H

#include "app_config.h"

void Motor_Init(void);                         /* all bridges off        */
void Motor_Apply(const short cmd[MOTOR_COUNT]);/* writes only on change  */
void Motor_AllOff(void);

#endif
