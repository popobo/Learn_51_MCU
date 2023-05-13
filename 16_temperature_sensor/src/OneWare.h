#ifndef __ONEWIRE_H_
#define __ONEWIRE_H_

unsigned char OneWire_Init(void);

void OneWire_SendBit(unsigned char one_bit);
unsigned char OneWire_ReceiveBit(void);
void OneWare_SendByte(unsigned char byte);
unsigned char OneWare_ReceiveByte(void);

#endif