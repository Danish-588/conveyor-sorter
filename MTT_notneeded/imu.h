/*
 * imu.h
 *
 *  Created on: Jun 30, 2018
 *      Author: Varun
 */

#ifndef IMU_H_
#define IMU_H_

#include "../MTT/uart.h"

uint32_t uart_base;
uint32_t uart;
volatile double *angle_data;
volatile long an_integer=0;
volatile int imu_next_byte = 1, imu_prev_byte = 1, imu_data_rx = 0;
void IMU_handler(void)
{
    UARTIntClear(uart_base, UART_INT_RX);
    while(UARTCharsAvail(uart_base))
    {
        int temp_data = UARTCharGetNonBlocking(uart_base);
        if(temp_data!=(-1))
        {
            imu_data_rx = temp_data;

            if (imu_data_rx & 0x80)
            {
                imu_data_rx &= 0b01111111;
                an_integer = (imu_data_rx << 7);
                imu_next_byte = true;
            }
            else if (imu_next_byte)
            {
                an_integer += imu_data_rx;
                *angle_data = 360-(an_integer / 10.0);
                imu_next_byte = false;
            }
        }
    }

}

void imu(uint32_t uart_imu, volatile double *angle_var)
{
    uart=uart_imu;
    angle_data=angle_var;
    uart_init_rxint(uart, 38400, IMU_handler);
    uart_base=uart;
}

void imu_init(uint32_t uart_imu)
{
    imu(uart_imu, &angle);
    UARTFIFODisable(uart_imu);
}


#endif /* IMU_H_ */
