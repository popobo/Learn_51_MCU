#ifndef __AT24C02_H_
#define __AT24C02_H_

/**
* @brief  向AT24C02指定位置写入一个字节，注意耗时5ms
* @param  address：写入的地址，byte：写入的字节
*/
void AT24C02_WriteByte(unsigned char address, unsigned char byte);

/**
* @brief  向AT24C02指定位置读出一个字节
* @param  address：写入的地址
* @retval byte：读出的字节
*/
unsigned char AT24C02_ReadByte(unsigned char address);

#endif