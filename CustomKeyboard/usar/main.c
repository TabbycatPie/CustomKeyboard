#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"

#define uchar = unsiged char

#define L_KEY_MASK 0x01  // left key press mask
#define R_KEY_MASK 0x02  // right key press mask
#define M_KEY_MASK 0x04  // middle key press mask
#define X_N_MASK 0x10    // 1 for X axis negative
#define Y_N_MASK 0x20    // 1 for Y axis negative
#define X_O_MASK 0x40    // 1 for X axis overflow
#define Y_O_MASK 0x80    // 1 for Y axis overflow
//direction
#define GO_LEFT  0x01
#define GO_RIGHT 0x02 
#define GO_UP    0x04 
#define GO_DOWN  0x08

void MoveMouse(char direction,char val){
	memset(HIDMouse,0,sizeof(HIDMouse));
	HIDMouse[0] |= 0x08;
	if(direction & GO_LEFT == GO_LEFT){
		HIDMouse[0] |= X_N_MASK;
	}
	if(direction & GO_UP == GO_UP){
		HIDMouse[0] |= Y_N_MASK;
	}
}

void HIDMousesend(){
	FLAG = 0;
	Mouse_Send();    //if mouse key is set,then send mouse event
	while(FLAG == 0); 
}



void main(){
	CfgFsys();                    //CH552时钟选择配置
	mDelaymS(50);                 //修改主频等待内部晶振稳定,必加
	USBDeviceInit();              //USB设备模式初始化
	EA = 1;                       //允许单片机中断

	while(1)
	{
		if(Ready)
		{
			//USB枚举成功处理
			FLAG = 0;
		}
		else
		{
			//这里是USB未枚举成功处理
		}
	}
}
