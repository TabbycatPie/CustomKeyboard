#include "led.h"
#include "ch552.H"  
#include "KeyHandler.h"

sbit KEY_PIN = P1^4;
void curNext();
void resetMem();
void recordKey(char key_stat);
long getLastKeyTime(char key_stat);
long getAncientKeyTime(char key_stat);

unsigned long key_press_times  [2]={0,0};
unsigned long key_release_times[2]={0,0};
unsigned char cur_index = 0;

#define KEY_PRESSED         0
#define KEY_RELEASED        1
unsigned char key_last_stat;

#define VALID   1
#define INVALID 0
char Valid();


//key status
#define KEY_CLICKED         0x02
#define KEY_LONE_PRESSED    0x03
#define KEY_DOUBLE_CLICKED  0x04
#define KEY_NO_EVENT        0x01

//click flag 
#define DOUBLE_FLAG   0xff  
#define SINGLE_FLAG   0x0f
#define NOTHIN_FLAG   0x00


#define TIME_UNIT 			   50 					   //50ms pre timer loop
#define KEY_VALID_TIME     50/TIME_UNIT    //50ms avoid jiter
#define CLICK_VALID_RTIME 250/TIME_UNIT    //50ms avoid jiter
#define DOUB_TRI_TIME     300/TIME_UNIT		 //300ms for double click trigger
#define LONG_TRI_TIME    2000/TIME_UNIT    //2000ms for long press trigger

void initKey(){
	cur_time_50ms = 0;
	cur_index = 0;
	key_last_stat = KEY_RELEASED;
}

void scanKey(){
	unsigned char read_key = KEY_PIN;
	if(read_key != key_last_stat){
		key_last_stat = read_key; // update key last stat
		recordKey(read_key);
		if(read_key == KEY_RELEASED){
			if(Valid() == VALID){
				//jiter filtered
				curNext();
			}
		}
	}
}
void handleKeyEvent(){
	//long press detect
	if(getLastKeyTime(KEY_RELEASED) - getLastKeyTime(KEY_PRESSED) >= LONG_TRI_TIME)
		long_press(),resetMem();
	//double click detect
	if(getLastKeyTime(KEY_PRESSED) - getAncientKeyTime(KEY_RELEASED) <= DOUB_TRI_TIME)
		double_click(),resetMem();
	//click detect
	if(cur_time_50ms - getLastKeyTime(KEY_PRESSED) >= CLICK_VALID_RTIME)
		click(),resetMem();
}
void KeyLoop(){
	scanKey();
	handleKeyEvent();
}
	



void resetMem(){
	cur_index = 0;
	key_release_times[0] = 0;
	key_release_times[1] = 0;
	key_press_times[0] = 0;
	key_press_times[1] = 0;
}
void recordKey(char key_stat){
	switch(key_stat){
		case KEY_PRESSED:
			key_press_times[cur_index] = cur_time_50ms;
			break;
		case KEY_RELEASED:
			key_release_times[cur_index] = cur_time_50ms;
			break;
	}
}
long getLastKeyTime(char key_stat){
	if(key_stat == KEY_PRESSED)
		return key_press_times[cur_index];
	else
		return key_release_times[cur_index];
}
long getAncientKeyTime(char key_stat){
	char ancient_index = (cur_index + 1)%2; 
	if(key_stat == KEY_PRESSED)
		return key_press_times[ancient_index];
	else
		return key_release_times[ancient_index];
	
}

void curNext(){
	cur_index ++;
	cur_index %= 2;
}


char Valid(){
	if(getLastKeyTime(KEY_RELEASED) - getLastKeyTime(KEY_PRESSED)>=1)
		return VALID;
	else 
		return INVALID;
}

