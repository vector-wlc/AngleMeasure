/*
 * @coding: utf-8
 * @Author: vector-wlc
 * @Date: 2020-05-26 10:47:50
 * @Description: 
 */

#include "oled.h"

/************************************6*8的点阵************************************/
const uint8_t F6x8[][6] =
    {
        {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0  0
        {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00}, // 1  1
        {0x00, 0x42, 0x61, 0x51, 0x49, 0x46}, // 2  2
        {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31}, // 3  3
        {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10}, // 4  4
        {0x00, 0x27, 0x45, 0x45, 0x45, 0x39}, // 5  5
        {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6  6
        {0x00, 0x01, 0x71, 0x09, 0x05, 0x03}, // 7  7
        {0x00, 0x36, 0x49, 0x49, 0x49, 0x36}, // 8  8
        {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E}, // 9  9
        {0x00, 0x00, 0x36, 0x36, 0x00, 0x00}, // :  10
        {0x00, 0x20, 0x54, 0x54, 0x54, 0x78}, // a  11
        {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38}, // b  12
        {0x00, 0x38, 0x44, 0x44, 0x44, 0x20}, // c  13
        {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F}, // d  14
        {0x00, 0x38, 0x54, 0x54, 0x54, 0x18}, // e  15
        {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02}, // f  16
        {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C}, // g  17
        {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78}, // h  18
        {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00}, // i  19
        {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00}, // j  20
        {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00}, // k  21
        {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00}, // l  22
        {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78}, // m  23
        {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78}, // n  24
        {0x00, 0x38, 0x44, 0x44, 0x44, 0x38}, // o  25
        {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18}, // p  26
        {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC}, // q  27
        {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08}, // r  28
        {0x00, 0x48, 0x54, 0x54, 0x54, 0x20}, // s  29
        {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20}, // t  30
        {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C}, // u  31
        {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C}, // v  32
        {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C}, // w  33
        {0x00, 0x44, 0x28, 0x10, 0x28, 0x44}, // x  34
        {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, // y  35
        {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44}, // z  36
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // space 37
};

void Oled::writeCmd(uint8_t cmd)
{
    WriteByte(OLED_CMD, cmd);
}

void Oled::writeData(uint8_t data)
{
    WriteByte(OLED_DATA, data);
}

void Oled::setPos(uint8_t row, uint8_t col)
{
    writeCmd(0xb0 + ((row >> 3) & 0xf));
    writeCmd(((col & 0xf0) >> 4) | 0x10);
    writeCmd((col & 0x0f) | 0x01);
}

Oled::Oled(uint8_t _port, uint8_t _scl_pos, uint8_t _sda_pos)
{
    LoadPort(_port, _scl_pos, _sda_pos, OLED_ADDRESS);
    SetPortLevel();
    SetDelayTime(5);
    uint8_t init_cmd[] =
        {// OLED 初始化命令
         0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F,

         0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12,

         0xD8, 0x30, 0x8D, 0x14, 0xAF};

    for (uint8_t i = 0; i < 27; ++i)
    {
        writeCmd(init_cmd[i]);
    }
}

void Oled::ClearAll()
{
    uint8_t row = 0;
    uint8_t col = 0;
    for (row = 0; row < 8; ++row)
    {
        writeCmd(0xB0 + row);
        writeCmd(0x00);
        writeCmd(0x10);
        for (col = 0; col < 128; ++col)
        {
            writeData(0x00);
        }
    }
}

void Oled::ClearRow(uint8_t row)
{
    uint8_t col;
    writeCmd(0xB0 + row);
    writeCmd(0x00);
    writeCmd(0x10);
    for (col = 0; col < 128; ++col)
    {
        writeData(0x00);
    }
}

void Oled::DisplayOn()
{
    writeCmd(0X8D); //SET DCDC命令
    writeCmd(0X14); //DCDC ON
    writeCmd(0XAF); //DISPLAY ON
}

void Oled::DisplayOff()
{
    writeCmd(0X8D); //SET DCDC命令
    writeCmd(0X10); //DCDC OFF
    writeCmd(0XAE); //DISPLAY OFF
}

void Oled::ShowChar(uint8_t row, uint8_t col, uint8_t ch)
{
    uint8_t index = 0;
    // 进行字符与数组索引的转换
    if (ch >= '0' && ch <= '9')
    {
        index = ch - '0';
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        index = ch - 'a' + 11;
    }
    else if (ch == ':')
    {
        index = 10;
    }
    else
    {
        index = 37;
    }
    setPos(row, col);
    for (uint8_t i = 0; i < 6; ++i)
    {
        writeData(F6x8[index][i]);
    }
}

// 显示字符串
void Oled::ShowStr(uint8_t row, uint8_t col, const uint8_t *str)
{
    while (*str)
    {
        ShowChar(row, col, *str);
        col += 8;
        if (col > 120)
        {
            col = 0;
            row += 8;
        }
        ++str;
    }
}

void Oled::ShowNum(uint8_t row, uint8_t col, uint8_t num)
{
    uint8_t str[4]; // 最多三位数
    sprintf((char *)str, "%d", num);
    ShowStr(row, col, str);
}