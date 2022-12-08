#include "led.h"
#include "ch552.H"  


#define RED  0x01
#define BLU  0x02


sbit RLED_PIN = P1^7;
sbit BLED_PIN = P1^6;

void LedTurnOn(unsigned char color){
	//turn all lights off
	RLED_PIN = 1;
	BLED_PIN = 1;
	if(color & RED == RED)
		RLED_PIN = 0;
	else if(color & BLU == BLU)
		BLED_PIN = 0
	else 
		return;
}