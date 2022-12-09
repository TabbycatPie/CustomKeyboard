#include "led.h"
#include "ch552.H"  




sbit RLED_PIN = P1^7;
sbit BLED_PIN = P1^6;

void LedTurnOn(unsigned char color){
	//turn all lights off
	RLED_PIN = 1;
	BLED_PIN = 1;
	if((color & RED) == RED)
		RLED_PIN = 0;
  if((color & BLUE) == BLUE)
		BLED_PIN = 0;
}

void LedTurnOffAll(){
	RLED_PIN = 1;
	BLED_PIN = 1;
}