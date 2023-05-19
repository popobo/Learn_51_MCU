#include "Atmel/REGX52.H"

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
* @brief  I2C start
*/
void I2C_Start(void)
{
    I2C_SDA = 1;
    I2C_SCL = 1;
    I2C_SDA = 0;
    I2C_SCL = 0;
}

/**
* @brief  I2C stop
*/
void I2C_Stop(void)
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_SDA = 1;
}

/**
* @brief  I2C发送一个字节
* @param  要发送的字节
*/
void I2C_SendByte(unsigned char byte)
{
    unsigned char i = 0;
    for (i = 0; i < 8; ++i)
    {
        I2C_SDA = byte & (0x80 >> i);
        I2C_SCL = 1;
        //记得判断高电平是否过短
        I2C_SCL = 0;
    }
}

/**
* @brief I2C接收一个字节
* @retval 接收到的字节
*/
unsigned char I2C_ReceiveByte(void)
{
    unsigned char byte = 0;
    unsigned char i = 0;
    I2C_SDA = 1;

    for(i = 0; i < 8; ++i)
    {
        I2C_SCL = 1;
        if(I2C_SDA) { byte |= 0x80 >> i; }
        I2C_SCL = 0;
    }

    return byte;
}

/**
* @brief  I2C发送应答
* @param  应答位，0应答，1不应答
*/
void I2C_SendAck(unsigned char ack_bit)
{
    I2C_SDA = ack_bit;
    I2C_SCL = 1;
    I2C_SCL = 0;
}

/**
* @brief  I2C接收应答
* @retval 应答
*/
unsigned char I2C_ReceiveAck(void)
{
    unsigned char ack_bit;
    I2C_SDA = 1;
    I2C_SCL = 1;
    ack_bit = I2C_SDA;
    I2C_SCL = 0;
    return ack_bit;
}