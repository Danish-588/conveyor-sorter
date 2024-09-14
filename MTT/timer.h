/*
 * timer.h
 *
 *  Created on: Jul 1, 2018
 *      Author: Varun
 */

#ifndef TIMER_H_
#define TIMER_H_

#include"driverlib/sysctl.h"
#include"driverlib/timer.h"
#include"driverlib/interrupt.h"

#define timer0 TIMER0_BASE
#define timer1 TIMER1_BASE
#define timer2 TIMER2_BASE
#define timer3 TIMER3_BASE

void timer_init(uint32_t timer, float freq, void (*timerhandler)(void))
{
    if(timer==timer0)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    else if(timer==timer1)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    else if(timer==timer2)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    else if(timer==timer3)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

    SysCtlDelay(50);

    TimerConfigure(timer, TIMER_CFG_PERIODIC);
    TimerLoadSet(timer, TIMER_A, ((SysCtlClockGet()/freq)-1));
    TimerIntEnable(timer, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(timer, TIMER_A, timerhandler);
    TimerEnable(timer, TIMER_A);
}
void timer_init_B(uint32_t timer, float freq, void (*timerhandler)(void))
{
    if(timer==timer0)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    else if(timer==timer1)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    else if(timer==timer2)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    else if(timer==timer3)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

    SysCtlDelay(50);

    TimerConfigure(timer, TIMER_CFG_PERIODIC);
    TimerLoadSet(timer, TIMER_B, ((SysCtlClockGet()/freq)-1));
    TimerIntEnable(timer, TIMER_TIMB_TIMEOUT);
    TimerIntRegister(timer, TIMER_B, timerhandler);
    TimerEnable(timer, TIMER_B);
}


#endif /* TIMER_H_ */
