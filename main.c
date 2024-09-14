#include "MTT/includes.h"

volatile bool reset=0;
// select boxes based on uart value
volatile bool
            red_ob      =0,
            yellow_ob   =0,
            green_ob    =0;

// inputs from baumer
volatile bool
            baumer0=0,
            baumer1=0,
            baumer2=0;

// counts from baumer trigger to actuation
volatile int
            piston0_buffer=60000,
            piston1_buffer=60000,
            piston2_buffer=60000;

// select which piston must be actuated
volatile bool
            piston0=0,
            piston1=0,
            piston2=0;

// counts when actuated
volatile int
            deactuate0 = 500000,
            deactuate1 = 500000,
            deactuate2 = 500000;


uint32_t uart_base;
uint32_t uart;
volatile double box_val;
volatile double *box_val_data;
volatile int boxval=0;
void box_handler(void)
{
    UARTIntClear(uart_base, UART_INT_RX);

    while(UARTCharsAvail(uart_base))
    {
        int temp_data = UARTCharGetNonBlocking(uart_base);
        boxval      =  temp_data;
        red_ob      = (temp_data==1);
        yellow_ob   = (temp_data==2);
        green_ob    = (temp_data==3);

        if (boxval >= 0 && boxval <= 3) {
          uart_init_rxint(uart, 9600, box_handler);
          uart_base = uart;
        }
        else {
            boxval = 0;
            //throw error
        }
    }

}

void conveyer_reset()
{
    piston0 = piston1 = piston2 = 0;
    baumer0 = baumer1 = baumer2 = 0;
    red_ob = yellow_ob = green_ob = 0;
    deactuate0 = deactuate1 = deactuate2 = 500000;
    piston0_buffer = piston1_buffer = piston2_buffer = 100000;



}

void box(uint32_t uart_box, volatile double *box_val_var)
{
    uart=uart_box;
    box_val_data=box_val_var;
    uart_init_rxint(uart, 9600, box_handler);
    uart_base=uart;
}

void box_init(uint32_t uart_box)
{
    box(uart_box, &box_val);
    UARTFIFODisable(uart_box);
}

void baumer_set()
{
    baumer0     = (GPIO_PORTM_DATA_R    &0x40)|baumer0;
    baumer1     = ((~GPIO_PORTM_DATA_R) &0x20)|baumer1;
    baumer2     = (GPIO_PORTM_DATA_R    &0x80)|baumer2;
}

void piston_select()
{
    if (red_ob)
    {
        if (baumer0)
        {
            piston0_buffer--;
            if (!piston0_buffer)
            {
                conveyer_reset();
                piston0 = 1;
            }
        }
    }
    if (yellow_ob)
    {
        if (baumer1)
        {
            piston1_buffer--;
            if (!piston1_buffer)
            {
                conveyer_reset();
                piston1 = 1;
            }
        }
    }
    if (green_ob)
    {
        if (baumer2)
        {
            piston2_buffer--;
            if (!piston2_buffer)
            {
                conveyer_reset();
                piston2 = 1;

            }
        }
    }
}
void piston_control()
{
    if (piston0)
    {
        GPIO_PORTM_DATA_R |= 0X08;
        deactuate0--;
        if (!deactuate0)
        {
            GPIO_PORTM_DATA_R &= (~0X08);
            conveyer_reset();

        }    }
    if (piston1)
    {
        GPIO_PORTM_DATA_R &= (~0X01);
        deactuate1--;
        if (!deactuate1)
        {
            GPIO_PORTM_DATA_R |= 0X01;
            conveyer_reset();

        }    }
    if (piston2)
    {
        GPIO_PORTM_DATA_R |= 0X04;
        deactuate2--;
        if (!deactuate2)
        {
            GPIO_PORTM_DATA_R &= (~0X04);
            conveyer_reset();

        }
    }
}


int main()
{
    System80Mhz();

    int_disable();

    input (portm_gpio, 0XF0);
    output(portm_gpio, 0x0F);
    input (portg_gpio, 0X07);

    box_init(uart4);

    GPIO_PORTM_DATA_R &=0;
    GPIO_PORTM_DATA_R |=1;
    int_enable();


    while(1)
    {
        baumer_set();
        piston_select();
        piston_control();
    }
}
