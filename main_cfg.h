#include "stm32f4xx.h"              // Device header

//Local function prototypes
extern void PWM_Disabled(void);
extern void Clock_Init(void);
extern void Motor1_Fordward(void);        //Move motor 1 fordward in open loop
extern void Motor1_Backward(void);        //Move motor 1 backward in open loop
extern void Motor2_Fordward(void);        //Move motor 2 fordward in open loop
extern void Motor2_Backward(void);        //Move motor 2 backward in open loop
extern void Motor3_Fordward(void);        //Move motor 3 fordward in open loop
extern void Motor3_Backward(void);        //Move motor 3 backward in open loop
extern void Motor4_Fordward(void);        //Move motor 4 fordward in open loop
extern void Motor4_Backward(void);        //Move motor 4 backward in open loop
extern void Motor5_Fordward(void);        //Move motor 5 fordward in open loop
extern void Motor5_Backward(void);        //Move motor 5 backward in open loop
extern void Motor6_Fordward(void);        //Move motor 6 fordward in open loop
extern void Motor6_Backward(void);        //Move motor 6 backward in open loop
extern void Robot_Move_Teach_Pendant(void);
extern void USART1_IRQHandler(void);

void ConfigureSystemClockTo84MHz(void);

//Global variables
extern volatile char char_HAND_HELD;              //Char received for hand held
extern uint8_t Uart_Receive_Flag;                //Flag for data receive
extern double speed;                      //This variable set duty cycle in motors for open loop
extern uint16_t MotorOnTimeMiliseconds;   // Time that the pwm is active in open loop (miliseconds)

