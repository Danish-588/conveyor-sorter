/*
 * stall.h
 *
 *	Created on: Nov 20, 2019
 *      Author: Gaurav
 */

#ifndef STALL_H_
#define STALL_H_
 
void instant_stall()
{
	if (w > 0)
        w -= stall_w_deaccs;
    if (w < 0)
        w += stall_w_deaccs;
    if ((w <= 0.5) && (w >= -0.5))
        w = 0;

    if (vy > 0)
        vy -= stall_deaccs;
    if (vy < 0)
        vy += stall_deaccs;
    if ((vy <= 0.2) && (vy >= -0.2))
        vy = 0;

    if (vx > 0)
        vx -= stall_deaccs;
    if (vx < 0)
        vx += stall_deaccs;
    if ((vx <= 0.2) && (vx >= -0.2))
        vx = 0;
}
 
#endif /* STALL_H_ */
