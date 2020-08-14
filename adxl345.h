/*
 * @coding: utf-8
 * @Author: vector-wlc
 * @Date: 2020-05-26 20:55:12
 * @Description: CLASS Adxl345
 */

#ifndef __ADXL345_H__
#define __ADXL345_H__

#include "i2c.h"
#include <math.h>

// CLASS Adxl345
class Adxl345 : public I2c
{
private:
    uint8_t data_buf[6];
    // 数据转换
    uint16_t doubleToUint16(double data);

    // 得到俯仰角
    uint16_t getFuYang(uint16_t x_data, uint16_t z_data);

    // 得到横滚角
    uint16_t getHengGun(uint16_t y_data, uint16_t z_data);

    // 得到航向角
    uint16_t getHangXiang(uint16_t y_data, uint16_t x_data);

public:
    Adxl345(uint8_t _port, uint8_t _scl_pos, uint8_t _sda_pos);
    Adxl345() {}
    ~Adxl345() {}

    // 得到角度数据
    uint8_t *GetAngle();
};

#endif
