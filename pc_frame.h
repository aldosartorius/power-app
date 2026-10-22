/****************************************************************************
* @Filename  : pc_frame.h
* @Notes     : Parser for the PC -> power-MCU PWM command frame. ISO C90.
*
*  Byte   Field             Type        Description
*  [0]    0xAA              -           start
*  [1]    0x0C (12)         uint8       length = bytes [0..11] covered by CRC
*  [2..3] pwm1              int16 LE    motor 1 command
*  [4..5] pwm2              int16 LE    motor 2 command
*  [6..7] pwm3              int16 LE    motor 3 command
*  [8..9] pwm4              int16 LE    motor 4 command
*  [10..11] pwm5            int16 LE    motor 5 command
*  [12]   CRC-8/SMBUS       uint8       over bytes [0..11]
*  [13]   0x55              -           end
*
*  Total 14 bytes (1.22 ms at 115200 bps, 8N1).
*  Command scale: -10000..+10000. Sign = direction (+ = IN1 high, forward),
*  |value|/10000 = duty cycle 0.0..1.0. Out-of-range values are saturated.
*****************************************************************************/
#ifndef PC_FRAME_H
#define PC_FRAME_H

#include "app_config.h"

#define PC_FRAME_START   0xAAu
#define PC_FRAME_END     0x55u
#define PC_FRAME_LEN     12u      /* bytes covered by CRC: [0..11] */
#define PC_FRAME_SIZE    14u

typedef struct {
    unsigned char state;
    unsigned char idx;
    unsigned char buf[PC_FRAME_SIZE];
    short         cmd[PC_PWM_CHANNELS];   /* last valid frame (decoded)  */
    unsigned long frames_ok;              /* diagnostic counters         */
    unsigned long crc_errors;
    unsigned long format_errors;
} PcFrameParser_t;

void PcFrame_Init(PcFrameParser_t *p);

/* Feed one byte. Returns 1 when a complete valid frame has just been
   decoded into p->cmd[], 0 otherwise. */
int  PcFrame_Feed(PcFrameParser_t *p, unsigned char byte);

#endif
