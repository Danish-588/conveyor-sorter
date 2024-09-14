/*
 * motor_encoder.h
 *
 *  Created on: Sep 10, 2018
 *      Author: Varun
 */

#ifndef MOTOR_ENCODER_H_
#define MOTOR_ENCODER_H_

#define enc1 1
#define enc2 2
#define uart0_enc 4
#define uart1_enc 8
#define uart4_enc 16
#define uart5_enc 32
#define uart0_gray 64
#define uart1_gray 128
#define uart4_gray 256
#define uart5_gray 512
#define enc3 1024

volatile int enc1_count = 0, enc2_count = 0, enc3_count = 0;
volatile int enc1_sendcount=0, enc2_sendcount=0, enc3_sendcount = 0;
volatile int uart0_count_val_tmp = 0, uart0_count_val = 0, uart0_count = 0, uart0_sendcount = 0;
volatile int uart1_count_val_tmp = 0, uart1_count_val = 0, uart1_count = 0, uart1_sendcount = 0;
volatile int uart4_count_val_tmp = 0, uart4_count_val = 0, uart4_count = 0, uart4_sendcount = 0;
volatile int uart5_count_val_tmp = 0, uart5_count_val = 0, uart5_count = 0, uart5_sendcount = 0;

volatile int enc1_dir = 1, enc2_dir = 1, uart0_dir = 1, uart1_dir = 1, uart4_dir = 1, uart5_dir = 1, enc3_dir = 1;

void enc1_isr(void)
{
    intclear(portk_gpio);

    if ((GPIO_PORTE_DATA_R) & (PIN0))
    {
        enc1_count+=enc1_dir;
        enc1_sendcount+=enc1_dir;
    }
    else
    {
        enc1_count-=enc1_dir;
        enc1_sendcount-=enc1_dir;
    }
}

void enc2_isr(void)
{
    intclear(porte_gpio);

    if ((GPIO_PORTP_DATA_R) & (PIN2))
    {
        enc2_count+=enc2_dir;
        enc2_sendcount+=enc2_dir;
    }
    else
    {
        enc2_count-=enc2_dir;
        enc2_sendcount-=enc2_dir;
    }
}

void enc3_isr(void)
{
    intclear(portg_gpio);

    if ((GPIO_PORTG_DATA_R) & (PIN1))
    {
        enc3_count+=enc3_dir;
        enc3_sendcount+=enc3_dir;
    }
    else
    {
        enc3_count-=enc3_dir;
        enc3_sendcount-=enc3_dir;
    }
}

void uart0_count_isr(void)
{
    intclear(porta_gpio);

    if ((GPIO_PORTA_DATA_R) & (PIN1))
    {
        uart0_count+=uart0_dir;
        uart0_sendcount+=uart0_dir;
    }
    else
    {
        uart0_count-=uart0_dir;
        uart0_sendcount-=uart0_dir;
    }
}

void uart1_count_isr(void)
{
    intclear(portc_gpio);

    if ((GPIO_PORTC_DATA_R) & (PIN5))
    {
        uart1_count+=uart1_dir;
        uart1_sendcount+=uart1_dir;
    }
    else
    {
        uart1_count-=uart1_dir;
        uart1_sendcount-=uart1_dir;
    }
}

void uart4_count_isr(void)
{
    intclear(portj_gpio);

    if ((GPIO_PORTJ_DATA_R) & (PIN1))
    {
        uart4_count+=uart4_dir;
        uart4_sendcount+=uart4_dir;
    }
    else
    {
        uart4_count-=uart4_dir;
        uart4_sendcount-=uart4_dir;
    }
}


void uart5_count_isr(void)
{
    intclear(portj_gpio);

    if ((GPIO_PORTJ_DATA_R) & (PIN5))
    {
        uart5_count+=uart5_dir;
        uart5_sendcount+=uart5_dir;
    }
    else
    {
        uart5_count-=uart5_dir;
        uart5_sendcount-=uart5_dir;
    }
}

uint8_t Read_Gray_UART0(void )
{
uint8_t uart0_count_val=0;
if((GPIO_PORTA_DATA_R) & (PIN0))
uart0_count_val |= 0x02 ;
 if((GPIO_PORTA_DATA_R) & (PIN1))
uart0_count_val |= 0x01 ;
return uart0_count_val;
}

int uart0_poll(void)
{
uart0_count_val_tmp = Read_Gray_UART0();
if(uart0_count_val != uart0_count_val_tmp)
{
if( (uart0_count_val==2 && uart0_count_val_tmp==3) || (uart0_count_val==3 && uart0_count_val_tmp==1) ||(uart0_count_val==1 && uart0_count_val_tmp==0) ||(uart0_count_val==0 && uart0_count_val_tmp==2))
{
uart0_count-=uart0_dir;
uart0_sendcount-=uart0_dir;
}
 else if( (uart0_count_val==3 && uart0_count_val_tmp==2) || (uart0_count_val==2 && uart0_count_val_tmp==0) ||(uart0_count_val==0 && uart0_count_val_tmp==1) ||(uart0_count_val==1 && uart0_count_val_tmp==3))
{
uart0_count+=uart0_dir;
uart0_sendcount+=uart0_dir;
}
uart0_count_val = uart0_count_val_tmp;
}
return uart0_count;
}

uint8_t Read_Gray_UART1(void )
{
uint8_t uart1_count_val=0;
if((GPIO_PORTC_DATA_R) & (PIN4))
uart1_count_val |= 0x02 ;
 if((GPIO_PORTC_DATA_R) & (PIN5))
uart1_count_val |= 0x01 ;
return uart1_count_val;
}

int uart1_poll(void)
{
uart1_count_val_tmp = Read_Gray_UART1();
if(uart1_count_val != uart1_count_val_tmp)
{
if( (uart1_count_val==2 && uart1_count_val_tmp==3) || (uart1_count_val==3 && uart1_count_val_tmp==1) ||(uart1_count_val==1 && uart1_count_val_tmp==0) ||(uart1_count_val==0 && uart1_count_val_tmp==2))
{
uart1_count-=uart1_dir;
uart1_sendcount-=uart1_dir;
}
 else if( (uart1_count_val==3 && uart1_count_val_tmp==2) || (uart1_count_val==2 && uart1_count_val_tmp==0) ||(uart1_count_val==0 && uart1_count_val_tmp==1) ||(uart1_count_val==1 && uart1_count_val_tmp==3))
{
uart1_count+=uart1_dir;
uart1_sendcount+=uart1_dir;
}
uart1_count_val = uart1_count_val_tmp;
}
return uart1_count ;
}

uint8_t Read_Gray_UART4(void )
{
uint8_t uart4_count_val=0;
if((GPIO_PORTJ_DATA_R) & (PIN0))
uart4_count_val |= 0x02 ;
 if((GPIO_PORTJ_DATA_R) & (PIN1))
uart4_count_val |= 0x01 ;
return uart4_count_val;
}

int uart4_poll(void)
{
uart4_count_val_tmp = Read_Gray_UART4();
if(uart4_count_val != uart4_count_val_tmp)
{
if( (uart4_count_val==2 && uart4_count_val_tmp==3) || (uart4_count_val==3 && uart4_count_val_tmp==1) ||(uart4_count_val==1 && uart4_count_val_tmp==0) ||(uart4_count_val==0 && uart4_count_val_tmp==2))
{
uart4_count-=uart4_dir;
uart4_sendcount-=uart4_dir;
}
 else if( (uart4_count_val==3 && uart4_count_val_tmp==2) || (uart4_count_val==2 && uart4_count_val_tmp==0) ||(uart4_count_val==0 && uart4_count_val_tmp==1) ||(uart4_count_val==1 && uart4_count_val_tmp==3))
{
uart4_count+=uart4_dir;
uart4_sendcount+=uart4_dir;
}
uart4_count_val = uart4_count_val_tmp;
}
return uart4_count ;
}

uint8_t Read_Gray_UART5(void )
{
uint8_t uart5_count_val=0;
if((GPIO_PORTJ_DATA_R) & (PIN2))
uart5_count_val |= 0x02 ;
 if((GPIO_PORTJ_DATA_R) & (PIN3))
uart5_count_val |= 0x01 ;
return uart5_count_val;
}

int uart5_poll(void)
{
uart5_count_val_tmp = Read_Gray_UART5();
if(uart5_count_val != uart5_count_val_tmp)
{
if( (uart5_count_val==2 && uart5_count_val_tmp==3) || (uart5_count_val==3 && uart5_count_val_tmp==1) ||(uart5_count_val==1 && uart5_count_val_tmp==0) ||(uart5_count_val==0 && uart5_count_val_tmp==2))
{
uart5_count-=uart5_dir;
uart5_sendcount-=uart5_dir;
}
 else if( (uart5_count_val==3 && uart5_count_val_tmp==2) || (uart5_count_val==2 && uart5_count_val_tmp==0) ||(uart5_count_val==0 && uart5_count_val_tmp==1) ||(uart5_count_val==1 && uart5_count_val_tmp==3))
{
uart5_count+=uart5_dir;
uart5_sendcount+=uart5_dir;
}
uart5_count_val = uart5_count_val_tmp;
}
return uart5_count ;
}

void encoder_init(uint32_t enc_port)
{
    if(enc_port & enc1)
    {
        gpio_interrupt(portk_gpio, PIN0, rising, enc1_isr);
        input(porte_gpio, PIN0);
    }
    if(enc_port & enc2)
    {
        gpio_interrupt(porte_gpio, PIN3, rising, enc2_isr);
        input(portp_gpio, PIN2);
    }
    if(enc_port & enc3)
    {
        gpio_interrupt(portg_gpio, PIN0, rising, enc3_isr);
        input(portg_gpio, PIN1);
    }
    if(enc_port & uart0_enc)
    {
        gpio_interrupt(porta_gpio, PIN0, rising, uart0_count_isr);
        input(porta_gpio, PIN1);
    }
    if(enc_port & uart1_enc)
    {
        gpio_interrupt(portc_gpio, PIN4, rising, uart1_count_isr);
        input(portc_gpio, PIN5);
    }
    if(enc_port & uart4_enc)
    {
        gpio_interrupt(portj_gpio, PIN0, rising, uart4_count_isr);
        input(portj_gpio, PIN1);
    }
    if(enc_port & uart5_enc)
    {
        gpio_interrupt(portj_gpio, PIN2, rising, uart5_count_isr);
        input(portj_gpio, PIN3);
    }
    if(enc_port & uart0_gray)
    {
        input(porta_gpio, PIN0|PIN1);
        pull_down(porta_gpio, PIN0|PIN1);
    }
    if(enc_port & uart1_gray)
    {
        input(portc_gpio, PIN4|PIN5);
        pull_down(portc_gpio, PIN4|PIN5);
    }
    if(enc_port & uart4_gray)
    {
        input(portj_gpio, PIN0|PIN1);
        pull_down(portj_gpio, PIN0|PIN1);
    }
    if(enc_port & uart5_gray)
    {
        input(portj_gpio, PIN2|PIN3);
        pull_down(portj_gpio, PIN2|PIN3);
    }
}

#endif /* MOTOR_ENCODER_H_ */
