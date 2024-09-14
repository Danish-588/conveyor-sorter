/*
 * sparton.h
 *
 *  Created on: 03-Sep-2021
 *      Author: Soham
 */
#include <string.h>
#include <MTT/uart.h>
#ifndef SPARTON_H_
#define SPARTON_H_



//Simple
volatile bool once = 1;
volatile bool angle_done = 0;
volatile uint8_t frame_case = 0;
volatile uint8_t frame_increment = 0;
volatile uint8_t anglepluschecksum[15] = {0};
volatile uint8_t checksum_calculated = 0;
volatile uint8_t checksum_received = 0;
volatile uint32_t sparton_uart = 0;
volatile float sparton_angle;
volatile char *mag_command_1 = "km0 f";
volatile char *mag_command_2 = " set drop save";
volatile char *yaw_command_repeat="$PSRFS,yaw,get,RPT=0.01*05";
volatile char *tare_command = "InvokeTare 1 set drop";

enum
{
    search,
    begin,
    angle_start,
};


extern float strtof(const char* str, char **endptr);

void uart_sendstring(uint32_t uart, volatile char *str)
{
    int i;
    for(i=0;i<strlen((const char*)str);i++)
    {
        UARTCharPut(uart,str[i]);
    }
}

char int2char(int num)
{
    return '0' + num;
}

int totaldigits(int num)
{
    int i = 0;
    while(num > 0)
    {
        num /= 10;
        i++;
    }
    return i;
}

void uart_sendfloat(uint32_t uart, float parameter)
{
    int i;
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = fabs(parameter*10000.0);

    if(temp3 == 0)
    {
        UARTCharPutNonBlocking(uart,'0');
    }
    else
    {
        if(parameter<0)
        {
            UARTCharPutNonBlocking(uart,'-');
        }
        for(i = (totaldigits(temp3)-1) ; i > -1 ; i--)
        {
            if(i == 3)
            {
                UARTCharPutNonBlocking(uart,'.');
            }
            temp1 = (temp3 - temp2)/pow(10,i);
            uart_transmit(uart,int2char(temp1));
            temp2 += (temp1*(pow(10,i)));
        }
    }
}

void set_km(float value)
{
    uart_sendstring(sparton_uart, mag_command_1);
    uart_sendfloat(sparton_uart, value);
    uart_sendstring(sparton_uart, mag_command_2);
    uart_transmit(sparton_uart, 13);
    uart_transmit(sparton_uart, 10);
}

void tare()
{
    uart_transmit(sparton_uart, 13);
    uart_transmit(sparton_uart, 10);
    uart_sendstring(sparton_uart, tare_command);
    uart_transmit(sparton_uart, 13);
    uart_transmit(sparton_uart, 10);
    uart_sendstring(sparton_uart, yaw_command_repeat);
    uart_transmit(sparton_uart, 13);
    uart_transmit(sparton_uart, 10);
}

void sparton_simple_isr()
{
    intclear(sparton_uart);
    while(UARTCharsAvail(sparton_uart))
    {
        uint8_t temp_data = UARTCharGetNonBlocking(sparton_uart) & 0xFF;

        switch(frame_case)
        {
        case search:
            if(temp_data==36)//36 = $
            {
                frame_case = begin;
            }
            break;
        case begin:
            frame_increment++;
            if(frame_increment>9)
            {
                frame_case = angle_start;
                frame_increment = 0;
            }
            break;
        case angle_start:
            anglepluschecksum[frame_increment] = temp_data;
            frame_increment++;
            if(frame_increment>14)
            {
                frame_increment = 0;
                frame_case = search;
            }
            if(temp_data==13)//13 = CR
            {
                angle_done = 1;
                frame_case = 0;
                frame_increment = 0;
            }
            break;
        }
    }
}

void sparton_simple_parse()
{
    uint8_t frame_index = 0;
    uint8_t asterisktracker = 0;
    while(anglepluschecksum[frame_index]!='*')
    {
        checksum_calculated ^= (int)(anglepluschecksum[frame_index]);
        frame_index++;
        asterisktracker++;
        if(frame_index>10)
        {
            checksum_calculated = 0x2B;
            asterisktracker = 0;
            break;
        }
    }
    checksum_received = (anglepluschecksum[asterisktracker+2]-48) + 16*((anglepluschecksum[asterisktracker+1]-48));
    if(checksum_received==checksum_calculated)
    {
        sparton_angle = strtof((const char*)anglepluschecksum,NULL);
        angle = 360.0 - sparton_angle;
    }
    checksum_calculated = 0x2B;
}

void sparton_init(int uartbase, int baud_rate)
{
    sparton_uart = uartbase;
    uart_init_rxint(uartbase, baud_rate, sparton_simple_isr);
    UARTFIFOEnable(sparton_uart);
}


#endif /* SPARTON_H_ */
