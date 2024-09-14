/*
 * fast_trigo.h
 *
 *  Created on: 01-Jul-2022
 *      Author: Soham
 */

#ifndef MTT_FAST_TRIGO_H_
#define MTT_FAST_TRIGO_H_

double fast_sin(float angle)
{
    float r_ang1,r_ang1_c;
    while(angle< -90)
    {
        angle += 360;
    }
    while(angle> 270)
    {
        angle -= 360;
    }
    if((angle>90)&&(angle<=270))
    {
        angle = 180 - angle;
    }
    r_ang1 = angle*0.0174532;
    r_ang1_c = r_ang1*r_ang1*r_ang1;
    return r_ang1 - ((r_ang1_c)/6) + ((r_ang1*r_ang1*r_ang1_c)/120) - ((r_ang1*r_ang1_c*r_ang1_c)/5040);
}

double fast_cos(float angle)
{
    float r_ang1 = 0,r_ang1_s = 0;
    while(angle< (-90))
    {
        angle += 360;
    }
    while(angle>=270)
    {
        angle -= 360;
    }
    if((angle>90)&&(angle<270))
    {
        angle = 180 - angle;
        r_ang1 = angle*0.0174532;
        r_ang1_s = r_ang1*r_ang1;
        return -(1 - ((r_ang1_s)/2) + ((r_ang1_s*r_ang1_s)/24) - ((r_ang1_s*r_ang1_s*r_ang1_s)/720));
    }
    else
    {
        r_ang1 = angle*0.0174532;
        r_ang1_s = r_ang1*r_ang1;
        return 1 - ((r_ang1_s)/2) + ((r_ang1_s*r_ang1_s)/24) - ((r_ang1_s*r_ang1_s*r_ang1_s)/720);
    }
}

float atan_approx(float z)
{
    const float n1 = 0.97239411f;
    const float n2 = -0.19194795f;
    return (n1 + n2 * z * z) * z;
}

float atan2_approx(float y, float x)
{
    float ay = fabs(y), ax = fabs(x);
    int invert = ay > ax;
    float z = (invert ? ax/ay : ay/ax);
    float th = atan_approx(z);
    if(invert) th = M_PI_2 - th;
    if(x < 0) th = M_PI - th;
    th = copysign(th, y);
    return th;
}

#endif /* MTT_FAST_TRIGO_H_ */
