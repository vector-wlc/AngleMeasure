/*
 * @coding: gb2312
 * @Author: vector-wlc
 * @Date: 2020-05-24 19:45:08
 * @Description: UART 通信类
 */

#ifndef __UART_H__
#define __UART_H__

#include "base_fun.h"

void UartInit();
void UartSendNum(uint8_t num);
void UartSendStr(const char *str);
void UartSendData(uint8_t *data_ptr, uint8_t data_length);

#endif