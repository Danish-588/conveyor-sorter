/*
 * bezier.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Gaurav
 */

#ifndef BEZIER_H_
#define BEZIER_H_

void bezier_3(float x1, float y1, float x2, float y2, float x3, float y3)
{
    req_x = ((pow(1 - t, 2)) * x1) + (2 * t * (1 - t) * x2) + ((pow(t, 2)) * x3);
    req_y = ((pow(1 - t, 2)) * y1) + (2 * t * (1 - t) * y2) + ((pow(t, 2)) * y3);
}

void bezier_4(float x4, float y4, float x5, float y5, float x6, float y6, float x7, float y7)
{
    req_x = ((pow((1 - t), 3) * x4) + (3 * t * (pow((1 - t), 2) * x5)) + (3 * (1 - t) * (pow(t, 2)) * x6) + ((pow(t, 3)) * x7));
    req_y = ((pow((1 - t), 3) * y4) + (3 * t * (pow((1 - t), 2) * y5)) + (3 * (1 - t) * (pow(t, 2)) * y6) + ((pow(t, 3)) * y7));
}

#endif /* BEZIER_H_ */
