#include "led.h"
#include "ch552.H"  

#define TIMER_START 0x0f
#define TIMER_STOP  0x00
unsigned char led_timer_signal;

sbit RLED_PIN = P1^7;
sbit BLED_PIN = P1^6;

//LED blink 
char blink_times;
#define ON  0x00
#define OFF 0xff
char blink_flip;
unsigned char interval_50ms;


unsigned char led_last_stat;

void initLED(){
	LedTurnOffAll();
	led_timer = 0;
	led_timer_signal = TIMER_STOP;
	blink_times = 0;
	interval_50ms = 0;
	blink_flip = OFF;
}


void LedBlinkTask(){
	if(led_timer >= interval_50ms){
		led_timer = 0;
		if(blink_times > 0){
			if(blink_flip == ON){
				LedTurnOn(led_last_stat);
				blink_times --;
				blink_flip = OFF;
			}
			else{
				//temp down for a interval
				RLED_PIN = 1;
				BLED_PIN = 1;
				blink_flip = ON;
			}
		}
		else{
			//task compelete, reset timer
			led_timer_signal = TIMER_STOP;
			blink_times = 0;
			blink_flip = OFF;
		}
	}
}

// please put this funtion to 50ms interupt or somewhere be called roughly 50ms
void LedTimerLoop(){
	if(led_timer_signal == TIMER_START){
		led_timer++;
		LedBlinkTask();
	}
	else{
		led_timer = 0;
	}
}


void LedTurnOn(unsigned char color){
	//turn all lights off
	RLED_PIN = 1;
	BLED_PIN = 1;
	if((color & RED) == RED)
		RLED_PIN = 0;
  if((color & BLUE) == BLUE)
		BLED_PIN = 0;
	led_last_stat = color;
}


//blink led: the led will go off $interval_100ms/10 sec and turn on it last stat for interval_100ms
//@para interval_100ms: blink interval,1 for 50ms
//@para blink_times: how many times the led blink
void LedBlinkStart(unsigned char _interval_50ms,char _blink_times){
	blink_times = _blink_times;
	interval_50ms = _interval_50ms;
	//start timer if its stoped
	if(led_timer_signal == TIMER_STOP)
		led_timer_signal = TIMER_START;
}




void LedTurnOffAll(){
	RLED_PIN = 1;
	BLED_PIN = 1;
	led_last_stat = BLACK;
}