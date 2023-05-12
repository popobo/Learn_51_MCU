#ifndef __AT24C02_H_
#define __AT24C02_H_

void AT24C02_WriteByte(unsigned char address, unsigned char byte);

unsigned char AT24C02_ReadByte(unsigned char address);

#endif