/*
 * equations.h
 *
 *  Created on: Sep 12, 2018
 *      Author: Varun
 */

#ifndef MTT_EQUATIONS_H_
#define MTT_EQUATIONS_H_

#define omni 1
#define mecanum 2

#define pi 3.14159

volatile float theta = 0;

void equations(void)
{
    if(fabs(vx) > vx_limit)
    {
        v_scaling_factor = vx_limit/vx;

        vx *= v_scaling_factor;
        vy *= v_scaling_factor;
    }

    if(fabs(vy) > vy_limit)
    {
        v_scaling_factor = vy_limit/vy;

        vy *= v_scaling_factor;
        vx *= v_scaling_factor;
    }

    if(holonomic == 1)
        theta = angle;
    else
        theta=0;

    if(drive == mecanum)
    {
        v1 = vx * (-fast_sin(45 + theta))  + vy * (fast_cos (45 + theta))  + w * bot_radius;
        v2 = vx * (-fast_sin(45 - theta))  + vy * (-fast_cos(45 - theta))  + w * bot_radius;
        v3 = vx * (fast_sin (45 + theta))  + vy * (-fast_cos(45 + theta))  + w * bot_radius;
        v4 = vx * (fast_sin (45 - theta))  + vy * (fast_cos (45 - theta))  + w * bot_radius;

        rpm1 = ((v1 * 60) / (2 * pi * 0.075));
        rpm2 = ((v2 * 60) / (2 * pi * 0.075));
        rpm3 = ((v3 * 60) / (2 * pi * 0.075));
        rpm4 = ((v4 * 60) / (2 * pi * 0.075));
    }
    else if(drive == omni)
    {
        v1 = (-vx * fast_sin(omni_front_angle + theta))       + (vy * fast_cos(omni_front_angle + theta))       + (w * bot_radius);
        v2 = (-vx * fast_sin(omni_front_angle + 120 + theta)) + (vy * fast_cos(omni_front_angle + 120 + theta)) + (w * bot_radius);
        v3 = (-vx * fast_sin(omni_front_angle + 240 + theta)) + (vy * fast_cos(omni_front_angle + 240 + theta)) + (w * bot_radius);

        rpm1 = (v1 * 60) / (2 * pi * 0.068);
        rpm2 = (v2 * 60) / (2 * pi * 0.068);
        rpm3 = (v3 * 60) / (2 * pi * 0.068);
    }
}

#endif /* MTT_EQUATIONS_H_ */
