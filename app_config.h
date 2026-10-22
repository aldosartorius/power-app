/****************************************************************************
* @Title     : Armdroid 2001 power-app - application configuration
* @Filename  : app_config.h
* @Author    : Aldo R. Sartorius Castellanos
* @Version   : 2.0.0
* Notes      : Pure configuration header (no HAL dependency). ISO C90.
*****************************************************************************/
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/* ---------------- Actuators ---------------------------------------------- */
#define MOTOR_COUNT              6       /* H-bridges driven by this MCU       */
#define MOTOR_CMD_MAX            10000   /* +/-10000 <=> duty +/-1.0 (100 %)   */

/* ---------------- PC link (USART2, PA2/PA3, 115200 bps) ------------------ */
#define PC_PWM_CHANNELS          5       /* motors 1..5 commanded by the PC    */
#define PC_WATCHDOG_MS           100u     /* 10 x 10 ms: no valid frame -> PWM 0 */

/* ---------------- Hand held (USART1, PB6/PB7, 115200 bps, 1 char) -------- */
#define HANDHELD_SPEED_CMD       7000    /* 0.70 duty, same as v1.x            */
#define HANDHELD_PULSE_MS        100u    /* motor on-time per received char    */
#define HANDHELD_OVERRIDE_MS     500u    /* hand held keeps priority this long */

#endif
