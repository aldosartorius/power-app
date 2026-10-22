#include "pc_frame.h"
#include "crc8.h"

enum { ST_START = 0, ST_LEN, ST_DATA, ST_CRC, ST_END };

void PcFrame_Init(PcFrameParser_t *p)
{
    unsigned int i;
    p->state = ST_START;
    p->idx = 0u;
    for (i = 0u; i < PC_PWM_CHANNELS; i++) {
        p->cmd[i] = 0;
    }
    p->frames_ok = 0ul;
    p->crc_errors = 0ul;
    p->format_errors = 0ul;
}

static short sat_cmd(long v)
{
    if (v >  MOTOR_CMD_MAX) { v =  MOTOR_CMD_MAX; }
    if (v < -MOTOR_CMD_MAX) { v = -MOTOR_CMD_MAX; }
    return (short)v;
}

static void decode(PcFrameParser_t *p)
{
    unsigned int  i;
    unsigned int  raw;
    long          v;

    for (i = 0u; i < PC_PWM_CHANNELS; i++) {
        raw = (unsigned int)p->buf[2u + 2u * i]
            | ((unsigned int)p->buf[3u + 2u * i] << 8);
        v = (raw & 0x8000u) ? (long)raw - 65536L : (long)raw;  /* portable */
        p->cmd[i] = sat_cmd(v);
    }
}

/* On a framing error, restart; if the offending byte is itself a start
   byte, use it as the beginning of the next frame (fast resync). */
static void resync(PcFrameParser_t *p, unsigned char byte)
{
    p->format_errors++;
    if (byte == PC_FRAME_START) {
        p->buf[0] = byte;
        p->idx = 1u;
        p->state = ST_LEN;
    } else {
        p->idx = 0u;
        p->state = ST_START;
    }
}

int PcFrame_Feed(PcFrameParser_t *p, unsigned char byte)
{
    switch (p->state) {

    case ST_START:
        if (byte == PC_FRAME_START) {
            p->buf[0] = byte;
            p->idx = 1u;
            p->state = ST_LEN;
        }
        break;

    case ST_LEN:
        if (byte == PC_FRAME_LEN) {
            p->buf[p->idx++] = byte;
            p->state = ST_DATA;
        } else {
            resync(p, byte);
        }
        break;

    case ST_DATA:
        p->buf[p->idx++] = byte;
        if (p->idx >= PC_FRAME_LEN) {
            p->state = ST_CRC;
        }
        break;

    case ST_CRC:
        p->buf[p->idx++] = byte;
        p->state = ST_END;
        break;

    case ST_END:
    default:
        p->state = ST_START;
        p->idx = 0u;
        if (byte != PC_FRAME_END) {
            resync(p, byte);
            break;
        }
        if (CRC8_SMBUS(p->buf, PC_FRAME_LEN) != p->buf[PC_FRAME_LEN]) {
            p->crc_errors++;
            break;
        }
        decode(p);
        p->frames_ok++;
        return 1;
    }
    return 0;
}
