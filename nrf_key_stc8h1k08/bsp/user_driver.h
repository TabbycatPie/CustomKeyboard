#ifndef   _user_driver_h
#define   _user_driver_h

#include "STC8H.h"


#define EX2             0x10

sbit user_k1  =  P3^3;
sbit user_k2  =  P3^6;
sbit user_k3  =  P3^0;
sbit user_k4  =  P3^7;


sbit rf_IRQ   =  P3^2;
sbit rf_CSN   =  P1^6;
sbit rf_CE    =  P1^2;
sbit user_led =  P1^1;

void user_spi_init(void);
unsigned char spi_send_rec_dat(unsigned char dat);
void user_gpio_init(void);
void user_timer_init(void);  //1ms
void goto_sleep(void);
#endif

 