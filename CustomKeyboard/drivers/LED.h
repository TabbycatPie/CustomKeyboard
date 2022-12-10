#ifndef __led__
#define __led__


#include "ch552.H"  

#define RED    0x02
#define BLUE   0x01
#define PURPLE 0x03
#define BLACK  0x00


extern unsigned char led_timer;
//turn led on or off
void initLED();
void LedTimerLoop();

//blink led: the led will go off $interval_100ms/10 sec and turn on it last stat for interval_100ms
//@para interval_100ms: blink interval,1 for 50ms
//@para blink_times: how many times the led blink
void LedBlinkStart(unsigned char interval_50ms,char blink_times);

//led utils
void LedTurnOn(unsigned char color);
void LedTurnOffAll();

