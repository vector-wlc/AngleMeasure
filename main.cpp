/*
 * @coding: utf-8
 * @Author: vector-wlc
 * @Date: 2020-05-24 19:41:20
 * @Description: 
 */

#include "uart.h"
#include "oled.h"
#include "adxl345.h"

int main()
{
    extern uint8_t is_sendable;
    WDTClose();
    UartInit();

    // CS 线接高
    // SDO 线接低
    // SCL 线为引脚 2.0
    // SDA 线为引脚 2.1
    Adxl345 adxl345('2', BIT0, BIT1);

    // SCL 线为引脚 2.2
    // SDA 线为引脚 2.3
    Oled oled('2', BIT2, BIT3);
    oled.ClearAll();

    uint8_t *data_ptr;
    while (1)
    {
        if (is_sendable)
        {
            data_ptr = adxl345.GetAngle();
            UartSendData(data_ptr, 6);
            for (uint8_t pos = 0; pos < 6; ++pos)
            {
                oled.ShowNum(OLED_SHOW_ROW, OLED_SHOW_COL + pos, data_ptr[pos]);
            }
        }
    }

    return 0;
}