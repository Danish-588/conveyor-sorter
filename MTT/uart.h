/*
 * uart.h
 *
 *  Created on: Jun 29, 2018
 *      Author: Varun
 */

#ifndef UART_H_
#define UART_H_

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/pin_map.h"
#include"driverlib/gpio.h"
#include"driverlib/sysctl.h"
#include"driverlib/adc.h"
#include"driverlib/timer.h"
#include"driverlib/uart.h"
#include"driverlib/interrupt.h"

#define uart0 UART0_BASE
#define uart1 UART1_BASE
#define uart2 UART2_BASE
#define uart3 UART3_BASE
#define uart4 UART4_BASE
#define uart5 UART5_BASE
#define uart6 UART6_BASE

//Init uart - port init, clk, int
//tx
//rx
void uart_init(uint32_t uart, int baud)
{
    if(uart==uart0)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);

        UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART0_BASE);
    }

    if(uart==uart1)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5);
        GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4);
        GPIOPinConfigure(GPIO_PC4_U1RX);
        GPIOPinConfigure(GPIO_PC5_U1TX);

        UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART1_BASE);
    }

    if(uart==uart2)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6|GPIO_PIN_7);
        GPIOPinConfigure(GPIO_PD6_U2RX);
        GPIOPinConfigure(GPIO_PD7_U2TX);

        UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART2_BASE);
    }

    if(uart==uart3)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);
        GPIOPinConfigure(GPIO_PC6_U3RX);
        GPIOPinConfigure(GPIO_PC7_U3TX);

        UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART3_BASE);
    }

    if(uart==uart4)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTJ_BASE, GPIO_PIN_0|GPIO_PIN_1);
        GPIOPinConfigure(GPIO_PJ0_U4RX);
        GPIOPinConfigure(GPIO_PJ1_U4TX);

        UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART4_BASE);
    }

    if(uart==uart5)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTJ_BASE, GPIO_PIN_2|GPIO_PIN_3);
        GPIOPinConfigure(GPIO_PJ2_U5RX);
        GPIOPinConfigure(GPIO_PJ3_U5TX);

        UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART5_BASE);
    }
    
    if(uart==uart6)
    {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
        SysCtlDelay(50);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlDelay(50);

        GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4|GPIO_PIN_5);
        GPIOPinConfigure(GPIO_PD4_U6RX);
        GPIOPinConfigure(GPIO_PD5_U6TX);

        UARTConfigSetExpClk(UART6_BASE, SysCtlClockGet(), baud, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
        UARTFIFODisable(UART6_BASE);
    }
}
void uart_init_rxint(uint32_t uart, int baud, void (*uarthandler)(void))
{
    if(uart==uart0)
    {
        uart_init(uart0, baud);
        UARTDisable(UART0_BASE);
        UARTIntEnable(UART0_BASE, UART_INT_RX);
        UARTIntRegister(UART0_BASE, uarthandler);
        UARTEnable(UART0_BASE);
        //UARTFIFODisable(UART0_BASE);
    }

    if(uart==uart1)
    {
        uart_init(uart1, baud);
        UARTDisable(UART1_BASE);
        UARTIntEnable(UART1_BASE, UART_INT_RX);
        UARTIntRegister(UART1_BASE, uarthandler);
        UARTEnable(UART1_BASE);
        //UARTFIFODisable(UART1_BASE);
    }

    if(uart==uart2)
    {
        uart_init(uart2, baud);
        UARTDisable(UART2_BASE);
        UARTIntEnable(UART2_BASE, UART_INT_RX);
        UARTIntRegister(UART2_BASE, uarthandler);
        UARTEnable(UART2_BASE);
        //UARTFIFODisable(UART2_BASE);
    }

    if(uart==uart3)
    {
        uart_init(uart3, baud);
        UARTDisable(UART3_BASE);
        UARTIntEnable(UART3_BASE, UART_INT_RX);
        UARTIntRegister(UART3_BASE, uarthandler);
        UARTEnable(UART3_BASE);
        //UARTFIFODisable(UART3_BASE);
    }

    if(uart==uart4)
    {
        uart_init(uart4, baud);
        UARTDisable(UART4_BASE);
        UARTIntEnable(UART4_BASE, UART_INT_RX);
        UARTIntRegister(UART4_BASE, uarthandler);
        UARTEnable(UART4_BASE);
        //UARTFIFODisable(UART4_BASE);
    }

    if(uart==uart5)
    {
        uart_init(uart5, baud);
        UARTDisable(UART5_BASE);
        UARTIntEnable(UART5_BASE, UART_INT_RX);
        UARTIntRegister(UART5_BASE, uarthandler);
        UARTEnable(UART5_BASE);
        //UARTFIFODisable(UART5_BASE);
    }
    
    if(uart==uart6)
    {
        uart_init(uart6, baud);
        UARTDisable(UART6_BASE);
        UARTIntEnable(UART6_BASE, UART_INT_RX);
        UARTIntRegister(UART6_BASE, uarthandler);
        UARTEnable(UART6_BASE);
        //UARTFIFODisable(UART6_BASE);
    }
}

void uart_transmit(uint32_t uart, int8_t data)
{
    UARTCharPut(uart, data);
}

int uart_receive(uint32_t uart)
{
    int data_rx=0;
    data_rx=UARTCharGetNonBlocking(uart);
    if(data_rx==-1)
    {
        return -1;
    }
    else
    {
        data_rx=data_rx&0xFF;
    }

    return data_rx;
}

#endif /* UART_H_ */
