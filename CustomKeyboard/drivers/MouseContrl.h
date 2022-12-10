#ifndef __mousecontrl__
#define __mousecontrl__
#include "usb.h"



//direction
#define GO_LEFT  0x01
#define GO_RIGHT 0x02 
#define GO_UP    0x04 
#define GO_DOWN  0x08
#define WIN_MODE 0xff

//used for generate a random number
extern unsigned int seed;

//move mouse to (x,y) direction when @direction is WIN_MODE;x,y can be negative
//  @direction :reserved you can input WIN_MODE
//  @x         :the movement on x axis
//  @y         :the movement on y axis
//  @loop_time :how many times do you want the mouse to move repeatly with (x,y) you input before

void MoveMouse(char direction,unsigned char x,unsigned char y,unsigned char loop_time);


//move mouse to draw a rectangle at (100,100)
void MoveMouseRect(unsigned char step_len);

//as it's name :)
void MoveMouseRandomly();

//send HID package
void HIDMousesend();