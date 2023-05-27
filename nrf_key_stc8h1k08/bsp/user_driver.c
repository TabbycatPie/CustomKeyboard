#include "user_driver.h"

#define EX3             0x20
#define EX4             0x40

void user_spi_init(void)
{
	SPCTL = 0xD3;    //使能SPI主机模式/2
	SPSTAT = 0xc0;   //清中断标志
}

unsigned char spi_send_rec_dat(unsigned char dat)
{
	unsigned char rec_dat = 0;
	SPDAT = dat;
	while (!(SPSTAT & 0x80));               //查询完成标志
	SPSTAT = 0xc0;                          //清中断标志
	rec_dat = SPDAT;
	return rec_dat;
}

void user_gpio_init(void)
{
	P1M0 = 0x46;
	P1M1 = 0x00;
	
	P3M0 = 0x00;
	P3M1 = 0x00;
	
	P3PU = 0xCD;   //开启3.6  3.3上拉电阻
}

void user_timer_init(void)  //1ms
	
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x0c;     
	TH0 = 0xfe;
	TR0 = 1;                                    //启动定时器
	ET0 = 1;                                    //使能定时器中断
}

void goto_sleep(void)
{
  //IT0 = 1;                                    //使能INT0下降沿中断
  //EX0 = 1;                                    //使能INT0中断
  IT1 = 1;                                 //使能INT1下降沿中断
  EX1 = 1;                                    //使能INT1中断                                   
  INTCLKO |= EX2;                              //使能INT2下降沿中断
	INTCLKO |= EX3;                             //使能INT3下降沿中断
  INTCLKO |= EX4;                             //使能INT4下降沿中断
	PCON |= 0x02;
}

void exti_sleep(void)
{
  IT1 = 1;  
  EX1 = 0;                                      
  INTCLKO = 0; 
}
