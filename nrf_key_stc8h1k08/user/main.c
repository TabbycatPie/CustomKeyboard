#include "STC8H.h"
#include "si24R1.h"
#include "user_driver.h"

//#define REMOTER_EXPAND //if define this, the remoter will be used as a key expantion remoter

#define    default_sleep_time    80

unsigned int sec_tick = 0;
unsigned int sleep_time = default_sleep_time;
unsigned char sendflag = 0;

typedef struct
{
	unsigned char msg_id;
	unsigned char rfSendKeyValue;
}_rf_pack;

_rf_pack rf_pack;

void TM0_Isr() interrupt 1
{
	sec_tick++;
	if(sec_tick == 50)
	{
		sendflag = 1;
		sec_tick = 0;
	}
	if((user_k1!=0) && (user_k2!=0) && (user_k3!=0) && (user_k4!=0))
	{
		if(sleep_time > 0)
		{
			sleep_time--;
		}
	}
	else
	{
		sleep_time = default_sleep_time;
	}
}

/*
void INT0_Isr() interrupt 0 
{
  user_led = 0;
	sleep_time = default_sleep_time;
}
*/

void INT1_Isr() interrupt 2 
{
	user_led = 0;
	sleep_time = default_sleep_time;
}

void INT2_Isr() interrupt 10 
{
	user_led = 0;
	sleep_time = default_sleep_time;
}

void INT3_Isr() interrupt 11 
{
  user_led = 0;
	sleep_time = default_sleep_time;
}

void INT4_Isr() interrupt 16 
{
  user_led = 0;
	sleep_time = default_sleep_time;
}

int main(void)
{
	EA = 0;
	rf_pack.msg_id = 2;
	user_spi_init();
	user_timer_init();
	user_gpio_init();
	SI24R1_Config_Init();
	user_led = 0;
	EA = 1;
	for(;;)
	{
		if(sendflag == 1)
		{
			sendflag = 0;
			if(user_k1 == 0)
			{
				user_led = 0;
				//define a REMOTER_EXPAND make the remoter a expand remoter
				#ifdef REMOTER_EXPAND
				rf_pack.rfSendKeyValue = 0x05;
				#else
				rf_pack.rfSendKeyValue = 0x01;
				#endif
			}
			else if(user_k2 == 0)
			{
				user_led = 0;
				#ifdef REMOTER_EXPAND
				rf_pack.rfSendKeyValue = 0x06;
				#else
				rf_pack.rfSendKeyValue = 0x02;
				#endif
			}
			else if(user_k3 == 0)
			{
				#ifdef REMOTER_EXPAND
				rf_pack.rfSendKeyValue = 0x07;
				#else
				rf_pack.rfSendKeyValue = 0x03;
				#endif
			}
			else if(user_k4 == 0)
			{
				user_led = 0;
				#ifdef REMOTER_EXPAND
				rf_pack.rfSendKeyValue = 0x08;
				#else
				rf_pack.rfSendKeyValue = 0x04;
				#endif
			}
			else
			{
				sleep_time = 0;
				rf_pack.rfSendKeyValue = 0;
			}
			 
			if(SI24R1_Read_IRQ_Status() & MAX_TX)
			{
				SI24R1_RF_ClearIRQ(MAX_TX);
			}
			SI24R1_SendData((unsigned char*)&rf_pack,TX_PLOAD_WIDTH,1);
		}
		if(sleep_time == 0)
		{
			user_led = 1;
			rf_pack.msg_id++;
			rf_pack.msg_id %= 250;
			SI24R1_power_off();
			goto_sleep();
			sleep_time = default_sleep_time;
		}
	}
}
