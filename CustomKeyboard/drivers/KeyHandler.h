#ifndef __keyhandler__
#define __keyhandler__


//key press

#define LONE_PRESS_COUNT = 2; //


#define KEY_PRESSED         0
#define KEY_RELEASED        1
//key status
#define KEY_CLICKED         0x02
#define KEY_LONE_PRESSED    0x03
#define KEY_DOUBLE_CLICKED  0x04

sbit KEY_PIN = P1^4;

extern unsigned char Key_Status;


#define KEY_TIMER_START 0x00;
#define KEY_TIMER_STOP 0xff;
extern unsigned int pressing_counter;
extern unsigned char key_timer_sig;
