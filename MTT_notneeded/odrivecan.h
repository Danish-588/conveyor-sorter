/*
 * odrivecan.h
 *
 *  Created on: 11-Feb-2022
 *      Author: Mihika Moni
 */

#ifndef ODRIVECAN_H_
#define ODRIVECAN_H_

int axis0_node_id = 0;
int axis1_node_id = 0;

int command_id;

volatile uint64_t ui64MsgData = 0;

//commands
enum
{
    axis_node_id,
    req_state,
    input_pos,
    input_vel,
    input_torque,
    traj_vel_lim,
    traj_inertia,
    reboot,
    clear_errors,
    linear_count,
    pos_gain,
    vel_gains,
};

//states
enum
{
  idlestate = 1,
  closedloop = 8,
};

//input modes
enum
{
    passthrough = 1,
    trap_traj = 5,
};

int f2b(float fl)
{
    return (*(int*)&fl);
}

uint64_t i2u(int inter)
{
    return (*(uint64_t*)&inter);
}

float b2f(uint64_t num)
{
    return (*(float*)&num);
}

int can_raw_transmit(uint32_t msg_id, int data) //Msg Object ID Init
{
    int part;
    uint32_t msg_obj;
    if(msg_id<=32)
    {
        msg_obj = msg_id-1;
        part = 0;
    }
    else
    {
        msg_obj = msg_id-33;
        part = 1;
    }

    if(!(rec&(1<<msg_obj)))
    {
        ui32MsgData[msg_obj][part] = data;
        pui8MsgData1 = (uint8_t *)&ui32MsgData[msg_obj][0];
        sCANMessage1.ui32MsgID = msg_obj + 1;
        sCANMessage1.pui8MsgData = pui8MsgData1;
        CANMessageSet(CAN0_BASE, msg_obj, &sCANMessage1, MSG_OBJ_TYPE_TX);
        trans|=1<<msg_obj;
        return 1;
    }
    else
        return 0;
}

int can_transmit_64(uint32_t msg_id, uint64_t data) //Msg Object ID Init
{
    uint32_t msg_obj;
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
        ui64MsgData = data;
        pui8MsgData1 = (uint8_t *)&ui64MsgData;
        sCANMessage1.ui32MsgID = msg_obj + 1;
        sCANMessage1.pui8MsgData = pui8MsgData1;
        CANMessageSet(CAN0_BASE, msg_obj, &sCANMessage1, MSG_OBJ_TYPE_TX);
        trans|=1<<msg_obj;
        return 1;
    }
    else
        return 0;
}

uint64_t can_receive_64(uint32_t msg_id)
{
    int data;
    uint32_t msg_obj;
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

void can_set_controller_mode(int node, uint8_t con_mode, uint8_t input_mode)
{
    can_transmit_64(((node<<5)|0xB),(((uint64_t)input_mode)<<32)|con_mode);
}

void can_set_limits(int node, uint8_t v_lim, uint8_t c_lim)
{
    can_transmit_64(((node<<5)|0xF),(((uint64_t)f2b(c_lim))<<32)|f2b(v_lim));
}

void set_traj_limits(int node, float traj_accel, float traj_decel)
{
    can_transmit_64(((node<<5)|0x12),(((uint64_t)f2b(traj_decel))<<32)|f2b(traj_accel));
}

void odcansend(int node, int command, float value)
{
    int temp_value = value;
    switch(command)
    {
        case axis_node_id:
        {
            command_id = 0x006;
            break;
        }
        case req_state:
        {
            command_id = 0x007;
            break;
        }
        case input_pos:
        {
            command_id = 0x00C;
            temp_value = f2b(value);
            break;
        }

        case input_vel:
        {
            command_id = 0x00D;
            temp_value = f2b(value);
            break;
        }

        case input_torque:
        {
            command_id = 0x00E;
            temp_value = f2b(value);
            break;
        }

        case traj_vel_lim:
        {
            command_id = 0x011;
            temp_value = f2b(value);
            break;
        }

        case traj_inertia:
        {
            command_id = 0x013;
            temp_value = f2b(value);
            break;
        }

        case reboot:
        {
            command_id = 0x016;
            break;
        }

        case clear_errors:
        {
            command_id = 0x018;
            break;
        }

        case linear_count:
        {
            command_id = 0x019;
            break;
        }

        case pos_gain:
        {
            command_id = 0x01A;
            temp_value = f2b(value);
            break;
        }

        case vel_gains:
        {
            command_id = 0x01B;
            temp_value = f2b(value);
            break;
        }
    }
    can_raw_transmit((node<<5)|command_id , temp_value);
}

#endif /* ODRIVECAN_H_ */
