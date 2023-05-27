#include "user_driver.h"

#define EX3             0x20
#define EX4             0x40

void user_spi_init(void)
{
	SPCTL = 0xD3;    //ʹ��SPI����ģʽ/2
	SPSTAT = 0xc0;   //���жϱ�־
}

unsigned char spi_send_rec_dat(unsigned char dat)
{
	unsigned char rec_dat = 0;
	SPDAT = dat;
	while (!(SPSTAT & 0x80));               //��ѯ��ɱ�־
	SPSTAT = 0xc0;                          //���жϱ�־
	rec_dat = SPDAT;
	return rec_dat;
}

void user_gpio_init(void)
{
	P1M0 = 0x46;
	P1M1 = 0x00;
	
	P3M0 = 0x00;
	P3M1 = 0x00;
	
	P3PU = 0xCD;   //����3.6  3.3��������
}

void user_timer_init(void)  //1ms
	
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x0c;     
	TH0 = 0xfe;
	TR0 = 1;                                    //������ʱ��
	ET0 = 1;                                    //ʹ�ܶ�ʱ���ж�
}

void goto_sleep(void)
{
  //IT0 = 1;                                    //ʹ��INT0�½����ж�
  //EX0 = 1;                                    //ʹ��INT0�ж�
  IT1 = 1;                                 //ʹ��INT1�½����ж�
  EX1 = 1;                                    //ʹ��INT1�ж�                                   
  INTCLKO |= EX2;                              //ʹ��INT2�½����ж�
	INTCLKO |= EX3;                             //ʹ��INT3�½����ж�
  INTCLKO |= EX4;                             //ʹ��INT4�½����ж�
	PCON |= 0x02;
}

void exti_sleep(void)
{
  IT1 = 1;  
  EX1 = 0;                                      
  INTCLKO = 0; 
}
