/****************************************************************************
* @Filename  : crc8.h
* @Notes     : CRC-8/SMBUS (poly 0x07, init 0x00, no reflection, xorout 0x00).
*              Same algorithm as the sensing-app data frame. ISO C90.
*****************************************************************************/
#ifndef CRC8_H
#define CRC8_H

unsigned char CRC8_SMBUS(const unsigned char *data, unsigned int len);

#endif
