/*
 * odriveuart.h
 *
 *  Created on: 29-Dec-2021
 *      Author: Mihika Moni
 */

#ifndef ODRIVEUART_H_
#define ODRIVEUART_H_

#include <string.h>

uint32_t odrive_uart;

int odrive_data_buffer[20];
int odrive_data[20];
int odrive_index = 0;

//Enum property
enum
{
    curr_lim,
    vel_lim,
    calib_curr,
    pole_pairs,
    torque_const,
    encoder_cpr,
    req_state,
    pos_gain,
    vel_gain,
    vel_int_gain,
    enable_brake_resistance,
    brake_resistance,
    max_negative_current,
    resetcount
};

//Enum command
enum
{
    save_config,
    erase_config,
    reboot,
    clear_errors
};

//Enum Req state
enum
{
    idlestate = 1,
    closedloopstate = 8
};

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

//Odrive transmit
void odsend_single_char(uint32_t uart, char character)
{
    UARTCharPut(uart,character);
}

void odsend_int(uint32_t uart, int parameter)
{
    uart_transmit(uart, parameter);
}
void odsend_float(uint32_t uart, float parameter)
{
    int i;
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = fabs(parameter*10000.0);

    if(temp3 == 0)
    {
        odsend_single_char(uart,'0');
    }
    else
    {
        if(parameter<0)
        {
            odsend_single_char(uart,'-');
        }
        for(i = (totaldigits(temp3)-1) ; i > -1 ; i--)
        {
            if(i == 3)
            {
                odsend_single_char(uart,'.');
            }
            temp1 = (temp3 - temp2)/pow(10,i);
            odsend_int(uart,int2char(temp1));
            temp2 += (temp1*(pow(10,i)));
        }
    }
}

void odsend_string(uint32_t uart, char *str)
{
    int i;
    for(i=0;i<strlen(str);i++)
    {
        odsend_single_char(odrive_uart,str[i]);
    }
}

//Receive
void uart_receive_ascii()
{
    intclear(odrive_uart);

    int j;

    if(uart_receive(odrive_uart)==0x0A)
    {
        odrive_index = 0;
        for(j = 0; j < 20; j++)
        {
            odrive_data[j] = odrive_data_buffer[j];
        }
    }
    else
    {
        odrive_data_buffer[odrive_index] = uart_receive(odrive_uart);
        odrive_index++;
    }
}

//Init
void odrive_init(uint32_t uart, int baud)
{
    uart_init(uart, baud);
   // uart_init_rxint(uart,baud,uart_receive_ascii);
    odrive_uart = uart;
}

//odset_init_prop()
//{
//    odset_property(1, curr_lim, 60);
//
//    odset_property(1, vel_lim, 0.5);
//
//    odset_property(1, calib_curr, 55);
//
//    odset_property(1, curr_lim, 60);
//}
void odset_property(int motor,int property, float value)
{
    odsend_string(odrive_uart, "w ");

    switch(property)
    {
        case curr_lim:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".motor.config.current_lim ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case vel_lim:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".controller.config.vel_limit ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case calib_curr:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".motor.config.calibration_current ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case pole_pairs:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".motor.config.pole_pairs ");

            odsend_int(odrive_uart, int2char(value));

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case torque_const:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".motor.config.torque_constant ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case encoder_cpr:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".encoder.config.cpr ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case  req_state:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".requested_state ");

            odsend_int(odrive_uart, int2char(value));

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case pos_gain:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".controller.config.pos_gain ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case vel_gain:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".controller.config.vel_gain ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case vel_int_gain:
        {
            odsend_string(odrive_uart, "axis");

            odsend_int(odrive_uart, int2char(motor));

            odsend_string(odrive_uart, ".controller.config.vel_integrator_gain ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case enable_brake_resistance:
        {
            odsend_string(odrive_uart, "config.enable_brake_resistor ");

            if(value)
            {
                odsend_string(odrive_uart, "True");
            }
            else
            {
                odsend_string(odrive_uart, "False");
            }
            odsend_int(odrive_uart,0x0A);

            break;
        }

        case brake_resistance:
        {
            odsend_string(odrive_uart, "config.brake_resistance ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case  max_negative_current:
        {
            odsend_string(odrive_uart, "config.dc_max_negative_current ");

            odsend_float(odrive_uart, value);

            odsend_int(odrive_uart,0x0A);

            break;
        }

        case resetcount:
        {
            odsend_string(odrive_uart, "esl");

            odsend_int(odrive_uart, int2char(motor));

            odsend_int(odrive_uart, value);
        }

    }
}

void odsend_command(int command)
{
    switch(command)
    {
        case save_config:
        {
            odsend_string(odrive_uart, "ss");

            odsend_int(odrive_uart, 0x0A);

            break;
        }

        case erase_config:
        {
            odsend_string(odrive_uart, "se");

            odsend_int(odrive_uart, 0x0A);

            break;
        }

        case reboot:
        {
            odsend_string(odrive_uart, "sr");

            odsend_int(odrive_uart, 0x0A);

            break;
        }

        case clear_errors:
        {
            odsend_string(odrive_uart, "sc");

            odsend_int(odrive_uart, 0x0A);

            break;
        }
    }
}


void odsend_traj(int motor, float destination)
{
    odsend_single_char(odrive_uart,'t');

    odsend_single_char(odrive_uart,' ');

    odsend_int(odrive_uart,int2char(motor));

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,destination);

    odsend_int(odrive_uart,0x0A);
}

void odsend_vel(int motor, float value, float feedforward)
{
    odsend_single_char(odrive_uart,'v');

    odsend_single_char(odrive_uart,' ');

    odsend_int(odrive_uart,int2char(motor));

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,value/60.0);

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,feedforward);

    odsend_int(odrive_uart,0x0A);
}

void odsend_pos_single(int motor, float position, float velocity_lim, float torque_lim)
{
    odsend_single_char(odrive_uart,'q');

    odsend_single_char(odrive_uart,' ');

    odsend_int(uart,int2char(motor));

    odsend_single_char(odrive_uart,' ');

    odsend_float(uart,position);

    odsend_single_char(odrive_uart,' ');

    odsend_float(uart,velocity_lim);

    odsend_single_char(odrive_uart,' ');

    odsend_float(uart,torque_lim);

    odsend_int(odrive_uart,0x0A);
}

void odsend_pos_multiple(int motor, float position, float velocity_ff, float torque_ff)
{
    odsend_single_char(odrive_uart,'p');

    odsend_single_char(odrive_uart,' ');

    odsend_int(odrive_uart,int2char(motor));

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,position);

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,velocity_ff);

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,torque_ff);

    odsend_int(odrive_uart,0x0A);
}

void odsend_torq(int motor, float torque)
{
    odsend_single_char(odrive_uart,'c');

    odsend_single_char(odrive_uart,' ');

    odsend_int(odrive_uart,int2char(motor));

    odsend_single_char(odrive_uart,' ');

    odsend_float(odrive_uart,torque);

    odsend_int(odrive_uart,0x0A);
}

#endif /* ODRIVEUART_H_ */
