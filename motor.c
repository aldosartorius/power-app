#include "motor.h"
#include "stm32f4xx_hal_gpio_cfg.h"
#include "stm32f4xx_hal_tim_cfg.h"

typedef struct {
    GPIO_Pin_TypeDef     *in1;
    GPIO_Pin_TypeDef     *in2;
    TIM_Base_InitTypeDef *tim;
    TIM_OC_InitTypeDef   *oc;
} MotorHw_t;

static const MotorHw_t kMotor[MOTOR_COUNT] = {
    { &sPWM_Motor1_IN1_PC10, &sPWM_Motor1_IN2_PC11, &sTIMER3, &sOC_TIMER3_CHANNEL_1_PWM_Motor1 },
    { &sPWM_Motor2_IN1_PC2,  &sPWM_Motor2_IN2_PC1,  &sTIMER3, &sOC_TIMER3_CHANNEL_2_PWM_Motor2 },
    { &sPWM_Motor3_IN1_PC3,  &sPWM_Motor3_IN2_PC0,  &sTIMER3, &sOC_TIMER3_CHANNEL_3_PWM_Motor3 },
    { &sPWM_Motor4_IN1_PA10, &sPWM_Motor4_IN2_PC4,  &sTIMER3, &sOC_TIMER3_CHANNEL_4_PWM_Motor4 },
    { &sPWM_Motor5_IN1_PB5,  &sPWM_Motor5_IN2_PB13, &sTIMER4, &sOC_TIMER4_CHANNEL_3_PWM_Motor5 },
    { &sPWM_Motor6_IN1_PB10, &sPWM_Motor6_IN2_PB15, &sTIMER4, &sOC_TIMER4_CHANNEL_4_PWM_Motor6 }
};

static const signed char kDirSign[MOTOR_COUNT] = MOTOR_DIR_SIGN_INIT;

static short s_applied[MOTOR_COUNT];   /* PHYSICAL commands (after kDirSign) */

static void write_motor(unsigned int i, short cmd)
{
    const MotorHw_t *m = &kMotor[i];
    short prev = s_applied[i];
    long  mag  = (cmd < 0) ? -(long)cmd : (long)cmd;

    /* Direction change: drop duty to 0 before swapping IN1/IN2 so the
       bridge never sees full duty with a half-updated direction. */
    if ((prev > 0 && cmd <= 0) || (prev < 0 && cmd >= 0)) {
        HAL_TIM_PWM_Duty(m->tim, m->oc, (double)0.0);
    }

    if (cmd > 0) {
        HAL_GPIO_Pin_Write(m->in2, GPIO_PIN_RESET);
        HAL_GPIO_Pin_Write(m->in1, GPIO_PIN_SET);
    } else if (cmd < 0) {
        HAL_GPIO_Pin_Write(m->in1, GPIO_PIN_RESET);
        HAL_GPIO_Pin_Write(m->in2, GPIO_PIN_SET);
    } else {
        HAL_GPIO_Pin_Write(m->in1, GPIO_PIN_RESET);
        HAL_GPIO_Pin_Write(m->in2, GPIO_PIN_RESET);
    }

    HAL_TIM_PWM_Duty(m->tim, m->oc, (double)mag / (double)MOTOR_CMD_MAX);
    s_applied[i] = cmd;
}

void Motor_AllOff(void)
{
    unsigned int i;
    for (i = 0u; i < MOTOR_COUNT; i++) {
        HAL_TIM_PWM_Duty(kMotor[i].tim, kMotor[i].oc, (double)0.0);
        HAL_GPIO_Pin_Write(kMotor[i].in1, GPIO_PIN_RESET);
        HAL_GPIO_Pin_Write(kMotor[i].in2, GPIO_PIN_RESET);
        s_applied[i] = 0;
    }
}

void Motor_Init(void)
{
    Motor_AllOff();
}

/* cmd[] is in the kinematic convention; kDirSign maps it to the bridge */
void Motor_Apply(const short cmd[MOTOR_COUNT])
{
    unsigned int i;
    short        phys;
    for (i = 0u; i < MOTOR_COUNT; i++) {
        phys = (kDirSign[i] < 0) ? (short)(-cmd[i]) : cmd[i];
        if (phys != s_applied[i]) {
            write_motor(i, phys);
        }
    }
}
