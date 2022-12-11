#ifndef __keyhandler__
#define __keyhandler__




extern void long_press();
extern void double_click();
extern void click();


void initKey();
void KeyLoop();
void KeyTimerTick();

#define KEY_PRESSED         0x00
#define KEY_RELEASED        0xff
unsigned char readKey();
