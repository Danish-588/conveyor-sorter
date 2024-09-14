/*
 * xy.h
 *
 *  Created on: Sep 10, 2018
 *      Author: Varun
 */

#ifndef XY_H_
#define XY_H_

#include "MTT/gpio.h"
#include "MTT/timer.h"
#include "MTT/tm4c123gh6pge.h"

#define EN0A ((GPIO_PORTE_DATA_R) & (PIN1))
#define EN0B ((GPIO_PORTE_DATA_R) & (PIN0))
#define EN1A ((GPIO_PORTK_DATA_R) & (PIN0))
#define EN1B ((GPIO_PORTK_DATA_R) & (PIN1))
#define EN2A ((GPIO_PORTA_DATA_R) & (PIN7))
#define EN2B ((GPIO_PORTA_DATA_R) & (PIN6))

volatile int xy_count1_val = 0, xy_count1_val_tmp = 0, xy_count1 = 0, xy_count1_dir = 1;
volatile int xy_count2_val = 0, xy_count2_val_tmp = 0, xy_count2 = 0, xy_count2_dir = 1;
volatile int xy_count3_val = 0, xy_count3_val_tmp = 0, xy_count3 = 0, xy_count3_dir = 1;

volatile double c1, c2, c3, s1, s2, s3, k = 0, X = 0, Y = 0;
volatile double v1_xy,v2_xy, v3_xy, vx_xy, vy_xy;
volatile float velocity_x_xy=0, velocity_y_xy=0;
volatile double x_deadreckon_point = 0.0, y_deadreckon_point = 0.0;

volatile float xy_enc1_angle = 30;

uint8_t Read_Gray_EN1(void);
uint8_t Read_Gray_EN2(void);
uint8_t Read_Gray_EN3(void);

int xy_count1_Poll(void);
int xy_count2_Poll(void);
int xy_count3_Poll(void);

void calculate_xy(void);

void xy_init(float);
void xy_poll(void);

void ISR_XY()
{
    intclear(timer2);
    calculate_xy();
    xy_count1 = xy_count2 = xy_count3 = 0;
}

uint8_t Read_Gray_EN1(void)
{
    uint8_t xy_count1_val = 0;
    if (EN0A)
        xy_count1_val |= 0x02;
    if (EN0B)
        xy_count1_val |= 0x01;
    return xy_count1_val;
}

int xy_count1_Poll(void)
{
    xy_count1_val_tmp = Read_Gray_EN1();
    if (xy_count1_val != xy_count1_val_tmp)
    {
        if ((xy_count1_val == 2 && xy_count1_val_tmp == 3)
                || (xy_count1_val == 3 && xy_count1_val_tmp == 1)
                || (xy_count1_val == 1 && xy_count1_val_tmp == 0)
                || (xy_count1_val == 0 && xy_count1_val_tmp == 2))
        {
            xy_count1+=xy_count1_dir;
        }
        else if ((xy_count1_val == 3 && xy_count1_val_tmp == 2)
                || (xy_count1_val == 2 && xy_count1_val_tmp == 0)
                || (xy_count1_val == 0 && xy_count1_val_tmp == 1)
                || (xy_count1_val == 1 && xy_count1_val_tmp == 3))
        {
            xy_count1-=xy_count1_dir;
        }
        xy_count1_val = xy_count1_val_tmp;
    }
    return xy_count1;
}

uint8_t Read_Gray_EN2(void)
{
    uint8_t xy_count2_val = 0;
    if (EN1A)
        xy_count2_val |= 0x02;
    if (EN1B)
        xy_count2_val |= 0x01;
    return xy_count2_val;
}

int xy_count2_Poll(void)
{
    xy_count2_val_tmp = Read_Gray_EN2();
    if (xy_count2_val != xy_count2_val_tmp)
    {
        if ((xy_count2_val == 2 && xy_count2_val_tmp == 3)
                || (xy_count2_val == 3 && xy_count2_val_tmp == 1)
                || (xy_count2_val == 1 && xy_count2_val_tmp == 0)
                || (xy_count2_val == 0 && xy_count2_val_tmp == 2))
        {
            xy_count2+=xy_count2_dir;
        }
        else if ((xy_count2_val == 3 && xy_count2_val_tmp == 2)
                || (xy_count2_val == 2 && xy_count2_val_tmp == 0)
                || (xy_count2_val == 0 && xy_count2_val_tmp == 1)
                || (xy_count2_val == 1 && xy_count2_val_tmp == 3))
        {
            xy_count2-=xy_count2_dir;
        }
        xy_count2_val = xy_count2_val_tmp;
    }
    return xy_count2;
}

uint8_t Read_Gray_EN3(void)
{
    uint8_t xy_count3_val = 0;
    if (EN2A)
        xy_count3_val |= 0x02;
    if (EN2B)
        xy_count3_val |= 0x01;
    return xy_count3_val;
}

int xy_count3_Poll(void)
{
    xy_count3_val_tmp = Read_Gray_EN3();
    if (xy_count3_val != xy_count3_val_tmp)
    {
        if ((xy_count3_val == 2 && xy_count3_val_tmp == 3)
                || (xy_count3_val == 3 && xy_count3_val_tmp == 1)
                || (xy_count3_val == 1 && xy_count3_val_tmp == 0)
                || (xy_count3_val == 0 && xy_count3_val_tmp == 2))
        {
            xy_count3+=xy_count3_dir;
        }
        else if ((xy_count3_val == 3 && xy_count3_val_tmp == 2)
                || (xy_count3_val == 2 && xy_count3_val_tmp == 0)
                || (xy_count3_val == 0 && xy_count3_val_tmp == 1)
                || (xy_count3_val == 1 && xy_count3_val_tmp == 3))
        {
            xy_count3-=xy_count3_dir;
        }
        xy_count3_val = xy_count3_val_tmp;
    }
    return xy_count3;
}

void calculate_xy()
{
    c1 = fast_cos(angle + xy_enc1_angle);
    c2 = fast_cos(angle + xy_enc1_angle + 120);
    c3 = fast_cos(angle + xy_enc1_angle + 240);

    s1 = fast_sin(angle + xy_enc1_angle);
    s2 = fast_sin(angle + xy_enc1_angle + 120);
    s3 = fast_sin(angle + xy_enc1_angle + 240);

    k = ((s1 * c3) + (c1 * s2) + (c2 * s3) - (s1 * c2) - (s3 * c1) - (s2 * c3));

    v1_xy = 2 * 3.14 * 0.0248 * 0.0167 * xy_count1;
    v2_xy = 2 * 3.14 * 0.0248 * 0.0167 * xy_count2;
    v3_xy = 2 * 3.14 * 0.0248 * 0.0167 * xy_count3;

    vx_xy = ((c2 - c3) * v1_xy + (c3 - c1) * v2_xy + (c1 - c2) * v3_xy) / k;
    vy_xy = ((s2 - s3) * v1_xy + v2_xy * (s3 - s1) + v3_xy * (s1 - s2)) / k;

    velocity_x_xy = vx_xy;
    velocity_y_xy = vy_xy;

    X += vx_xy / 30;
    Y += vy_xy / 30;

    x = X - x_deadreckon_point;
    y = Y - y_deadreckon_point;
}

void xy_init(float angle_enc1)
{

    xy_enc1_angle = angle_enc1;

    input(porta_gpio, PIN6|PIN7);
    input(portk_gpio, PIN0|PIN1);
    input(porte_gpio, PIN0|PIN1);

    xy_count1_val = Read_Gray_EN1();
    xy_count2_val = Read_Gray_EN2();
    xy_count3_val = Read_Gray_EN3();

    timer_init(timer2, 30, ISR_XY);
}

void xy_poll(void)
{
    xy_count1_Poll();
    xy_count2_Poll();
    xy_count3_Poll();
}

#endif /* XY_H_ */
