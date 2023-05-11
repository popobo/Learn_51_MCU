#ifndef __DS1302_H__
#define __DS1302_H__

#define DS1302_SECOND (0x80)
#define DS1302_MINUTE (0x82)
#define DS1302_HOUR (0x84)
#define DS1302_DATE (0x86)
#define DS1302_MONTH (0x88)
#define DS1302_DAY (0x8A)
#define DS1302_YEAR (0x8C)
#define DS1302_WP (0x8E)

extern unsigned char DS1302_Time[];

/**
* @brief  init DS1302, set CE 0, set SCLK 0
*/
void DS1302_Init(void);

/**
* @brief  write one byte to DS1302
* @param  cmd to DS1302
* @param  byte sent to DS1302
* @retval none
*/
void DS1302_WriteByte(unsigned char cmd, unsigned char byte);

/**
* @brief  read one byte to DS1302
* @param  cmd to DS1302
* @retval byte read from DS1302
*/
unsigned char DS1302_ReadByte(unsigned char cmd);

/**
* @brief  设置DS1302_Time到DS1302
*/
void DS1302_SetTime(void);

/**
* @brief  读取DS1302中的事件到DS1302_Time
*/
void DS1302_GetTime(void);

#endif