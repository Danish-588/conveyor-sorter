/*
 * VESC.h
 *
 *  Created on: Dec 26, 2019
 *      Author: Chaitanya
 */

#ifndef VESC_H_
#define VESC_H_

#include <stdbool.h>
#include "MTT/includes.h"
#include "MTT/vesc_headers/buffervesc.h"
#include "MTT/vesc_headers/crcvesc.h"
#include "MTT/vesc_headers/datatypes.h"

int packSendPayload(uint8_t * payload, int lenPay, uint32_t uart)
{
    uint16_t crcPayload = crc16(payload, lenPay);
    int dum_cnt = 0;
    int count = 0;
    uint8_t messageSend[256];

    if (lenPay <= 256)
    {
        messageSend[count++] = 2;
        messageSend[count++] = lenPay;
    }
    else
    {
        messageSend[count++] = 3;
        messageSend[count++] = (uint8_t)(lenPay >> 8);
        messageSend[count++] = (uint8_t)(lenPay & 0xFF);
    }

    memcpy(&messageSend[count], payload, lenPay);

    count += lenPay;
    messageSend[count++] = (uint8_t)(crcPayload >> 8);
    messageSend[count++] = (uint8_t)(crcPayload & 0xFF);
    messageSend[count++] = 3;
    messageSend[count] = '\0';

    // Sending package
    while(dum_cnt<count)
    {
        uart_transmit(uart, messageSend[dum_cnt]);
        dum_cnt++;
    }
    dum_cnt = 0;

    // Returns number of send bytes
    return count;
}

void setHandbrake(float hbcurrent, uint32_t uart)
{
    int32_t index = 0;
    uint8_t payload[5];

    payload[index++] = COMM_SET_HANDBRAKE;
    buffer_append_float32(payload, (int32_t)hbcurrent, 1000, &index);

    packSendPayload(payload, 5, uart);
}

void setRPM(float rpm, int poles, uint32_t uart)
{
    int32_t index = 0;
    uint8_t payload[5];

    payload[index++] = COMM_SET_RPM ;
    buffer_append_int32(payload, (int32_t)(rpm * poles), &index);

    packSendPayload(payload, 5, uart);
}

void vesc_init(uint32_t uart, int baud)
{
    uart_init(uart, baud);
}
#endif /* VESC_H_ */
