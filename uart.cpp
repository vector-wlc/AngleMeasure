/*
 * @coding: utf-8
 * @Author: vector-wlc
 * @Date: 2020-05-24 19:45:03
 * @Description: 
 */

#include "uart.h"

void UartInit()
{
    DCOCTL = 0;            // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ; // Set DCO
    DCOCTL = CALDCO_1MHZ;
    P1SEL |= BIT1 + BIT2;   // P1.1 = RXD, P1.2=TXD
    P1SEL2 |= BIT1 + BIT2;  // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;   // SMCLK
    UCA0BR0 = 104;          // 1MHz 9600
    UCA0BR1 = 0;            // 1MHz 9600
    UCA0MCTL = UCBRS0;      // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;   // **Initialize USCI state machine**
    UC0IE |= UCA0RXIE;      // Enable USCI_A0 RX interrupt
    __bis_SR_register(GIE); // Enter LPM0 w/ int until Byte RXed
}

void UartSendNum(uint8_t num)
{
    while (!(IFG2 & UCA0TXIFG))
    {
    }

    UCA0TXBUF = num;
    SetLow(IFG2, UCA0TXIFG);
}

void UartSendStr(const char *str)
{
    while (*str)
    {
        while (!(IFG2 & UCA0TXIFG))
        {
        }

        UCA0TXBUF = *str;
        ++str;
    }

    SetLow(IFG2, UCA0TXIFG);
}

void UartSendData(uint8_t *data_ptr, uint8_t data_length)
{
    uint8_t pos = 0;
    while (pos < data_length)
    {
        while (!(IFG2 & UCA0TXIFG))
        {
        }
        UCA0TXBUF = data_ptr[pos];
        ++pos;
    }
}

uint8_t is_sendable = 0;
// RX 接收数据中断服务函数
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    is_sendable = UCA0RXBUF;
}