/****************************************************************************
* @Filename  : arbiter.h
* @Notes     : Command arbitration between the hand held (manual override)
*              and the PC (Simulink), plus the PC communication watchdog.
*              Pure logic, no HAL dependency. ISO C90.
*
*  Priority rules
*   1. Hand held has priority. Any valid character ('A'..'L') takes control
*      for HANDHELD_OVERRIDE_MS; the motor runs for HANDHELD_PULSE_MS per
*      character (same jog behaviour as v1.x, but non-blocking).
*   2. Outside the override window the PC commands motors 1..5, as long as
*      a valid frame arrived within the last PC_WATCHDOG_MS.
*   3. Otherwise every output is 0 (fail-safe).
*****************************************************************************/
#ifndef ARBITER_H
#define ARBITER_H

#include "app_config.h"

typedef enum {
    SRC_NONE = 0,        /* fail-safe: all motors stopped */
    SRC_PC,
    SRC_HANDHELD
} CmdSource_t;

typedef struct {
    short          pc_cmd[PC_PWM_CHANNELS];
    unsigned short pc_age_ms;            /* time since last valid PC frame */
    short          hh_cmd[MOTOR_COUNT];
    unsigned short hh_pulse_ms;          /* remaining jog on-time          */
    unsigned short hh_override_ms;       /* remaining priority window      */
    unsigned long  watchdog_trips;       /* PC_SOURCE -> NONE transitions  */
    CmdSource_t    source;
    short          out[MOTOR_COUNT];     /* commands to apply to bridges   */
} Arbiter_t;

void Arbiter_Init(Arbiter_t *a);
void Arbiter_OnHandheldChar(Arbiter_t *a, unsigned char c);
void Arbiter_OnPcFrame(Arbiter_t *a, const short cmd[PC_PWM_CHANNELS]);
void Arbiter_Tick1ms(Arbiter_t *a);   /* call once per elapsed millisecond */

#endif
