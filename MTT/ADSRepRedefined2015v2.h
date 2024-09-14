/*
 * ADSRepRedefined2015v2.h
 *
 *  Created on: Aug 30, 2018
 *      Author: Varun
 */

#ifndef ADSREPREDEFINED2015V2_H_
#define ADSREPREDEFINED2015V2_H_


/************************************************************************************************************************************************
 *                                                                                                                                              *
 *                                                                                                                                              *
 *                                                       MiT  Tech Team                                                                         *
 *                                                              - ADs Rep Redefined 2015  -> Coded 22/01/2015                                   *
 *                                                                                                                                              *
 *                                                                                                                                              *
 *                                                                                                                                              *
 *                                                      /\              /\                                                                      *
 *                                                     /  \            /  \                                                                     *
 *                                                    /    \          /    \                                                                    *
 *                                                   /      \        /      \                                                                   *
 *                                                  /        \      /        \                                                                  *
 *                                                 /          \    /          \                                                                 *
 *                                              __/            \__/            \____                                                            *
 *                                                                                                                                              *
 *                                                                                                                                              *
 *************************************************************************************************************************************************/
#define Kp 4 // Do not touch this value for base frame

#define REP_On 1
#define REP_Off 0

#include"stdint.h"
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/pin_map.h"
#include"driverlib/gpio.h"
#include"driverlib/sysctl.h"
#include"driverlib/pwm.h"
#include"MTT/pwm.h"
#include"MTT/uart.h"
#include"MTT/pid.h"
#include"MTT/timer.h"

///////////////// Rep Variables /////////////////////////////////////////////////////////////////////////////////////

#define h0 1
#define h4 2
#define g2 7

#define h0_lmd 3
#define h3_lmd 4
#define h4_lmd 5
#define h7_lmd 6

#define h0_cytron 8
#define h4_cytron 9
#define h3_cytron 10
#define h6_cytron 11

////////////////////////////Motor 1/////////////////////////
struct motor{
volatile unsigned char prev_count1;
volatile unsigned char flag;
volatile unsigned char flag1;
volatile int count1_accumulated;
volatile int count1_accumulated_temp;
volatile int count1;
volatile int Corrected_Rpm_1;
volatile int corr1;
volatile int Motor1_Required_Rpm;
volatile uint8_t port;
volatile int max_duty;
volatile int pos_control_dir;
}

motor_h0={0,0,0,0,0,0,0,0,0,h0,2370,1},
motor_h4={0,0,0,0,0,0,0,0,0,h4,2370,1},
motor_h0_lmd={0,0,0,0,0,0,0,0,0,h0_lmd,2370,1},
motor_h3_lmd={0,0,0,0,0,0,0,0,0,h3_lmd,2370,1},
motor_h4_lmd={0,0,0,0,0,0,0,0,0,h4_lmd,2370,1},
motor_h7_lmd={0,0,0,0,0,0,0,0,0,h7_lmd,2370,1},
motor_h0_cytron={0,0,0,0,0,0,0,0,0,h0_cytron,3800,1},
motor_h4_cytron={0,0,0,0,0,0,0,0,0,h4_cytron,3800,1},
motor_h3_cytron={0,0,0,0,0,0,0,0,0,h3_cytron,3800,1},
motor_h6_cytron={0,0,0,0,0,0,0,0,0,h6_cytron,3800,1};

///////////////////////////////////////////////////////////////////////


struct motor new_motor(uint8_t);
void rep_init(void(*isrhandler)(void));
void pwm_duty_rep(uint32_t*, int, int, int);
void mosfet_H0_init(void);
void mosfet_H4_init(void);
void lmd_H0_init(void);
void lmd_H3_init(void);
void lmd_H4_init(void);
void lmd_H7_init(void);

void cytron_H0_init(void);
void cytron_H4_init(void);
void cytron_H3_init(void);
void cytron_H6_init(void);

void motor_H0_clockwise(float, int);
void motor_H4_clockwise(float, int);
void motor_H0_clockwise_lmd(float, int);
void motor_H3_clockwise_lmd(float, int);
void motor_H4_clockwise_lmd(float, int);
void motor_H7_clockwise_lmd(float, int);

void motor_H0_clockwise_cytron(float, int);
void motor_H4_clockwise_cytron(float, int);
void motor_H3_clockwise_cytron(float, int);
void motor_H6_clockwise_cytron(float, int);

void motor_H0_anticlockwise(float, int);
void motor_H4_anticlockwise(float, int);
void motor_H0_anticlockwise_lmd(float, int);
void motor_H3_anticlockwise_lmd(float, int);
void motor_H4_anticlockwise_lmd(float, int);
void motor_H7_anticlockwise_lmd(float, int);

void motor_H0_anticlockwise_cytron(float, int);
void motor_H4_anticlockwise_cytron(float, int);
void motor_H3_anticlockwise_cytron(float, int);
void motor_H6_anticlockwise_cytron(float, int);

void Motor1_Clockwise(int, int, uint8_t);
void Motor1_AntiClockwise(float, int, uint8_t);

int Rpm_Motor_control(int, struct motor*, int);
int motor_position_control(int, int, struct motor*, pid*, int);

struct motor new_motor(uint8_t port)
{
    struct motor m1;
    m1.Corrected_Rpm_1=0;
    m1.Motor1_Required_Rpm=0;
    m1.corr1=0;
    m1.count1=0;
    m1.count1_accumulated=0;
    m1.count1_accumulated_temp=0;
    m1.flag=0;
    m1.flag1=0;
    m1.prev_count1=0;
    m1.port=port;
    m1.max_duty=2370;
    m1.pos_control_dir=1;
    return m1;
}

void rep_init(void(*isrhandler)(void))
{
    timer_init(timer1, 770, isrhandler);
}

void ig32_rep_init(void(*isrhandler)(void))
{
    timer_init_B(timer1, 550, isrhandler);
}

void pwm_duty_rep(uint32_t* pin, int duty, int rep_state, int deadband)
{
    float load_reg_value;

    if(deadband)
        PWMDeadBandEnable(pin[0], pin[1], 0x30, 0x30);
    else
        PWMDeadBandDisable(pin[0], pin[1]);

    if((!rep_state) && (duty == 100))
    {
        load_reg_value=PWMGenPeriodGet(pin[0], pin[1]);
        duty = load_reg_value - 1;
    }
    else if((!rep_state) && (duty == 0))
        duty = 0;
    else if(!rep_state)
    {
        load_reg_value=PWMGenPeriodGet(pin[0], pin[1]);
        duty=(load_reg_value*duty)/100.0;
    }

    PWMPulseWidthSet(pin[0], pin[2], duty);
}

void mosfet_H0_init(void)
{
    pwm_init(H0, 32000, 0);
    pwm_init(H1, 32000, 0);
    pwm_init(H2, 32000, 0);
    pwm_init(H3, 32000, 0);
}

void mosfet_H4_init(void)
{
    pwm_init(H4, 32000, 0);
    pwm_init(H5, 32000, 0);
    pwm_init(H6, 32000, 0);
    pwm_init(H7, 32000, 0);
}

void mosfet_G2_init(void)
{
    pwm_init(G2, 32000, 0);
    pwm_init(G3, 32000, 0);
    pwm_init(G4_MOD1, 32000, 0);
    pwm_init(G5_MOD1, 32000, 0);
}

void lmd_H0_init(void)
{
    pwm_init(H0, 32000, 0);
    output(porth_gpio, GPIO_PIN_1|GPIO_PIN_2);
    reset_pins(porth_gpio, GPIO_PIN_1|GPIO_PIN_2);
}

void lmd_H3_init(void)
{
    pwm_init(H3, 32000, 0);
    output(portk_gpio, GPIO_PIN_1|GPIO_PIN_2);
    reset_pins(portk_gpio, GPIO_PIN_1|GPIO_PIN_2);
}

void lmd_H4_init(void)
{
    pwm_init(H4, 32000, 0);
    output(porth_gpio, GPIO_PIN_5|GPIO_PIN_6);
    reset_pins(porth_gpio, GPIO_PIN_5|GPIO_PIN_6);
}

void lmd_H7_init(void)
{
    pwm_init(H7, 32000, 0);
    output(portn_gpio, GPIO_PIN_2);
    output(portk_gpio, GPIO_PIN_3);
    reset_pins(portn_gpio, GPIO_PIN_2);
    reset_pins(portk_gpio, GPIO_PIN_3);
}

void cytron_H0_init(void)
{
    pwm_init(H0, 20000, 0);
    output(porth_gpio, GPIO_PIN_1);
    reset_pins(porth_gpio, GPIO_PIN_1);
}

void cytron_H4_init(void)
{
    pwm_init(H4, 20000, 0);
    output(porth_gpio, GPIO_PIN_5);
    reset_pins(porth_gpio, GPIO_PIN_5);
}

void cytron_H3_init(void)
{
    pwm_init(H3, 20000, 0);
    output(portk_gpio, GPIO_PIN_2);
    reset_pins(portk_gpio, GPIO_PIN_2);
}

void cytron_H6_init(void)
{
    pwm_init(H6, 20000, 0);
    output(porth_gpio, GPIO_PIN_7);
    reset_pins(porth_gpio, GPIO_PIN_7);
}

void motor_H0_anticlockwise(float duty, int rep_state)
{

    pwm_duty_rep(H0, duty, rep_state, 1);
    pwm_duty_rep(H2, 0, 0, 0);
    pwm_duty_rep(H3, 100, 0, 0);

}

void motor_H0_clockwise(float duty, int rep_state)
{
    pwm_duty_rep(H2, duty, rep_state, 1);
    pwm_duty_rep(H0, 0, 0, 0);
    pwm_duty_rep(H1, 100, 0, 0);

}

void motor_H4_anticlockwise(float duty, int rep_state)
{
    pwm_duty_rep(H4, duty, rep_state, 1);
    pwm_duty_rep(H6, 0, 0, 0);
    pwm_duty_rep(H7, 100, 0, 0);

}

void motor_H4_clockwise(float duty, int rep_state)
{
    pwm_duty_rep(H6, duty, rep_state, 1);
    pwm_duty_rep(H4, 0, 0, 0);
    pwm_duty_rep(H5, 100, 0, 0);

}

void motor_G2_anticlockwise(float duty, int rep_state)
{
    pwm_duty_rep(G2, duty, rep_state, 1);
    pwm_duty_rep(G4_MOD1, 0, 0, 0);
    pwm_duty_rep(G5_MOD1, 100, 0, 0);

}

void motor_G4_clockwise(float duty, int rep_state)
{
    pwm_duty_rep(G4_MOD1, duty, rep_state, 1);
    pwm_duty_rep(G2, 0, 0, 0);
    pwm_duty_rep(G3, 100, 0, 0);

}

void motor_H0_anticlockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H0, duty, rep_state, 0);
    reset_pins(porth_gpio, PIN1);
}

void motor_H0_clockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H0, duty, rep_state, 0);
    set_pins(porth_gpio, PIN1);
}

void motor_H3_anticlockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H3, duty, rep_state, 0);
    reset_pins(portk_gpio, PIN2);
}

void motor_H3_clockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H3, duty, rep_state, 0);
    set_pins(portk_gpio, PIN2);
}

void motor_H4_anticlockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H4, duty, rep_state, 0);
    reset_pins(porth_gpio, PIN5);
}

void motor_H4_clockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H4, duty, rep_state, 0);
    set_pins(porth_gpio, PIN5);
}

void motor_H7_anticlockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H7, duty, rep_state, 0);
    reset_pins(portn_gpio, PIN2);
}

void motor_H7_clockwise_lmd(float duty, int rep_state)
{
    pwm_duty_rep(H7, duty, rep_state, 0);
    set_pins(portn_gpio, PIN2);
}

void motor_H0_anticlockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H0, duty, rep_state, 0);
    reset_pins(porth_gpio, PIN1);
}

void motor_H0_clockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H0, duty, rep_state, 0);
    set_pins(porth_gpio, PIN1);
}

void motor_H4_anticlockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H4, duty, rep_state, 0);
    reset_pins(porth_gpio, PIN5);
}

void motor_H4_clockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H4, duty, rep_state, 0);
    set_pins(porth_gpio, PIN5);
}

void motor_H3_anticlockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H3, duty, rep_state, 0);
    reset_pins(portk_gpio, PIN2);
}

void motor_H3_clockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H3, duty, rep_state, 0);
    set_pins(portk_gpio, PIN2);
}

void motor_H6_anticlockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H6, duty, rep_state, 0);
    reset_pins(porth_gpio, PIN7);
}

void motor_H6_clockwise_cytron(float duty, int rep_state)
{
    pwm_duty_rep(H6, duty, rep_state, 0);
    set_pins(porth_gpio, PIN7);
}

void Motor1_Clockwise(int duty, int rep_state, uint8_t port)
{
    switch(port)
    {
    case h0:
        pwm_duty_rep(H2, duty, rep_state, 1);
        pwm_duty_rep(H0, 0, 0, 0);
        pwm_duty_rep(H1, 100, 0, 0);
        break;
    case h4:
        pwm_duty_rep(H6, duty, rep_state, 1);
        pwm_duty_rep(H4, 0, 0, 0);
        pwm_duty_rep(H5, 100, 0, 0);
        break;
    case g2:
        pwm_duty_rep(G4_MOD1, duty, rep_state, 1);
        pwm_duty_rep(G2, 0, 0, 0);
        pwm_duty_rep(G3, 100, 0, 0);
        break;
    case h0_lmd:
        pwm_duty_rep(H0, duty, rep_state, 0);
        set_pins(porth_gpio, PIN1);
        break;
    case h3_lmd:
        pwm_duty_rep(H3, duty, rep_state, 0);
        set_pins(portk_gpio, PIN2);
        break;
    case h4_lmd:
        pwm_duty_rep(H4, duty, rep_state, 0);
        set_pins(porth_gpio, PIN5);
        break;
    case h7_lmd:
        pwm_duty_rep(H7, duty, rep_state, 0);
        set_pins(portn_gpio, PIN2);
        break;
    case h0_cytron:
        pwm_duty_rep(H0, duty, rep_state, 0);
        set_pins(porth_gpio, PIN1);
        break;
    case h4_cytron:
        pwm_duty_rep(H4, duty, rep_state, 0);
        set_pins(porth_gpio, PIN5);
        break;
    case h3_cytron:
        pwm_duty_rep(H3, duty, rep_state, 0);
        set_pins(portk_gpio, PIN2);
        break;
    case h6_cytron:
        pwm_duty_rep(H6, duty, rep_state, 0);
        set_pins(porth_gpio, PIN7);
        break;
    default:
        break;
    }
}

void Motor1_AntiClockwise(float duty, int rep_state, uint8_t port)
{
    switch(port)
    {
    case h0:
        pwm_duty_rep(H0, duty, rep_state, 1);
        pwm_duty_rep(H2, 0, 0, 0);
        pwm_duty_rep(H3, 100, 0, 0);
        break;
    case h4:
        pwm_duty_rep(H4, duty, rep_state, 1);
        pwm_duty_rep(H6, 0, 0, 0);
        pwm_duty_rep(H7, 100, 0, 0);
        break;
    case g2:
        pwm_duty_rep(G2, duty, rep_state, 1);
        pwm_duty_rep(G4_MOD1, 0, 0, 0);
        pwm_duty_rep(G5_MOD1, 100, 0, 0);
        break;
    case h0_lmd:
        pwm_duty_rep(H0, duty, rep_state, 0);
        GPIOPinWrite(porth_gpio, PIN1, ~PIN1);
        break;
    case h3_lmd:
        pwm_duty_rep(H3, duty, rep_state, 0);
        GPIOPinWrite(portk_gpio, PIN2, ~PIN2);
        break;
    case h4_lmd:
        pwm_duty_rep(H4, duty, rep_state, 0);
        GPIOPinWrite(porth_gpio, PIN5, ~PIN5);
        break;
    case h7_lmd:
        pwm_duty_rep(H7, duty, rep_state, 0);
        GPIOPinWrite(portn_gpio, PIN2, ~PIN2);
        break;
    case h0_cytron:
        pwm_duty_rep(H0, duty, rep_state, 0);
        reset_pins(porth_gpio, PIN1);
        break;
    case h4_cytron:
        pwm_duty_rep(H4, duty, rep_state, 0);
        reset_pins(porth_gpio, PIN5);
        break;
    case h3_cytron:
        pwm_duty_rep(H3, duty, rep_state, 0);
        reset_pins(portk_gpio, PIN2);
        break;
    case h6_cytron:
        pwm_duty_rep(H6, duty, rep_state, 0);
        reset_pins(porth_gpio, PIN7);
        break;
    default:
        break;
    }
}

int Rpm_Motor_control(int rpm, struct motor *motor1, int Current_Motor1_Rpm)
{
    motor1->Motor1_Required_Rpm = (int)(rpm);

    if(Current_Motor1_Rpm>motor1->Motor1_Required_Rpm)
    {
      motor1->flag1=1;
      motor1->corr1=(Current_Motor1_Rpm-motor1->Motor1_Required_Rpm)/Kp +1;
    }

    else if(Current_Motor1_Rpm<motor1->Motor1_Required_Rpm)
    {

     motor1->flag1^=motor1->flag1;
     motor1->corr1=(motor1->Motor1_Required_Rpm-Current_Motor1_Rpm)/Kp +1;

    }
    else
        motor1->corr1^=motor1->corr1;

    if(motor1->Motor1_Required_Rpm==0)
    {
        if((Current_Motor1_Rpm>motor1->Motor1_Required_Rpm&&Current_Motor1_Rpm>motor1->prev_count1)||(Current_Motor1_Rpm<motor1->Motor1_Required_Rpm&&Current_Motor1_Rpm<motor1->prev_count1))
        motor1->corr1+=3;
    }


    if(motor1->flag)
    {
       if(motor1->flag1)
        motor1->Corrected_Rpm_1-=motor1->corr1;
        else
        motor1->Corrected_Rpm_1+=motor1->corr1;

        if(motor1->Corrected_Rpm_1>motor1->max_duty)
        motor1->Corrected_Rpm_1=motor1->max_duty;
        else if(motor1->Corrected_Rpm_1<0)
        {
        motor1->flag^=motor1->flag;
        motor1->Corrected_Rpm_1^=motor1->Corrected_Rpm_1;
        }

        Motor1_AntiClockwise(motor1->Corrected_Rpm_1,REP_On, motor1->port);
    }

    else
    {
        if(motor1->flag1)
        motor1->Corrected_Rpm_1 +=motor1->corr1;
        else
        motor1->Corrected_Rpm_1 -=motor1->corr1;

        if(motor1->Corrected_Rpm_1>motor1->max_duty)
        motor1->Corrected_Rpm_1=motor1->max_duty;
        else if(motor1->Corrected_Rpm_1<0)
        {
          motor1->flag=1;
          motor1->Corrected_Rpm_1 ^=motor1->Corrected_Rpm_1;
        }

        Motor1_Clockwise(motor1->Corrected_Rpm_1,REP_On, motor1->port);
    }

    motor1->prev_count1=Current_Motor1_Rpm;
    motor1->count1_accumulated +=Current_Motor1_Rpm;
    Current_Motor1_Rpm^=Current_Motor1_Rpm;

    return motor1->Corrected_Rpm_1;
}

int motor_position_control(int req_cnt, int current_cnt, struct motor *motor1, pid *motor_position_control, int max_rpm)
{
    int req_rpm, cnt_error = 0;

    cnt_error=(req_cnt-current_cnt)*motor1->pos_control_dir;
    pid_update(motor_position_control, cnt_error);

    if(motor_position_control->output>max_rpm)
        req_rpm=max_rpm;
    else if(motor_position_control->output<-max_rpm)
        req_rpm=-max_rpm;
    else
        req_rpm=motor_position_control->output;

    return req_rpm;
}
#endif /* ADSREPREDEFINED2015V2_H_ */
