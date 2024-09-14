/*
 * ps_parse.h
 *
 *  Created on: 20-Jun-2022
 *      Author: Soham
 */

#ifndef PS_PARSE_H_
#define PS_PARSE_H_

volatile bool ps_digital[40];
volatile int16_t ps_analog[7];

enum digital
{
    share_hold,
    l3_hold,
    r3_hold,
    options_hold,
    up_hold,
    right_hold,
    down_hold,
    left_hold,
    triangle_hold,
    circle_hold,
    cross_hold,
    square_hold,
    l1_hold,
    r1_hold,
    l2_hold,
    r2_hold,
    share_toggle,
    l3_toggle,
    r3_toggle,
    options_toggle,
    up_toggle,
    right_toggle,
    down_toggle,
    left_toggle,
    triangle_toggle,
    circle_toggle,
    cross_toggle,
    square_toggle,
    l1_toggle,
    r1_toggle,
    l2_toggle,
    r2_toggle,
    ps,
    touchpad,
    ps_up,
    ps_down,
    touchpad_up,
    touchpad_down,
    r2_up,
    r2_down,
};

enum analog
{
    battery,
    l2val,
    r2val,
    lx,
    ly,
    rx,
    ry,
};

uint64_t can_receive_ps(uint32_t msg_id)
{
    uint64_t data;
    uint32_t msg_obj;

    uint64_t ui64MsgData = 0;

    if(msg_id<=32)
    {
        msg_obj = msg_id-1;
    }
    else
    {
        msg_obj = msg_id-33;
    }

    if(!(rec&(1<<msg_obj)))
    {
        can_receive_init(msg_id);
    }

    pui8MsgData2 = (uint8_t *)&ui64MsgData;
    sCANMessage2.pui8MsgData = pui8MsgData2;
    CANMessageGet(CAN0_BASE, msg_obj, &sCANMessage2, 1);

    data=ui64MsgData;
    return data;
}

void ps_getdata(uint32_t digital_id,uint32_t analog_id)
{
    uint8_t i;
    uint64_t temp = 0;
    uint64_t ps_frame = 0;
    ps_frame = can_receive_ps(digital_id)&0x3FFFFFFFF;
    for(i = 0; i<40 ; i++)
    {
        ps_digital[i] = (ps_frame>>i)&0x1;
    }

    ps_frame = can_receive_ps(analog_id)&0xFFFFFFFFFFFFFF;
    for(i = 0; i<3 ; i++)
    {
        temp = (ps_frame>>(i*8))&0xFF;
        ps_analog[i] = (*(uint8_t*)&temp);
    }
    for(i = 0; i<4 ; i++)
    {
        temp = (ps_frame>>(24+(i*8)))&0xFF;
        ps_analog[i+3] = (*(int8_t*)&temp);
    }
}

#endif /* PS_PARSE_H_ */
