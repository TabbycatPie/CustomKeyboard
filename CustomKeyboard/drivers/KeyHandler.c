#include "ch552.H"  
#include "KeyHandler.h"
#include "usb.h"


sbit KEY_PIN = P1^4;


unsigned long key_timer;


unsigned char key_last_stat;



//key event
#define KEY_NO_EVENT        0x00
#define KEY_HAS_EVENT       0xff
unsigned char key_event;

//click flag 
#define DOUBLE_FLAG   0xff  
#define SINGLE_FLAG   0x0f
#define NOTHIN_FLAG   0x00


#define TIME_UNIT 			   50 					   //50ms pre timer loop
#define CLICK_VALID_TIME   50/TIME_UNIT    //50ms avoid jiter
#define CLICK_VALID_RTIME 300/TIME_UNIT    //50ms avoid jiter
#define DOUB_TRI_TIME     500/TIME_UNIT		 //300ms for double click trigger
#define LONG_TRI_TIME    2000/TIME_UNIT    //2000ms for long press trigger

unsigned long key_press_time1;
unsigned long key_release_time1;
unsigned long key_press_time2;
unsigned long key_release_time2;

void initKey(){
	key_last_stat = KEY_RELEASED;
	key_event = KEY_NO_EVENT;
	key_timer = 0;
	key_press_time1 = 0;
	key_release_time1 = 0;
}

unsigned char readKey(){
	unsigned char read_key;
	if(!KEY_PIN){
		read_key = KEY_PRESSED;
	}
	else{
		read_key = KEY_RELEASED;
	}
	mDelaymS(8);//avoid jiter
	if(!KEY_PIN){
		if(read_key == KEY_PRESSED){
			return KEY_PRESSED;
		}
	}
	else{
		if(read_key == KEY_RELEASED){
			return KEY_RELEASED;
		}
	}
	return KEY_RELEASED;
}


void scanKey(){
	unsigned char read_key = readKey();
	if(read_key != key_last_stat){
		//key change
		key_last_stat = read_key; // update key last stat
		if(read_key == KEY_PRESSED){
			if(key_press_time1 > 0){
				key_press_time2 =  key_timer;
			}
			else{
				key_press_time1 = key_timer;   // record time 
			}
		}
		else{
			if(key_release_time1 > 0){
				key_release_time2 = key_timer;
			}
			else{
				key_release_time1 = key_timer; // record time
			}
		}
	}
	else{
		//key hold
		if(key_last_stat == KEY_PRESSED){
			if((key_timer - key_press_time1) >= LONG_TRI_TIME){
				long_press();
				key_timer = 0;
				key_press_time1 = 0;
				key_release_time1 = 0;
				key_press_time2 = 0;
				key_release_time2 = 0;
			}
		}
		//key_release
		else{
			//click check
			if(key_press_time1 > 0 
				&& ((key_release_time1 - key_press_time1) >= CLICK_VALID_TIME)
				&& (key_timer - key_release_time1) >= DOUB_TRI_TIME){
					click();
					key_timer = 0;
					key_press_time1 = 0;
					key_release_time1 = 0;
					key_press_time2 = 0;
					key_release_time2 = 0;
				}
			if(key_press_time1 > 0 
				&&(key_press_time2 - key_press_time1) <  DOUB_TRI_TIME 
				&&(key_release_time1 - key_press_time1) >= CLICK_VALID_TIME
				&&(key_timer - key_press_time2) >= CLICK_VALID_TIME){
					double_click();
					key_timer = 0;
					key_press_time1 = 0;
					key_release_time1 = 0;
					key_press_time2 = 0;
					key_release_time2 = 0;
				}
		}
	}
}

void KeyTimerTick(){
	key_timer++;
}

void KeyLoop(){
	scanKey();
}
	





