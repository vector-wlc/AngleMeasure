/*
 * @coding: gb2312
 * @Author: vector-wlc
 * @Date: 2020-05-26 21:33:52
 * @Description: CLASS Adxl345
 */

#include "adxl345.h"

Adxl345::Adxl345(uint8_t _port, uint8_t _scl_pos, uint8_t _sda_pos)
{
    LoadPort(_port, _scl_pos, _sda_pos, ADXL345_ADDRESS);
    SetPortLevel();

    SetDelayTime(5);

    // 设置带宽
    WriteByte(BW_RATE, BW_RATE_100HZ);

    // 设置测量范围为 10-bit
    uint8_t value = ReadByte(DATA_FORMAT);
    value &= ~0x0F;
    value |= RANGE_2G;
    value |= 0x08;
    WriteByte(DATA_FORMAT, value);

    // 允许测量
    WriteByte(POWER_CTL, MEASURE);
}

uint16_t Adxl345::doubleToUint16(double data)
{
    uint16_t data_uint = (uint16_t)abs(data);

    if (data < 0)
    {
        data_uint = (~data_uint) + 1;
    }

    return data_uint;
}

// 得到俯仰角
uint16_t Adxl345::getFuYang(uint16_t x_data, uint16_t z_data)
{
    uint8_t is_x_negative = (x_data > 0xFFF);
    uint8_t is_z_negative = (z_data > 0xFFF);
    if (is_x_negative)
    {
        x_data = -x_data;
    }
    if (is_z_negative)
    {
        z_data = -z_data;
    }

    if (z_data == 0 && is_x_negative)
    {
        return doubleToUint16(-90);
    }

    if (z_data == 0 && !is_x_negative)
    {
        return 90;
    }

    double fu_yang = atan(double(x_data) / double(z_data)) * 57.296;

    if (!is_x_negative && is_z_negative)
    {
        fu_yang = 180 - fu_yang;
    }
    else if (is_x_negative && !is_z_negative)
    {
        fu_yang = -fu_yang;
    }
    else if (is_x_negative && is_z_negative)
    {
        fu_yang = fu_yang - 180;
    }

    return doubleToUint16(fu_yang);
}

// 得到横滚角
uint16_t Adxl345::getHengGun(uint16_t y_data, uint16_t z_data)
{
    uint8_t is_y_negative = (y_data > 0xFFF);
    uint8_t is_z_negative = (z_data > 0xFFF);
    if (is_y_negative)
    {
        y_data = -y_data;
    }
    if (is_z_negative)
    {
        z_data = -z_data;
    }

    if (z_data == 0 && is_y_negative)
    {
        return doubleToUint16(-90);
    }

    if (z_data == 0 && !is_y_negative)
    {
        return 90;
    }

    double heng_gun = atan(double(y_data) / double(z_data)) * 57.296;

    if (!is_y_negative && is_z_negative)
    {
        heng_gun = 180 - heng_gun;
    }
    else if (is_y_negative && !is_z_negative)
    {
        heng_gun = -heng_gun;
    }
    else if (is_y_negative && is_z_negative)
    {
        heng_gun = heng_gun - 180;
    }

    return doubleToUint16(heng_gun);
}

// 得到航向角
uint16_t Adxl345::getHangXiang(uint16_t y_data, uint16_t x_data)
{
    uint8_t is_y_negative = (y_data > 0xFFF);
    uint8_t is_x_negative = (x_data > 0xFFF);
    if (is_y_negative)
    {
        y_data = -y_data;
    }
    if (is_x_negative)
    {
        x_data = -x_data;
    }

    if (x_data == 0 && is_y_negative)
    {
        return 90;
    }

    if (x_data == 0 && !is_y_negative)
    {
        return doubleToUint16(-90);
    }

    double hang_xiang = atan(double(y_data) / double(x_data)) * 57.296;

    if (is_y_negative && is_x_negative)
    {
        hang_xiang = 180 - hang_xiang;
    }
    else if (!is_y_negative && !is_x_negative)
    {
        hang_xiang = -hang_xiang;
    }
    else if (!is_y_negative && is_x_negative)
    {
        hang_xiang = hang_xiang - 180;
    }

    return doubleToUint16(hang_xiang);
}

uint8_t *Adxl345::GetAngle()
{
    uint16_t x_data = (ReadByte(AXES_DATA + 1));
    x_data <<= 8;
    x_data += ReadByte(AXES_DATA);
    uint16_t y_data = (ReadByte(AXES_DATA + 3));
    y_data <<= 8;
    y_data += ReadByte(AXES_DATA + 2);
    uint16_t z_data = (ReadByte(AXES_DATA + 5));
    z_data <<= 8;
    z_data += ReadByte(AXES_DATA + 4);

    // 这里使用中文
    // 计算航向角，横滚角和俯仰角
    uint16_t hang_xiang = getHangXiang(y_data, x_data); // 航向角
    uint16_t fu_yang = getFuYang(x_data, z_data);       // 俯仰角
    uint16_t heng_gun = getHengGun(y_data, z_data);     // 横滚角

    // 将角度数据写入缓冲区
    data_buf[1] = hang_xiang >> 8;
    data_buf[2] = hang_xiang & 0xff;
    data_buf[3] = fu_yang >> 8;
    data_buf[4] = fu_yang & 0xff;
    data_buf[5] = heng_gun >> 8;
    data_buf[6] = heng_gun & 0xff;

    return data_buf;
}
