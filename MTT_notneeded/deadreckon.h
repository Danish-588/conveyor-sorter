/*
 * deadreckon.h
 *
 *	Created on: Nov 20, 2019
 *      Author: Gaurav
 */

#ifndef DEADRECKON_H_
#define DEADRECKON_H_
 

void calculate_deadreck()
{
    x_scale = 0 + 1 * x;
    y_scale = 0 + 1 * y;

    x_final = x_scale - x_deadreck;
    y_final = y_scale - y_deadreck;

    if((angle_temp - angle_deadreckon_point) < 0)
        angle = 360 + (angle_temp - angle_deadreckon_point);
    else if ((angle_temp - angle_deadreckon_point) > 360)
        angle = (angle_temp - angle_deadreckon_point) - 360;
    else
        angle = (angle_temp - angle_deadreckon_point);
}

#endif /* DEADRECKON_H_ */
