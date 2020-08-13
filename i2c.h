/*
 * #coding: gb2312
 * #Author: vector-wlc
 * #Date: 2020-05-12 12:11:02
 * #Description: BASE CLASS I2C  
 */

#ifndef __IIC_H__
#define __IIC_H__

#include "base_fun.h"

// CLASS I2c
// I2C 软件模拟类
class I2c
{
private:
    Port *out;             // 输出引脚
    Port *dir;             // 方向选择
    Port *sel;             // 功能选择
    Port *ren;             // 上下拉使能
    Port *in;              // 输入引脚
    uint8_t scl_pos;       // 时钟引脚
    uint8_t sda_pos;       // 数据引脚
    uint8_t slave_address; // 元件的 I2C 地址

    uint16_t delay_time_us; // 周期

    // 设置 SCL 高电平
    void setSclHigh()
    {
        SetHigh(*out, scl_pos);
    }

    // 设置 SCL 低电平
    void setSclLow()
    {
        SetLow(*out, scl_pos);
    }

    // 设置 SDA 输出
    void setSdaOut()
    {
        SetHigh(*dir, sda_pos);
    }

    // 设置 SDA 输入
    void setSdaIn()
    {
        SetLow(*dir, sda_pos);
    }

    // 读取 SDA 数据
    uint8_t readSda()
    {
        if ((*in) & sda_pos)
        {
            return 1;
        }
        return 0;
    }

    // 设置 SDA 高电平
    void setSdaHigh()
    {
        SetHigh(*out, sda_pos);
    }

    // 设置 SDA 低电平
    void setSdaLow()
    {
        SetLow(*out, sda_pos);
    }

    // 开始信号
    uint8_t start();

    // 结束信号
    void stop();

    // 接收应答信号
    uint8_t receiveAck();

    // 发送应答
    void sendAck();

    // 不发送应答
    void sendNack();

    // 传输一个字节
    // #参数说明
    // data : 需要传输的字节
    void sendByte(uint8_t data);

    // 接收一个字节
    // #参数说明
    // ack = 1  发送 ACK
    // ack = 0  不发送 ACK
    // #返回值
    // 数据
    uint8_t receiveByte(uint8_t ack);

    void delayUs(uint8_t delay_us);

public:
    // 引脚初始化
    // #参数说明
    // _port : IIC 所使用到的端口
    // _scl_pos : IIC SCL 时钟线引脚位置
    // _sda_pos : IIC SDA 数据线引脚位置
    // _slave_address : IIC 从属元件地址
    I2c(uint8_t _port,
        uint8_t _scl_pos,
        uint8_t _sda_pos,
        uint8_t _slave_address)
    {
        delay_time_us = 1;
        LoadPort(_port, _scl_pos, _sda_pos, _slave_address);
        SetPortLevel();
    }

    I2c() { delay_time_us = 1; }
    ~I2c() {}

    // 载入引脚
    // #参数说明
    // _port : IIC 所使用到的端口
    // _scl_pos : IIC SCL 时钟线引脚位置
    // _sda_pos : IIC SDA 数据线引脚位置
    // _slave_address : IIC 从属元件地址
    void LoadPort(uint8_t _port, uint8_t _scl_pos, uint8_t _sda_pos, uint8_t _slave_address);

    // 设置引脚电平
    // 确保传输成功
    // SCL SDA 上拉电阻
    // SCL 为输出
    void SetPortLevel();

    // 在设备中读取一个字节
    // #参数说明
    // address : 需要读取的地址
    // #返回值
    // 数据
    uint8_t ReadByte(uint8_t address);

    // 在设备中写入一个字节
    // #参数说明
    // address : 需要写入的地址
    // data : 需要写入的数据
    uint8_t WriteByte(uint8_t address, uint8_t data);

    // 设置上拉电阻
    void SetPullUp();

    // 设置延迟时间
    void SetDelayTime(int _delay_time_us)
    {
        delay_time_us = _delay_time_us;
    }
};

#endif
