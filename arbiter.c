#include "arbiter.h"

static void clear(short *v, unsigned int n)
{
    unsigned int i;
    for (i = 0u; i < n; i++) {
        v[i] = 0;
    }
}

static void update_outputs(Arbiter_t *a)
{
    unsigned int i;
    CmdSource_t  prev = a->source;

    if (a->hh_override_ms > 0u) {
        a->source = SRC_HANDHELD;
        for (i = 0u; i < MOTOR_COUNT; i++) {
            a->out[i] = (a->hh_pulse_ms > 0u) ? a->hh_cmd[i] : 0;
        }
    } else if (a->pc_age_ms < PC_WATCHDOG_MS) {
        a->source = SRC_PC;
        for (i = 0u; i < MOTOR_COUNT; i++) {
            a->out[i] = (i < PC_PWM_CHANNELS) ? a->pc_cmd[i] : 0;
        }
    } else {
        a->source = SRC_NONE;
        clear(a->out, MOTOR_COUNT);
    }

    if (prev == SRC_PC && a->source == SRC_NONE) {
        a->watchdog_trips++;
    }
}

void Arbiter_Init(Arbiter_t *a)
{
    clear(a->pc_cmd, PC_PWM_CHANNELS);
    clear(a->hh_cmd, MOTOR_COUNT);
    clear(a->out, MOTOR_COUNT);
    a->pc_age_ms = PC_WATCHDOG_MS;        /* start in fail-safe */
    a->hh_pulse_ms = 0u;
    a->hh_override_ms = 0u;
    a->watchdog_trips = 0ul;
    a->source = SRC_NONE;
}

/* Legacy v1.x character map. The table below is the PHYSICAL motion of
   v1.x (same as the paper version); it is multiplied by kDirSign so the
   hand held moves the robot exactly as before after motor.c applies the
   kinematic sign convention. 'I'/'J' keep the coupled wrist motion
   (motor 4 physically opposite to motor 5). */
static const signed char kDirSign[MOTOR_COUNT] = MOTOR_DIR_SIGN_INIT;

void Arbiter_OnHandheldChar(Arbiter_t *a, unsigned char c)
{
    const short s = HANDHELD_SPEED_CMD;
    short cmd[MOTOR_COUNT];

    clear(cmd, MOTOR_COUNT);
    switch (c) {
    case 'A': cmd[0] =  s;               break;
    case 'B': cmd[0] = -s;               break;
    case 'C': cmd[1] =  s;               break;
    case 'D': cmd[1] = -s;               break;
    case 'E': cmd[2] =  s;               break;
    case 'F': cmd[2] = -s;               break;
    case 'G': cmd[3] =  s;               break;
    case 'H': cmd[3] = -s;               break;
    case 'I': cmd[3] = -s; cmd[4] =  s;  break;
    case 'J': cmd[3] =  s; cmd[4] = -s;  break;
    case 'K': cmd[5] =  s;               break;
    case 'L': cmd[5] = -s;               break;
    default:  return;                    /* ignore unknown bytes */
    }

    {
        unsigned int i;
        for (i = 0u; i < MOTOR_COUNT; i++) {
            a->hh_cmd[i] = (kDirSign[i] < 0) ? (short)(-cmd[i]) : cmd[i];
        }
    }
    a->hh_pulse_ms = HANDHELD_PULSE_MS;     /* re-trigger = continuous jog */
    a->hh_override_ms = HANDHELD_OVERRIDE_MS;
    update_outputs(a);
}

void Arbiter_OnPcFrame(Arbiter_t *a, const short cmd[PC_PWM_CHANNELS])
{
    unsigned int i;
    for (i = 0u; i < PC_PWM_CHANNELS; i++) {
        a->pc_cmd[i] = cmd[i];
    }
    a->pc_age_ms = 0u;
    update_outputs(a);
}

void Arbiter_Tick1ms(Arbiter_t *a)
{
    if (a->pc_age_ms < PC_WATCHDOG_MS) {
        a->pc_age_ms++;
        if (a->pc_age_ms >= PC_WATCHDOG_MS) {
            clear(a->pc_cmd, PC_PWM_CHANNELS);   /* never reuse stale cmds */
        }
    }
    if (a->hh_pulse_ms > 0u)    { a->hh_pulse_ms--; }
    if (a->hh_override_ms > 0u) { a->hh_override_ms--; }
    update_outputs(a);
}
