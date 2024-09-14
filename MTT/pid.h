/*
 * pid.h




 *
 *  Created on: Apr 25, 2015
 *      Author: Rahul Katiyar
 */
#ifndef PID_H_
#define PID_H_

typedef struct pid
{
	double kp;
	double ki;
	double kd;
	double curr_error;
	double prev_error;
	double sum;
	double sample_time;
	double output;

}pid;

///////////////////////////pid declaration///////////////////////////
pid x_dist;
pid y_dist;
pid orient;
pid navigation_line;
pid throwing_line;

//////////////PIDs for distance sensor based corrections///////////
pid x_sensor;
pid y_sensor;
pid orient_sensor;

void pid_init(pid*a,double kp,double ki,double kd,double sample_time)
{
	a->kp=kp;
	a->ki=ki;
	a->kd=kd;
	a->sample_time=sample_time;

}


double pid_update(pid*a,double error)
{
		double D;
		a->curr_error=error;
		D=((a->curr_error-a->prev_error));
		a->sum=a->sum+(a->curr_error);
		a->output=(a->kp*a->curr_error)+(a->ki*a->sum)+(a->kd*D);
		a->prev_error=a->curr_error;
		return a->output;

}
void set_kp(pid*a,double kp)
{
    a->kp=kp;
}

void pid_clear(pid*a)
{
    a->sum=0;
    a->prev_error=0;
}

#endif
