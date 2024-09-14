/*
 * 80mhz.h
 *
 *  Created on: Jun 30, 2018
 *      Author: Robocon
 */
#include<stdbool.h>
#include"driverlib/sysctl.h"

void System80Mhz(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}

void delay_ms(float ms)
{
	SysCtlDelay((SysCtlClockGet()/3000)*ms);
}

void delay(int clock_cycles)
{
	SysCtlDelay(clock_cycles);
}
