/*
 * deadreckon.h
 *
 *	Created on: Nov 20, 2019
 *      Author: Gaurav
 */

#ifndef NEXTCASE_H_
#define NEXTCASE_H_

void next()
{
    if (((fabs(error_x) < 0.03) && (fabs(error_y) < 0.03)) || (direct_next))
    {
        direct_next = 0;
        if (!angle_check)
        {
            navi_choice++;
        }
        if (angle_check)
        {
            if (fabs(error_angle) < 0.5)
            {
                angle_check = 0;
                navi_choice++;
            }
        }
    }
}
#endif /* NEXTCASE_H_ */
