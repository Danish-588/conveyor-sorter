/*
 * PulseWidth.h
 *
 *  Created on: Jul 1, 2018
 *      Author: Varun
 */

#ifndef PWM_H_
#define PWM_H_

#include"stdint.h"
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/pin_map.h"
#include"driverlib/gpio.h"
#include"driverlib/sysctl.h"
#include"driverlib/pwm.h"
#include"math.h"

/*======================================================Settings for PINs====================================================*/

/*---------------------------------------------------------MODULE 0----------------------------------------------------------*/

uint32_t H0[8] = {PWM0_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_0_BIT, GPIO_PORTH_BASE, GPIO_PH0_M0PWM0, GPIO_PIN_0, SYSCTL_PERIPH_GPIOH};
uint32_t P0[8] = {PWM0_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_0_BIT, GPIO_PORTP_BASE, GPIO_PP0_M0PWM0, GPIO_PIN_0, SYSCTL_PERIPH_GPIOP};

uint32_t H1[8] = {PWM0_BASE, PWM_GEN_0, PWM_OUT_1, PWM_OUT_1_BIT, GPIO_PORTH_BASE, GPIO_PH1_M0PWM1, GPIO_PIN_1, SYSCTL_PERIPH_GPIOH};
uint32_t P1[8] = {PWM0_BASE, PWM_GEN_0, PWM_OUT_1, PWM_OUT_1_BIT, GPIO_PORTP_BASE, GPIO_PP1_M0PWM1, GPIO_PIN_1, SYSCTL_PERIPH_GPIOP};

uint32_t H2[8] = {PWM0_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_2_BIT, GPIO_PORTH_BASE, GPIO_PH2_M0PWM2, GPIO_PIN_2, SYSCTL_PERIPH_GPIOH};
uint32_t P2[8] = {PWM0_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_2_BIT, GPIO_PORTP_BASE, GPIO_PP2_M0PWM2, GPIO_PIN_2, SYSCTL_PERIPH_GPIOP};
uint32_t B4[8] = {PWM0_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_2_BIT, GPIO_PORTB_BASE, GPIO_PB4_M0PWM2, GPIO_PIN_4, SYSCTL_PERIPH_GPIOB};

uint32_t H3[8] = {PWM0_BASE, PWM_GEN_1, PWM_OUT_3, PWM_OUT_3_BIT, GPIO_PORTH_BASE, GPIO_PH3_M0PWM3, GPIO_PIN_3, SYSCTL_PERIPH_GPIOH};
uint32_t B5[8] = {PWM0_BASE, PWM_GEN_1, PWM_OUT_3, PWM_OUT_3_BIT, GPIO_PORTB_BASE, GPIO_PB5_M0PWM3, GPIO_PIN_5, SYSCTL_PERIPH_GPIOB};

uint32_t H4[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_4_BIT, GPIO_PORTH_BASE, GPIO_PH4_M0PWM4, GPIO_PIN_4, SYSCTL_PERIPH_GPIOH};
uint32_t G4[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_4_BIT, GPIO_PORTG_BASE, GPIO_PG4_M0PWM4, GPIO_PIN_4, SYSCTL_PERIPH_GPIOG};
uint32_t M6[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_4_BIT, GPIO_PORTM_BASE, GPIO_PM6_M0PWM4, GPIO_PIN_6, SYSCTL_PERIPH_GPIOM};
uint32_t E4[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_4_BIT, GPIO_PORTE_BASE, GPIO_PE4_M0PWM4, GPIO_PIN_4, SYSCTL_PERIPH_GPIOE};

uint32_t H5[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT, GPIO_PORTH_BASE, GPIO_PH5_M0PWM5, GPIO_PIN_5, SYSCTL_PERIPH_GPIOH};
uint32_t G5[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT, GPIO_PORTG_BASE, GPIO_PG5_M0PWM5, GPIO_PIN_5, SYSCTL_PERIPH_GPIOG};
uint32_t M7[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT, GPIO_PORTM_BASE, GPIO_PM7_M0PWM5, GPIO_PIN_7, SYSCTL_PERIPH_GPIOM};
uint32_t E5[8] = {PWM0_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT, GPIO_PORTE_BASE, GPIO_PE5_M0PWM5, GPIO_PIN_5, SYSCTL_PERIPH_GPIOE};

uint32_t H6[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTH_BASE, GPIO_PH6_M0PWM6, GPIO_PIN_6, SYSCTL_PERIPH_GPIOH};
uint32_t D0[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTD_BASE, GPIO_PD0_M0PWM6, GPIO_PIN_0, SYSCTL_PERIPH_GPIOD};
uint32_t N2[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTN_BASE, GPIO_PN2_M0PWM6, GPIO_PIN_2, SYSCTL_PERIPH_GPION};
uint32_t C4[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTC_BASE, GPIO_PC4_M0PWM6, GPIO_PIN_4, SYSCTL_PERIPH_GPIOC};
uint32_t G6[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTG_BASE, GPIO_PG6_M0PWM6, GPIO_PIN_6, SYSCTL_PERIPH_GPIOG};

uint32_t H7[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTH_BASE, GPIO_PH7_M0PWM7, GPIO_PIN_7, SYSCTL_PERIPH_GPIOH};
uint32_t D1[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTD_BASE, GPIO_PD1_M0PWM7, GPIO_PIN_1, SYSCTL_PERIPH_GPIOD};
uint32_t N3[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTN_BASE, GPIO_PN3_M0PWM7, GPIO_PIN_3, SYSCTL_PERIPH_GPION};
uint32_t C5[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTC_BASE, GPIO_PC5_M0PWM7, GPIO_PIN_5, SYSCTL_PERIPH_GPIOC};
uint32_t G7[8] = {PWM0_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTG_BASE, GPIO_PG7_M0PWM7, GPIO_PIN_7, SYSCTL_PERIPH_GPIOG};

/*---------------------------------------------------------MODULE 1----------------------------------------------------------*/

uint32_t D0_MOD1[8] = {PWM1_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_0_BIT, GPIO_PORTD_BASE, GPIO_PD0_M1PWM0, GPIO_PIN_0, SYSCTL_PERIPH_GPIOD};
uint32_t G2[8] = {PWM1_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_0_BIT, GPIO_PORTG_BASE, GPIO_PG2_M1PWM0, GPIO_PIN_2, SYSCTL_PERIPH_GPIOG};

uint32_t D1_MOD1[8] = {PWM1_BASE, PWM_GEN_0, PWM_OUT_1, PWM_OUT_1_BIT, GPIO_PORTD_BASE, GPIO_PD1_M1PWM1, GPIO_PIN_1, SYSCTL_PERIPH_GPIOD};
uint32_t G3[8] = {PWM1_BASE, PWM_GEN_0, PWM_OUT_1, PWM_OUT_1_BIT, GPIO_PORTG_BASE, GPIO_PG3_M1PWM1, GPIO_PIN_3, SYSCTL_PERIPH_GPIOG};

uint32_t A6[8] = {PWM1_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_2_BIT, GPIO_PORTA_BASE, GPIO_PA6_M1PWM2, GPIO_PIN_6, SYSCTL_PERIPH_GPIOA};
uint32_t G4_MOD1[8] = {PWM1_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_2_BIT, GPIO_PORTG_BASE, GPIO_PG4_M1PWM2, GPIO_PIN_4, SYSCTL_PERIPH_GPIOG};
uint32_t E4_MOD1[8] = {PWM1_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_2_BIT, GPIO_PORTE_BASE, GPIO_PE4_M1PWM2, GPIO_PIN_4, SYSCTL_PERIPH_GPIOE};

uint32_t A7[8] = {PWM1_BASE, PWM_GEN_1, PWM_OUT_3, PWM_OUT_3_BIT, GPIO_PORTA_BASE, GPIO_PA7_M1PWM3, GPIO_PIN_7, SYSCTL_PERIPH_GPIOA};
uint32_t G5_MOD1[8] = {PWM1_BASE, PWM_GEN_1, PWM_OUT_3, PWM_OUT_3_BIT, GPIO_PORTG_BASE, GPIO_PG5_M1PWM3, GPIO_PIN_5, SYSCTL_PERIPH_GPIOG};
uint32_t E5_MOD1[8] = {PWM1_BASE, PWM_GEN_1, PWM_OUT_3, PWM_OUT_3_BIT, GPIO_PORTE_BASE, GPIO_PE5_M1PWM3, GPIO_PIN_5, SYSCTL_PERIPH_GPIOE};

uint32_t F0[8] = {PWM1_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_4_BIT, GPIO_PORTF_BASE, GPIO_PF0_M1PWM4, GPIO_PIN_0, SYSCTL_PERIPH_GPIOF};
uint32_t N4[8] = {PWM1_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_4_BIT, GPIO_PORTN_BASE, GPIO_PN4_M1PWM4, GPIO_PIN_4, SYSCTL_PERIPH_GPION};

uint32_t F1[8] = {PWM1_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT, GPIO_PORTF_BASE, GPIO_PF1_M1PWM5, GPIO_PIN_1, SYSCTL_PERIPH_GPIOF};
uint32_t N5[8] = {PWM1_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT, GPIO_PORTN_BASE, GPIO_PN5_M1PWM5, GPIO_PIN_5, SYSCTL_PERIPH_GPION};

uint32_t F2[8] = {PWM1_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTF_BASE, GPIO_PF2_M1PWM6, GPIO_PIN_2, SYSCTL_PERIPH_GPIOF};
uint32_t N6[8] = {PWM1_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT, GPIO_PORTN_BASE, GPIO_PN6_M1PWM6, GPIO_PIN_6, SYSCTL_PERIPH_GPION};

uint32_t F3[8] = {PWM1_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTF_BASE, GPIO_PF3_M1PWM7, GPIO_PIN_3, SYSCTL_PERIPH_GPIOF};
uint32_t N7[8] = {PWM1_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT, GPIO_PORTN_BASE, GPIO_PN7_M1PWM7, GPIO_PIN_7, SYSCTL_PERIPH_GPION};

/*===========================================================================================================================*/

void pwm_duty(uint32_t* pin, float freq, int duty, int rep_state, int deadband)
{
    long int pwm_clock=0;
    float load_reg_value, divisor;

    if(deadband)
        PWMDeadBandEnable(pin[0], pin[1], 0x30, 0x30);
    else
        PWMDeadBandDisable(pin[0], pin[1]);

    load_reg_value=round(SysCtlClockGet()/freq);
    if(load_reg_value>65535)
    {
        divisor=load_reg_value/65535;
        if(divisor<=2)
            SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
        else if((divisor>2) && (divisor<=4))
            SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
        else if((divisor>4) && (divisor<=8))
            SysCtlPWMClockSet(SYSCTL_PWMDIV_8);
        else if((divisor>8) && (divisor<=16))
            SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
        else if((divisor>16) && (divisor<=32))
            SysCtlPWMClockSet(SYSCTL_PWMDIV_32);
        else if((divisor>32) && (divisor<=64))
            SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
        else
            SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    }

    pwm_clock=SysCtlPWMClockGet();

    switch(pwm_clock)
    {
    case SYSCTL_PWMDIV_1:
        load_reg_value=round(SysCtlClockGet()/(freq*1));
        break;
    case SYSCTL_PWMDIV_2:
        load_reg_value=round(SysCtlClockGet()/(freq*2));
        break;
    case SYSCTL_PWMDIV_4:
        load_reg_value=round(SysCtlClockGet()/(freq*4));
        break;
    case SYSCTL_PWMDIV_8:
        load_reg_value=round(SysCtlClockGet()/(freq*8));
        break;
    case SYSCTL_PWMDIV_16:
        load_reg_value=round(SysCtlClockGet()/(freq*16));
        break;
    case SYSCTL_PWMDIV_32:
        load_reg_value=round(SysCtlClockGet()/(freq*32));
        break;
    case SYSCTL_PWMDIV_64:
        load_reg_value=round(SysCtlClockGet()/(freq*64));
        break;
    }

    if(load_reg_value!=PWMGenPeriodGet(pin[0], pin[1]));
        PWMGenPeriodSet(pin[0], pin[1], load_reg_value);

    if(!rep_state)
        duty=(load_reg_value*duty)/100.0;

    if(duty==load_reg_value)
        duty=duty-1;
    PWMPulseWidthSet(pin[0], pin[2], duty);
}

void pwm_init(uint32_t* pin, float frequency, float duty)
{
    if(pin[0]==PWM0_BASE)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    else
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlDelay(50);
    SysCtlPeripheralEnable(pin[7]);
    SysCtlDelay(50);

    PWMGenConfigure(pin[0], pin[1], PWM_GEN_MODE_UP_DOWN);

    pwm_duty(pin, frequency, duty, 1, 0);
    PWMOutputState(pin[0], pin[3], true);
    PWMGenEnable(pin[0], pin[1]);

    GPIOPinTypePWM(pin[4], pin[6]);
    GPIOPinConfigure(pin[5]);
}

#endif /* PWM_H_ */
