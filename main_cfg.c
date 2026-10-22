#include "main_cfg.h"              // cfg header

//Global variables definition
volatile char char_HAND_HELD = ' ';              //Char received for hand held
uint8_t Uart_Receive_Flag = 0;                //Flag for data receive
double speed = 0.7;                      //This variable set duty cycle in motors for open loop
uint16_t MotorOnTimeMiliseconds =100;   // Time that the pwm is active in open loop (miliseconds)


