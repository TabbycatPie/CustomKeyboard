#ifndef __led__
#define __led__


#include "ch552.H"  

#define RED  0x01
#define BLUE 0x02

//turn led on or off
void LedTurnOn(unsigned char color);
void LedTurnOffAll();