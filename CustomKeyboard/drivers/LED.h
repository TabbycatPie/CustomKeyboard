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


#define FORCE_BLINK 0xff
#define NORMAL_BLINK 0x00
//blink led: the led will go off $interval_100ms/10 sec and turn on it last stat for interval_100ms
//@para interval_100ms: blink interval,1 for 50ms
//@para blink_times: how many times the led blink
//@para force: FORCE_BLINK to reset other blink task and force blink itself
void LedBlinkStart(unsigned char _interval_50ms,char _blink_times,unsigned char force);
	
//led utils
void LedTurnOn(unsigned char color);
void LedTurnOffAll();

#endif
