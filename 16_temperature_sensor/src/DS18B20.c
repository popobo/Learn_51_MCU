#include "DS18B20.h"
#include "OneWare.h"

#define DS18B20_SKIP_ROM 0xCC
#define DS18B20_CONVERT_T 0x44
#define DS18B20_READ_SCR 0xBE


void DS18B20_CovertT(void)
{
    OneWire_Init();
    OneWare_SendByte(DS18B20_SKIP_ROM);
    OneWare_SendByte(DS18B20_CONVERT_T);

}

float DS18B20_ReadT(void)
{
    unsigned char TLSB = 0;
    unsigned char TMSB = 0;
    int temp = 0;
    float T = 0;
    OneWire_Init();
    OneWare_SendByte(DS18B20_SKIP_ROM);
    OneWare_SendByte(DS18B20_READ_SCR);
    TLSB = OneWare_ReceiveByte();
    TMSB = OneWare_ReceiveByte();
    temp = (TMSB << 8) | TLSB;
    T = temp / 16.0;
    return T;
}