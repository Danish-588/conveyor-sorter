/*
 * gpio.h
 *
 *  Created on: Jun 30, 2018
 *      Author: Varun
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"inc/tm4c123gh6pge.h"
#include"driverlib/sysctl.h"
#include"driverlib/interrupt.h"

#define PIN0 0x01
#define PIN1 0x02
#define PIN2 0x04
#define PIN3 0x08
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80

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

#define high GPIO_HIGH_LEVEL
#define low  GPIO_LOW_LEVEL
#define rising GPIO_RISING_EDGE
#define falling GPIO_FALLING_EDGE

void output(uint32_t port,  uint8_t pins)
{
    if(port==porta_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);    //Enable clock
    if(port==portb_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    //Enable clock
    if(port==portc_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);    //Enable clock
    if(port==portd_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);    //Enable clock
    if(port==porte_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    //Enable clock
    if(port==portf_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    //Enable clock
    if(port==portg_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);    //Enable clock
    if(port==porth_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);    //Enable clock
    if(port==portj_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);    //Enable clock
    if(port==portk_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);    //Enable clock
    if(port==portl_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);    //Enable clock
    if(port==portm_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);    //Enable clock
    if(port==portn_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);    //Enable clock
    if(port==portp_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);    //Enable clock

    SysCtlDelay(50);    //for delay (min 5 clock cycles)
    GPIOPinTypeGPIOOutput(port, pins);   //Sets direction, DEN register, and sets PUR & PDR to 0 for specified pins
}

void input(uint32_t port,  uint8_t pins)
{
    if(port==porta_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);    //Enable clock
    if(port==portb_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    //Enable clock
    if(port==portc_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);    //Enable clock
    if(port==portd_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);    //Enable clock
    if(port==porte_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    //Enable clock
    if(port==portf_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    //Enable clock
    if(port==portg_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);    //Enable clock
    if(port==porth_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);    //Enable clock
    if(port==portj_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);    //Enable clock
    if(port==portk_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);    //Enable clock
    if(port==portl_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);    //Enable clock
    if(port==portm_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);    //Enable clock
    if(port==portn_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);    //Enable clock
    if(port==portp_gpio)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);    //Enable clock

    SysCtlDelay(50);    //for delay (min 5 clock cycles)
    GPIOPinTypeGPIOInput(port, pins);   //Sets direction, DEN register, and sets PUR & PDR to 0 for specified pins
}

void set_pins(uint32_t port, uint8_t pins)
{
    GPIOPinWrite(port, pins, pins);
}

void reset_pins(uint32_t port, uint8_t pins)
{
    GPIOPinWrite(port, pins, ~pins);
}

void pull_up(uint32_t port, uint8_t pins)
{
    GPIOPadConfigSet(port, pins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void pull_down(uint32_t port, uint8_t pins)
{
    GPIOPadConfigSet(port, pins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
}

void gpio_interrupt(uint32_t port, uint8_t pins, uint32_t type, void (*gpiohandler)(void))
{
	input(port, pins);
    GPIOIntEnable(port, pins); //Enable Interrupt for given pins
    GPIOIntTypeSet(port, pins, type);    //Set Interrupt trigger source for specified pins
    GPIOIntRegister(port, gpiohandler); //Register function as interrupt handler for given GPIO port, NVIC_ENX register is also modified in this function
}

void toggle(uint32_t port, uint8_t pins)
{
    GPIOPinWrite(port, pins, (GPIOPinRead(port, pins)^pins));
}

uint8_t read_pin(uint32_t port, uint8_t pins)
{
    int pin_state=0;
    pin_state = GPIOPinRead(port, pins);
    return pin_state;
}

void port_value(uint32_t port, uint8_t value)
{
	GPIOPinWrite(port, 0xFF, value);
}

#endif /* GPIO_H_ */
