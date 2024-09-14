/*/////////////////////////////////////serial Library////////////////////////////////////
created on 3 july 2015
by rahul

we can send any data via 8bit serial communication with index no. for differntiating different ojects


///////////////////////////////////////////////////////////////////////////////////////////
*/
void send_data(int data)
{
	char data16=0;
	//while((UART3_FR_R&0x10) != 0){};
	data16=data>>8;
	UART3_DR_R=data16;
	data16=data;
	UART3_DR_R=data16;


}

#define start_of_line 12
#define end_of_line 13
#define escape 15
#define error 18

////////////edit this////////
// write the register of uart you are using
#define send UART3_DR_R
//#define recieve UART3_DR_R
volatile double data_arr[255];
volatile int enter_flag=1,enter_flag1=0,enter_flag2=0,enter_flag3=0;
volatile char index_no=0,sign_bit;
volatile int data=0;
///////////////////////////////
///////////format////////
/*
 ___________ ________________________________________________________________
|			|		  |          |      |                      |             |
| START BIT |INDEX_NO | SIGN BIT | DATA | DATA.......          | END_OF_LINE |
|___________|_________|__________|______|______________________|_____________|

*/
///////////////////////

void send_d(char s)
{
    while((UART3_FR_R&UART_FR_TXFF));
    send=s;
}
////////////////////////////////

void check_and_send(char a)
{
	if(a==start_of_line||a==end_of_line||a==escape||a==error)
	{
		send_d(escape);
		send_d(a);
	}
	else
		send_d(a);


}




serial_send(char index_no,int data)
{
	char sign_bit;
	if(data>0)
		sign_bit=0;   //positive
	else
		sign_bit=1;	//negative

	send_d(start_of_line);
	check_and_send(index_no);
	check_and_send(sign_bit);
	if(sign_bit==1)
	{
	    data=-data;
	}
	check_and_send(data);
	check_and_send(data>>8);
	check_and_send(data>>16);
	check_and_send(data>>24);
	while((UART3_FR_R&UART_FR_TXFF));
	send_d(end_of_line);


}

volatile int last_recieve=0,curr_recieve=0;

/*int check_and_recieve()
{
	int a;
	a=curr_recieve;

	if(a==escape||enter_flag2)
	{
	    enter_flag2=1;
		a=recieve;
		return a;
	}
	else
	{
		return a;
	}

}*/
//int check_and_recieve()
//{
//    if(curr_recieve==escape)
//    {
//        return 1;
//    }
//    else
//        return 0;
//
//}
//recieve_data()
//{
//
//	curr_recieve = UART3_DR_R;
//	if((last_recieve==end_of_line&&curr_recieve==start_of_line)||enter_flag)
//	{
//		enter_flag=1;
//
//		if(enter_flag1==1)
//		{
//		    if(check_and_recieve&&enter_flag2==0)
//		    {
//
//		       enter_flag2==1;
//		    }
//		    else
//		    if(enter_flag2==1||(!check_and_recieve))
//		    {
//		        enter_flag2==0;
//		        enter_flag3++;
//		        switch(enter_flag3)
//		        {
//		        case 1:
//		                index_no=curr_recieve;
//		                sign_bit=0;
//		                break;
//		        case 2:
//		                sign_bit=curr_recieve;
//		                break;
//		        case 3:
//		                data|=curr_recieve;
//		                break;
//		        case 4:
//		                data|=curr_recieve<<8;
//		                break;
//		        case 5:
//		                data|=curr_recieve<<16;
//		                break;
//		        case 6:
//		                data|=curr_recieve<<24;
//		                break;
//		        case 7:
//		                enter_flag=0;
//		                enter_flag1=0;
//		                enter_flag3=0;
//		                if(sign_bit)
//		                {
//		                        data=-data;
//		                }
//		                data_arr[index_no]=data;
//		                data=0;
//		                break;
//		        }
//		    }
//		}
//		else
//		{
//		    enter_flag1=1;
//		}
//
//	}
//
//	last_recieve=curr_recieve;
//}
//
//int serial_recieve(int index_no)
//{
//	return data_arr[index_no];
//
//}

