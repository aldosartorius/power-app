#include "crc8.h"

unsigned char CRC8_SMBUS(const unsigned char *data, unsigned int len)
{
    unsigned char crc = 0x00u;
    unsigned int  i;
    unsigned char bit;

    for (i = 0u; i < len; i++) {
        crc ^= data[i];
        for (bit = 0u; bit < 8u; bit++) {
            if (crc & 0x80u) {
                crc = (unsigned char)((crc << 1) ^ 0x07u);
            } else {
                crc = (unsigned char)(crc << 1);
            }
        }
    }
    return crc;
}
