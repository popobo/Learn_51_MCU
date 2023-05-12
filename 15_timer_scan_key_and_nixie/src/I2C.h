#ifndef __I2C_H_
#define __I2C_H_

void I2C_Start(void);

void I2C_Stop(void);

void I2C_SendByte(unsigned char byte);

unsigned char I2C_ReceiveByte(void);

void I2C_SendAck(unsigned char ack_bit);

unsigned char I2C_ReceiveAck(void);

#endif