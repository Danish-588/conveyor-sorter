/*
 * can.h
 *
 *  Created on: Jun 21, 2018
 *      Author: Varun
 */

#ifndef CAN_H_
#define CAN_H_


#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_can.h"
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/pin_map.h"
#include"driverlib/gpio.h"
#include"driverlib/interrupt.h"
#include"driverlib/sysctl.h"
#include"driverlib/timer.h"
#include"driverlib/can.h"

#include "../MTT/can_id_map.h"
#include"tm4c123gh6pge.h"

volatile bool g_bErrFlag = 0, can_error_gpio=0, can_bus_off=0;
volatile uint32_t g_ui32MsgCount1 = 0, g_ui32MsgCount2 = 0;
volatile uint32_t ui32Status;
volatile int can_error=0, no_cable=0, ack_error=0;
volatile uint8_t prevg=0, last_err=0;

tCANMsgObject sCANMessage1, sCANMessage2;
tCANBitClkParms sCANClock;
volatile uint32_t ui32MsgData[32][2]={ [0 ... 31] = { [0 ... 1] = 0 } };
uint8_t *pui8MsgData1, *pui8MsgData2;
volatile uint32_t rec=0, trans=0;
void (*can_isr_function)(void);

void can_init(void (*pfnHandler)(void));    //Port Init, Msg Object Init, Bit Timing, 125Hz Timer Init
int can_receive_init(uint32_t msg_obj);
int can_transmit(uint32_t msg_id, int data);
int can_receive(uint32_t msg_id);
int can_transmit_multiple(volatile int* arr, uint8_t start, uint8_t end);
int can_receive_multiple(volatile int* arr, uint8_t start, uint8_t end);
int can_receive_init_multiple(uint8_t start, uint8_t end);
void CAN0IntHandler(void)
{
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
    if(ui32Status == CAN_INT_INTID_STATUS)
        {
            ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
            if(ui32Status&(~((3<<3)|4|3)))
            {
                if(g_bErrFlag == 0)
					if(can_error_gpio)
						prevg = GPIOPinRead(GPIO_PORTG_BASE, 0xFF);
                g_bErrFlag = 1;
                can_error++;
                if(can_error_gpio)
                if(can_error%2000==0)
                GPIOPinWrite(GPIO_PORTG_BASE, 0xFF, GPIO_PORTG_DATA_R^0xFF);
                if(ui32Status&0x07)
                    last_err=ui32Status;
            }
            else if(ui32Status&4)
            {
                no_cable++;
                if(can_error_gpio)
                if(no_cable%2000==0)
                {
                    GPIOPinWrite(GPIO_PORTG_BASE, 0xFF, GPIO_PORTG_DATA_R^0xFF);
                    last_err=ui32Status;
                }
            }
			else if(ui32Status&3)
			{
				ack_error=1;				
			}
            else
            {
                if(g_bErrFlag == 1)
                {
                    g_bErrFlag = 0;
					if(can_error_gpio)
                    GPIOPinWrite(GPIO_PORTG_BASE, 0xFF, prevg);
                }
				ack_error=0;
                no_cable=0;
            }
            if(ui32Status>=64)
            {
                can_bus_off=1;
				if(!ack_error)
                can_init(can_isr_function);
            }
        }
    else
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        if(ui32Status>=64)
        {
			if(ui32Status&3)
			{
				ack_error=1;				
			}
            can_bus_off=1;
			if(!ack_error)
            can_init(can_isr_function);
        }
    }
}

int can_transmit(uint32_t msg_id, int data) //Msg Object ID Init
{
    int part;
    uint32_t msg_obj;
    if (data < 0)
            {
                data = ((0x80000000) | (-(data)));
            }
    else
            {
                data = data ;
            }
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

int can_transmit_multiple(volatile int* arr, uint8_t start, uint8_t end)
{
    int id = start, index=0, err_cnt=0, err=0, stop=(end%64)+1;
    while(id!=stop)
    {
        err=can_transmit(id, arr[index]);
        if(!err)
            err_cnt++;
        id=(id%64)+1;
        index++;
    }
    return err_cnt;
}

int can_receive_init(uint32_t msg_id)
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

    if((!(trans&(1<<msg_obj)))&&(!(rec&(1<<msg_obj))))
    {
        pui8MsgData2 = (uint8_t *)&ui32MsgData[msg_obj][0];
        sCANMessage2.ui32MsgID = msg_obj + 1;
        sCANMessage2.pui8MsgData = pui8MsgData2;
        CANMessageSet(CAN0_BASE, msg_obj, &sCANMessage2, MSG_OBJ_TYPE_RX);
        rec|=1<<msg_obj;
        return 1;
    }
    else if((!(trans&(1<<msg_obj)))&&(rec&(1<<msg_obj)))
        return 1;
    else
        return 0;
}

int can_receive_init_multiple(uint8_t start, uint8_t end)
{
    int id = start, err_cnt=0, err=0, stop=(end%64)+1;
    while(id!=stop)
    {
        err=can_receive_init(id);
        if(!err)
            err_cnt++;
        id=(id%64)+1;
    }
    return err_cnt;
}

int can_receive(uint32_t msg_id)
{
    int data;
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
        can_receive_init(msg_id);
    }

    pui8MsgData2 = (uint8_t *)&ui32MsgData[msg_obj][0];
    sCANMessage2.pui8MsgData = pui8MsgData2;
    CANMessageGet(CAN0_BASE, msg_obj, &sCANMessage2, 1);

    data=ui32MsgData[msg_obj][part];
    if((data)&(0x80000000))
               {
        data = -((data)&(0x7FFFFFFF)) ;
               }
               else
               {
                   data = data ;
               }
    return data;
}

//stores from index=1, so data at index n is from id n
int can_receive_multiple(volatile int* arr, uint8_t start, uint8_t end)
{
    uint8_t id = start, index=1, err_cnt=0, stop=(end%65)+1;

    while(id!=stop)
    {
        arr[index]=can_receive(id);
        id=(id%65)+1;
        index++;
    }
    return err_cnt;
}

//stores from index=0, so data at index n is from id n+1
int can_receive_array(volatile int* arr, uint8_t start, uint8_t end)
{
    uint8_t id = start, index=0, err_cnt=0, stop=(end%64)+1;

    while(id!=stop)
    {
        arr[index]=can_receive(id);
        id=(id%64)+1;
        index++;
    }
    return err_cnt;
}

void can_init(void (*Timer0IntHandler)(void))
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlDelay(50);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    SysCtlDelay(50);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlDelay(50);

    GPIOPinConfigure(GPIO_PE4_CAN0RX);
    GPIOPinConfigure(GPIO_PE5_CAN0TX);

    GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    CANInit(CAN0_BASE);

    can_isr_function=Timer0IntHandler;

    /*-----------1Mbps------------------*/
    sCANClock.ui32Phase2Seg=0x02;
    sCANClock.ui32SyncPropPhase1Seg=0x0D;
    sCANClock.ui32SJW=0x01;
    sCANClock.ui32QuantumPrescaler=0x05;

    /*----------664kbps----------------*/
//    sCANClock.ui32Phase2Seg = 0x04;
//    sCANClock.ui32SyncPropPhase1Seg = 0x10;
//    sCANClock.ui32SJW = 0x01;
//    sCANClock.ui32QuantumPrescaler = 0x06;

    /*-------------400kbps------------*/
//    sCANClock.ui32Phase2Seg = 0x08;
//    sCANClock.ui32SyncPropPhase1Seg = 0x10;
//    sCANClock.ui32SJW = 0x01;
//    sCANClock.ui32QuantumPrescaler = 0x08;

    CANBitTimingSet(CAN0_BASE, &sCANClock);

    CANIntRegister(CAN0_BASE, CAN0IntHandler); // if using dynamic vectors
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
	IntMasterEnable();
    CANEnable(CAN0_BASE);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ((SysCtlClockGet()/125)-1));
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerEnable(TIMER0_BASE, TIMER_A);

    sCANMessage1.ui32MsgIDMask = 0x00;
    sCANMessage1.ui32Flags = 0x00;
    sCANMessage1.ui32MsgLen = 8;

    sCANMessage2.ui32MsgIDMask = 0xFFFFF;
    sCANMessage2.ui32Flags = MSG_OBJ_USE_ID_FILTER;
    sCANMessage2.ui32MsgLen = 8;

}


#endif /* CAN_H_ */
