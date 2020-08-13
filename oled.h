/*
 * @coding: gb2312
 * @Author: vector-wlc
 * @Date: 2020-05-26 10:47:55
 * @Description: CLASS OLED
 */

#ifndef __OLED_H__
#define __OLED_H__

#include "i2c.h"
#include <stdio.h>

// CLASS Oled
// OLED 使用 I2C 通信
class Oled : public I2c
{
private:
    // 写入命令
    void writeCmd(uint8_t cmd);

    // 写入数据
    void writeData(uint8_t data);

    // 设置光标
    void setPos(uint8_t row, uint8_t col);

public:
    Oled(uint8_t _port, uint8_t _scl_pos, uint8_t _sda_pos);
    Oled() {}

    ~Oled() {}

    // 清除全屏
    void ClearAll();

    // 清除一行
    void ClearRow(uint8_t row);

    // 开启显示
    void DisplayOn();

    // 关闭显示
    void DisplayOff();

    // 显示字符
    void ShowChar(uint8_t row, uint8_t col, uint8_t ch);

    // 显示字符串
    void ShowStr(uint8_t row, uint8_t col, const uint8_t *str);

    // 显示数字
    void ShowNum(uint8_t row, uint8_t col, uint8_t num);
};

#endif
