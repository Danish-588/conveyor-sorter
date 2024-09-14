/*
 * interrupt.h
 *
 *  Created on: Jul 1, 2018
 *      Author: Varun
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include"driverlib/gpio.h"
#include"driverlib/uart.h"
#include"driverlib/timer.h"

#define uart0 UART0_BASE
#define uart1 UART1_BASE
#define uart2 UART2_BASE
#define uart3 UART3_BASE
#define uart4 UART4_BASE
#define uart5 UART5_BASE
#define uart6 UART6_BASE

#define timer0 TIMER0_BASE
#define timer1 TIMER1_BASE
#define timer2 TIMER2_BASE
#define timer3 TIMER3_BASE

#define porta_gpio GPIO_PORTA_BASE
#define portb_gpio GPIO_PORTB_BASE
#define portc_gpio GPIO_PORTC_BASE
#define portd_gpio GPIO_PORTD_BASE
#define porte_gpio GPIO_PORTE_BASE
#define portf_gpio GPIO_PORTF_BASE
#define portg_gpio GPIO_PORTG_BASE
#define porth_gpio GPIO_PORTH_BASE
#define portj_gpio GPIO_PORTJ_BASE
#define portk_gpio GPIO_PORTK_BASE
#define portl_gpio GPIO_PORTL_BASE
#define portm_gpio GPIO_PORTM_BASE
#define portn_gpio GPIO_PORTN_BASE
#define portp_gpio GPIO_PORTP_BASE

void intclear(uint32_t peripheral)
{
    switch(peripheral)
    {
    case porta_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portb_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portc_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portd_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case porte_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portf_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portg_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case porth_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portj_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portk_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portl_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portm_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portn_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case portp_gpio:
        GPIOIntClear(peripheral, 0xFF);  //Sets ICR register
        break;
    case timer0:
        TimerIntClear(peripheral, TIMER_TIMA_TIMEOUT);
        break;
    case timer1:
        TimerIntClear(peripheral, TIMER_TIMA_TIMEOUT);
        break;
    case timer2:
        TimerIntClear(peripheral, TIMER_TIMA_TIMEOUT);
        break;
    case timer3:
        TimerIntClear(peripheral, TIMER_TIMA_TIMEOUT);
        break;
    case uart0:
        UARTIntClear(UART0_BASE, UART_INT_RX);
        break;
    case uart1:
        UARTIntClear(UART1_BASE, UART_INT_RX);
        break;
    case uart2:
        UARTIntClear(UART2_BASE, UART_INT_RX);
        break;
    case uart3:
        UARTIntClear(UART3_BASE, UART_INT_RX);
        break;
    case uart4:
        UARTIntClear(UART4_BASE, UART_INT_RX);
        break;
    case uart5:
        UARTIntClear(UART5_BASE, UART_INT_RX);
        break;
    case uart6:
        UARTIntClear(UART6_BASE, UART_INT_RX);
        break;
    default:
        break;
    }
}

void int_enable(void)
{
    IntMasterEnable();
}

void int_disable(void)
{
    IntMasterDisable();
}

#endif /* INTERRUPT_H_ */
