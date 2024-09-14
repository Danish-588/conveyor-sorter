
#ifndef PS_BT_H_
#define PS_BT_H_



#define MODE_PS2 0
#define MODE_PS3 1
//////////////////////////////////    VARIABLES   ////////////////////////////////////

volatile int test,garbage;

volatile int PS_data01,PS_data02,PS_data03,PS_data04,PS_data05,PS_data06,PS_data07,PS_data08,PS_data09,PS_data10,PS_data11,PS_data12;
volatile int PS_byte01_rec,PS_byte02_rec,PS_byte03_rec,PS_byte04_rec,PS_byte05_rec,PS_byte06_rec,PS_byte07_rec,PS_byte08_rec,PS_byte09_rec,PS_byte10_rec,PS_byte11_rec,PS_byte12_rec;

volatile int PS_Byte1;// Buttons -> D-PAD && Tri Sqr Crs Crl
volatile int PS_Byte2;// Buttons -> L1L2R1R2 start select
volatile int PS_Byte3;// LeftAnaX
volatile int PS_Byte4;// LeftAnaY
volatile int PS_Byte5;// RightAnaX
volatile int PS_Byte6;// RightAnaY

volatile int isr_count,prev_isr;
volatile int timer_count;


volatile int data_array[12]={0},dataWatchCnt=0;
volatile int PS_Received_Data = 0, PS_isr_check = 0, counter = 0;

volatile int mode_ps;
volatile uint32_t psuart;
////////////////////////////  BUTTON MAPPINGS  //////////////////////////////////////////////

#define PS_SELECT_PRESSED ((PS_Byte1 & 0x01)==0x01)
#define PS_L3_PRESSED ((PS_Byte1 & 0x02)==0x02)
#define PS_R3_PRESSED ((PS_Byte1 & 0x04)==0x04)
#define PS_START_PRESSED ((PS_Byte1 & 0x08)==0x08)

#define PS_UP_PRESSED ((PS_Byte1 & 0x10)==0x10)
#define PS_RIGHT_PRESSED ((PS_Byte1 & 0x20)==0x20)
#define PS_DOWN_PRESSED ((PS_Byte1 & 0x40)==0x40)
#define PS_LEFT_PRESSED ((PS_Byte1 & 0x80)==0x80)

#define PS_L2_PRESSED ((PS_Byte2 & 0x01)==0x01)
#define PS_R2_PRESSED ((PS_Byte2 & 0x02)==0x02)
#define PS_L1_PRESSED ((PS_Byte2 & 0x04)==0x04)
#define PS_R1_PRESSED ((PS_Byte2 & 0x08)==0x08)

#define PS_TRIANGLE_PRESSED ((PS_Byte2 & 0x10)==0x10)
#define PS_CIRCLE_PRESSED ((PS_Byte2 & 0x20)==0x20)
#define PS_CROSS_PRESSED ((PS_Byte2 & 0x40)==0x40)
#define PS_SQUARE_PRESSED ((PS_Byte2 & 0x80)==0x80)


#define PS_ANALOG_RIGHT_LEFT ((PS_Byte3)<-100)
#define PS_ANALOG_RIGHT_RIGHT ((PS_Byte3)>100)
#define PS_ANALOG_RIGHT_UP ((PS_Byte4)>100)
#define PS_ANALOG_RIGHT_DOWN ((PS_Byte4)<-100)

#define PS_ANALOG_LEFT_LEFT ((PS_Byte5)<-100)
#define PS_ANALOG_LEFT_RIGHT ((PS_Byte5)>100)
#define PS_ANALOG_LEFT_UP ((PS_Byte6)>100)
#define PS_ANALOG_LEFT_DOWN ((PS_Byte6)<-100)


//////////////////////////////    FUNCTIONS     //////////////////////////////////////////////
void flush(void);
void timerCheck(void);
void uartCheck(int uart_data,int mode);
void watchData(int uart_data);
void PS_uart_init(uint32_t uart,int mode);

////////////////////////////////////////////////////////////////////////////////////////////

void PS3_ISR(void)
{
    intclear(psuart);

    PS_Received_Data = uart_receive(psuart);
    uartCheck(PS_Received_Data, mode_ps);
    PS_isr_check++;
}

void PS_uart_init(uint32_t uart,int mode)
{
    int baud;
    psuart=uart;
    mode_ps=mode;
    if(mode == MODE_PS2)
    {
        baud = 9600;
    }
    else if(mode == MODE_PS3)
    {
        baud = 115200;
    }
    else
    {
        baud = 0;
    }

    uart_init_rxint(uart, baud, PS3_ISR);
}


void flush()
{
    PS_byte01_rec=PS_byte02_rec=PS_byte03_rec=PS_byte04_rec=PS_byte05_rec=PS_byte06_rec=PS_byte07_rec=PS_byte08_rec=PS_byte09_rec=PS_byte10_rec=PS_byte11_rec=PS_byte12_rec=0;
    PS_Byte1=PS_Byte2=0;
    PS_Byte3=PS_Byte4=PS_Byte5=PS_Byte6=0;
}

void timerCheck(void)
{
    timer_count++;
    if (timer_count % 125 == 0)
    {
        timer_count = 0;
        if (isr_count == prev_isr)
        {
            flush();
        }
    }
    prev_isr=isr_count;
}

void uartCheck(int uart_data,int mode)
{
    isr_count++;
    switch (uart_data & 0x0f)
    {
    case 0:
    {
        test = uart_data;
        break;
    }
    case 1:
    {
        if (test == 0)
        {
            PS_data01 = uart_data;
            PS_byte01_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 2:
    {
        if (test == 0)
        {
            PS_data02 = uart_data;
            PS_byte02_rec = 1;
        }
        else
        {
            flush();
        }
        break;

    }
    case 3:
    {
        if (test == 0)
        {
            PS_data03 = uart_data;
            PS_byte03_rec = 1;
        }
        else
        {
            flush();
        }
        break;

    }
    case 4:
    {
        if (test == 0)
        {
            PS_data04 = uart_data;
            PS_byte04_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 5:
    {
        if (test == 0)
        {
            PS_data05 = uart_data;
            PS_byte05_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 6:
    {
        if (test == 0)
        {
            PS_data06 = uart_data;
            PS_byte06_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 7:
    {
        if (test == 0)
        {
            PS_data07 = uart_data;
            PS_byte07_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 8:
    {
        if (test == 0)
        {
            PS_data08 = uart_data;
            PS_byte08_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 9:
    {
        if (test == 0)
        {
            PS_data09 = uart_data;
            PS_byte09_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 10:
    {
        if (test == 0)
        {
            PS_data10 = uart_data;
            PS_byte10_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 11:
    {
        if (test == 0)
        {
            PS_data11 = uart_data;
            PS_byte11_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    case 12:
    {
        if (test == 0)
        {
            PS_data12 = uart_data;
            PS_byte12_rec = 1;
        }
        else
        {
            flush();
        }
        break;
    }
    default:
    {
        garbage = uart_data;
        flush();
        break;
    }
    }

    if (PS_byte01_rec == 1 && PS_byte02_rec == 1)
    {
        PS_Byte1 = (PS_data01 & 0xF0) | ((PS_data02 & 0xF0) >> 4);
    }

    if (PS_byte03_rec == 1 && PS_byte04_rec == 1)
    {
        PS_Byte2 = (PS_data03 & 0xF0) | ((PS_data04 & 0xF0) >> 4);
    }

    if (PS_byte05_rec == 1 && PS_byte06_rec == 1)
    {
        PS_Byte3 = ((PS_data05 & 0xF0) | ((PS_data06 & 0xF0) >> 4)) - 128;
    }

    if (PS_byte07_rec == 1 && PS_byte08_rec == 1)
    {
        PS_Byte4 = (0 - (((PS_data07 & 0xF0) | ((PS_data08 & 0xF0) >> 4)) - 128));
    }

    if (PS_byte09_rec == 1 && PS_byte10_rec == 1)
    {
        PS_Byte5 = ((PS_data09 & 0xF0) | ((PS_data10 & 0xF0) >> 4)) - 128;
    }

    if (PS_byte11_rec == 1 && PS_byte12_rec == 1)
    {
        PS_Byte6 = (0 - (((PS_data11 & 0xF0) | ((PS_data12 & 0xF0) >> 4)) - 128));
    }

    if(mode == MODE_PS3)
    {
        watchData(uart_data);
    }
}

void watchData(int uart_data)
{
    int i=0,counter=0;
    data_array[dataWatchCnt] = uart_data;

    for(i=0;i<11;i++)
    {
        if(data_array[i] == data_array[i+1])
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    if(counter > 10)
    {
      flush();
    }

    if(dataWatchCnt<11)
    {
        dataWatchCnt++;
    }
    else
    {
        dataWatchCnt = 0;
    }
}
#endif /* PS_BT_H_ */
