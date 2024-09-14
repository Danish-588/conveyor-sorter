/*
 * rgb.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Gaurav
 */

#ifndef RGB_H_
#define RGB_H_

#define White 0
#define Red 1
#define Green 2
#define Blue 3
#define Cyan 4
#define Yellow 5
#define Purple 6
#define Black 7

volatile int R = 0, G = 0, B = 0;
volatile int interval = 100, kakashi_delay = 0, color = 0;

void Kakashi(int color1, int color2, int color3, int color4)
{
    kakashi_delay++;

    if (kakashi_delay >= 0 && kakashi_delay <= (interval/4))
        color = color1;

    if (kakashi_delay >= ((interval/4) + 1) && kakashi_delay <= (interval/2))
        color = color2;

    if (kakashi_delay >= ((interval/2) + 1) && kakashi_delay <= (interval * (3/4)))
        color = color3;

    if (kakashi_delay >= ((interval * (3/4)) + 1) && kakashi_delay <= interval)
        color = color4;
    
	if (kakashi_delay > interval)
		kakashi_delay = 0;
}

void color_combination(int c)
{
    switch (c)
    {
    case 0:
        R = 1;
        G = 1;
        B = 1;
        break;
    case 1:
        R = 1;
        G = 0;
        B = 0;
        break;
    case 2:
        R = 0;
        G = 1;
        B = 0;
        break;
    case 3:
        R = 0;
        G = 0;
        B = 1;
        break;
    case 4:
        R = 0;
        G = 1;
        B = 1;
        break;
    case 5:
        R = 1;
        G = 1;
        B = 0;
        break;
    case 6:
        R = 1;
        G = 0;
        B = 1;
        break;
    case 7:
        R = 0;
        G = 0;
        B = 0;
        break;
    }
}

void rgb(uint32_t rgb_port, int r, uint8_t r_pin, int g, uint8_t g_pin, int b, uint8_t b_pin)
{
	if (r)
		set_pins(rgb_port, r_pin);
	else
	    reset_pins(rgb_port, r_pin);
	
	if (g)
	    set_pins(rgb_port, g_pin);
	else
	    reset_pins(rgb_port, g_pin);
	
	if (b)
	    set_pins(rgb_port, b_pin);
	else
		reset_pins(rgb_port, b_pin);
}

#endif /* RGB_H_ */
