#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

void _74HC595_WriteByte(unsigned char byte);

void MatrixLED_ShowColumn(unsigned char col, unsigned char byte);

void MatrixLED_Init();

#endif