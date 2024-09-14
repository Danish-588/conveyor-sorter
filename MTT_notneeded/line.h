/*
 * line.h
 *
 *  Created on: Jan 12, 2017
 *      Author: gaurav
 */

#ifndef LINE_H_
#define LINE_H_

volatile float lt_front=0, lt_back=0, line_mechanism_data=0;
volatile int Mdata=0;
volatile float back_line_error=0,back_prev_error=0,back_req_line_error=0;
volatile float back_count=0,back_log_count=0;
volatile float mechanism_line_error=0,mechanism_prev_error=0,mechanism_req_line_error=0;
volatile float mechanism_count=0,mechanism_log_count=0;
volatile float front_line_error=0,front_prev_error=0,front_req_line_error=0;
volatile float front_count=0,front_log_count=0;

void back_line_poll()
{
	Mdata =	lt_back;
		back_count=0;
		back_log_count=0;
		if(Mdata&0x01)
		 {
		  back_log_count+=1;
		  back_count++;
		 }
		 if(Mdata&0x02)
		 {
			 back_log_count+=2;
			 back_count++;
		 }
		 if(Mdata&0x04)
		 {
		   back_log_count+=3;
		   back_count++;
		 }
		 if(Mdata&0x08)
	   {
		 back_log_count+=4;
		   back_count++;
	   }
		 if(Mdata&0x10)
	   {
		 back_log_count+=5;
		   back_count++;
	   }
		 if(Mdata&0x20)
	   {
		 back_log_count+=6;
		   back_count++;
	   }
		 if(Mdata&0x40)
	   {
		 back_log_count+=7;
		   back_count++;
	   }
		 if(Mdata&0x80)
	   {
		 back_log_count+=8;
		   back_count++;
	   }
	   if(back_count==0)
	   {
		   back_line_error=back_prev_error;
	   }
	   else
	   {
		   back_line_error=((back_log_count)/back_count);
		   back_prev_error =  back_line_error ;
	   }
}

void front_line_poll()
{
		Mdata =	lt_front;
		front_count=0;
		front_log_count=0;
		if(Mdata&0x80)
		 {
		  front_log_count+=8;
		  front_count++;
		 }
		 if(Mdata&0x40)
		 {
			 front_log_count+=7;
			 front_count++;
		 }
		 if(Mdata&0x20)
		 {
		   front_log_count+=6;
		   front_count++;
		 }
		 if(Mdata&0x10)
	   {
		 front_log_count+=5;
		   front_count++;
	   }
		 if(Mdata&0x08)
	   {
		 front_log_count+=4;
		   front_count++;
	   }
		 if(Mdata&0x04)
	   {
		 front_log_count+=3;
		   front_count++;
	   }
		 if(Mdata&0x02)
	   {
		 front_log_count+=2;
		   front_count++;
	   }
		 if(Mdata&0x01)
	   {
		 front_log_count+=1;
		   front_count++;
	   }
	   if(front_count==0)
	   {
		   front_line_error=front_prev_error;
	   }
	   else
	   {
		   front_line_error=(((front_log_count)/front_count));
		   front_prev_error =  front_line_error ;
	   }
}

void mechanism_line_poll()
{
	Mdata =	line_mechanism_data;
			mechanism_count=0;
			mechanism_log_count=0;
			if(Mdata&0x01)
			 {
			  mechanism_log_count+=1;
			  mechanism_count++;
			 }
			 if(Mdata&0x02)
			 {
				 mechanism_log_count+=2;
				 mechanism_count++;
			 }
			 if(Mdata&0x04)
			 {
			   mechanism_log_count+=3;
			   mechanism_count++;
			 }
			 if(Mdata&0x08)
		   {
			 mechanism_log_count+=4;
			   mechanism_count++;
		   }
			 if(Mdata&0x10)
		   {
			 mechanism_log_count+=5;
			   mechanism_count++;
		   }
			 if(Mdata&0x20)
		   {
			 mechanism_log_count+=6;
			   mechanism_count++;
		   }
			 if(Mdata&0x40)
		   {
			 mechanism_log_count+=7;
			   mechanism_count++;
		   }
			 if(Mdata&0x80)
		   {
			 mechanism_log_count+=8;
			   mechanism_count++;
		   }
		   if(mechanism_count==0)
		   {
			   mechanism_line_error=mechanism_prev_error;
		   }
		   else
		   {
			   mechanism_line_error=(((mechanism_log_count)/mechanism_count)-(4.5-mechanism_req_line_error));
			   mechanism_prev_error =  mechanism_line_error ;
		   }
}


#endif /* LINE_H_ */
