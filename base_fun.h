/*
 * @coding: gb2312
 * @Author: vector-wlc
 * @Date: 2020-04-08 20:32:23
 * @Description: include base functions
 */

#ifndef __BASE_FUN_H__
#define __BASE_FUN_H__

#include <msp430g2553.h>
#include <stdint.h>
#include <string.h>

#ifdef __vscode
#define __interrupt // 防止 VSCode 报错
#endif

// 端口类型
typedef volatile unsigned char Port;

// 设置为高电平
#define SetHigh(port, value) (port) |= (value)

// 设置为低电平
#define SetLow(port, value) (port) &= ~(value)

// CPU 频率
#define CPU_FRE ((double)1000000)

// 时间延迟 ms
#define DelayMs(t_ms) __delay_cycles((long)(CPU_FRE * (double)t_ms / 1000.0))

// 时间延迟 us
#define DelayUs(t_us) __delay_cycles((long)(CPU_FRE * (double)t_us / 1000000.0))

// 关闭看门狗
#define WDTClose() WDTCTL = WDTPW + WDTHOLD

////////////////////////
// UART
////////////////////////

#define FRAME_START 0xE5 // 帧头
#define FRAME_END 0xE6   // 帧尾

#define READY 0x01      // 准备就绪
#define FEATURE 0x05    // 特征码
#define CONFIRM 0x06    // 题目确认
#define TYPE 0x04       // 倾角测量题目类型
#define SEND_A 0x41     // 向物联网实验平台发送角度 A 数据
#define SEND_B 0x42     // 向物联网实验平台发送角度 B 数据
#define COLLECTION 0x49 // 采集数据指令
#define ONLY_A 0xF1     // 只采集 A
#define BOTH 0xF2       // 采集 A 和 B
#define STEP_DONE 0x4A  // 步骤完成
#define STEP_BACK 0x4B  // 步骤后退
#define TASK_DONE 0x4C  // 任务完成
#define END 0x4D        // 实验结束
#define ERROR 0xFF      // 接收数据出错

////////////////////////
// ADXL345
////////////////////////

#define ADXL345_ADDRESS 0x53 // ADXL345 IIC地址
#define POWER_CTL 0x2D       // 省电特性控制
#define AXES_DATA 0x32       // 数据起始位置， X --> Y --> Z
#define DATA_FORMAT 0x31     // 数据形式
#define BW_RATE 0x2C         // 数据速率控制

#define BW_RATE_1600HZ 0x0F
#define BW_RATE_800HZ 0x0E
#define BW_RATE_400HZ 0x0D
#define BW_RATE_200HZ 0x0C
#define BW_RATE_100HZ 0x0B
#define BW_RATE_50HZ 0x0A
#define BW_RATE_25HZ 0x09

#define RANGE_2G 0x00
#define RANGE_4G 0x01
#define RANGE_8G 0x02
#define RANGE_16G 0x03

#define MEASURE 0x08

////////////////////////
// OLED
////////////////////////

#define OLED_ADDRESS 0x3C // oled 地址
#define OLED_CMD 0x00     // oled 控制指令地址
#define OLED_DATA 0x40    // oled 数据指令地址
#define OLED_SHOW_ROW 30  // oled 显示行数
#define OLED_SHOW_COL 10  // oled 显示列数

#endif