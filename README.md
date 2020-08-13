<!--
 * @Coding: utf-8
 * @Author: vector-wlc
 * @Date: 2020-08-12 19:52:29
 * @Description: README
-->
# AngleMeasure

## 简介
本程序使用 MSP430G2553 单片机软件模拟 IIC 读取 ADXL345 三轴加速度计内的数据，并且使用 OLED (IIC 通信) 显示得到的加速度数据，同时单片机通过硬件 UART 与计算机或其他设备进行通信。

## 环境
* 代码编辑：Visual Studio Code
* 运行调试：IAR Embedded Workbench IDE 7.11

## 注意
* 本程序中的软件模拟 IIC 代码也许只能在 MSP430G2553 正常使用，因为这个单片机有一个比较玄学的问题——当把 IO 引脚方向改成输入时，IIC 时序会断开
* 本程序的代码关于 UART 的部分需要使用**硬件调试**才会正常运行，即在 IAR 中的配置为：**Options -> Debugger -> FET Debugger**

## 使用
当计算机发送数字 1 时，角度测量开始。
当计算机发送数字 0 时，角度测量结束。
角度数据以**补码**形式发送