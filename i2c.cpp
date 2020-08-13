/*
 * @coding: gb2312
 * @Author: vector-wlc
 * @Date: 2020-05-20 19:19:18
 * @Description: BASE CLASS I2c
 */

#include "i2c.h"

void I2c::LoadPort(uint8_t _port, uint8_t _scl_pos, uint8_t _sda_pos, uint8_t _slave_address)
{
    if (_port == '1')
    {
        dir = &P1DIR;
        out = &P1OUT;
        sel = &P1SEL;
        ren = &P1REN;
        in = &P1IN;
    }
    else
    {
        dir = &P2DIR;
        out = &P2OUT;
        sel = &P2SEL;
        ren = &P2REN;
        in = &P2IN;
    }

    scl_pos = _scl_pos;
    sda_pos = _sda_pos;

    slave_address = _slave_address;
}

// 确保传输成功
void I2c::SetPortLevel()
{
    // SEL 普通 IO 模式
    SetLow(*sel, scl_pos);
    SetLow(*sel, sda_pos);

    // SCL SDA 方向为输出
    SetHigh(*dir, scl_pos);
    setSdaOut();
}

// 设置上拉电阻
void I2c::SetPullUp()
{
    SetHigh(*ren, scl_pos);
    SetHigh(*ren, sda_pos);
    SetHigh(*out, scl_pos);
    SetHigh(*out, sda_pos);
    SetLow(*ren, scl_pos);
    SetLow(*ren, sda_pos);
}

uint8_t I2c::start()
{
    setSdaHigh();
    setSclHigh();
    delayUs(delay_time_us);
    if (!readSda())
    {
    }
    setSdaOut();
    setSdaLow();
    delayUs(delay_time_us);
    setSclLow();
    if (readSda())
    {
        setSdaOut();
        return 0;
    }
    return 1;
}

void I2c::stop()
{
    setSclLow();
    setSdaLow();
    delayUs(delay_time_us);
    setSclHigh();
    delayUs(delay_time_us);
    setSdaHigh();
    delayUs(delay_time_us);
}

uint8_t I2c::receiveAck()
{
    setSclLow();

    delayUs(delay_time_us);
    setSclHigh();

    delayUs(delay_time_us);

    if (readSda()) //应答为高电平，异常，通信失败
    {
        setSdaOut();
        setSclLow();
        return 0;
    }
    setSdaOut();
    setSclLow();
    return 1;
}

void I2c::sendAck()
{
    setSclLow();
    delayUs(delay_time_us);
    setSdaLow();
    delayUs(delay_time_us);
    setSclHigh();
    delayUs(delay_time_us);
    setSclLow();
    delayUs(delay_time_us);
}

void I2c::sendNack()
{
    setSclLow();
    delayUs(delay_time_us);
    setSdaHigh();
    delayUs(delay_time_us);
    setSclHigh();
    delayUs(delay_time_us);
    setSclLow();
    delayUs(delay_time_us);
}

void I2c::sendByte(uint8_t data)
{
    uint8_t i = 8;
    while (i--)
    {

        if (data & 0x80) //SDA 输出数据
        {
            setSdaHigh();
        }
        else
        {
            setSdaLow();
        }
        data <<= 1;
        delayUs(delay_time_us);
        setSclHigh(); //SCL 拉高，采集信号
        delayUs(delay_time_us);
        setSclLow(); //SCL 时钟线拉低
    }
}

void I2c::delayUs(uint8_t delay_us)
{
    while (delay_us)
    {
        DelayUs(1);
        --delay_us;
    }
}

uint8_t I2c::receiveByte(uint8_t ack)
{
    uint8_t i = 8;
    uint8_t data = 0;

    setSdaHigh();
    delayUs(delay_time_us);
    setSdaIn();

    while (i--)
    {
        data <<= 1;
        setSclLow();
        delayUs(delay_time_us);
        setSclHigh();
        delayUs(delay_time_us);

        if (readSda())
        {
            data |= 0x01;
        }
        else
        {
            data |= 0x00;
        }
    }
    setSdaOut();
    setSclLow();
    return data;
}

uint8_t I2c::ReadByte(uint8_t address)
{
    uint8_t error = 0;

    ++error;
    if (!start())
    {
        return error;
    }
    sendByte(slave_address << 1); /* 器件地址 */

    ++error;
    if (!receiveAck())
    {
        stop();
        return error;
    }
    sendByte(address); /* 设置低起始地址 */
    receiveAck();

    ++error;
    if (!start())
    {
        return error;
    }

    sendByte((slave_address << 1) + 1); /* 器件地址 */

    ++error;
    if (!receiveAck())
    {
    }

    uint8_t data = receiveByte(1);
    stop();
    return data;
}

uint8_t I2c::WriteByte(uint8_t address, uint8_t data)
{
    uint8_t error = 0;

    ++error;
    if (!start())
    {
        return error;
    }
    sendByte(slave_address << 1); /* 器件地址 */

    ++error;
    if (!receiveAck())
    {
        stop();
        return error;
    }
    sendByte(address); /* 设置低起始地址 */
    receiveAck();
    sendByte(data);
    receiveAck();
    stop();
    return 0xFF;
}