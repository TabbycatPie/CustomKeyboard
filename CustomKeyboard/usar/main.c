#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"


#define L_KEY_MASK 0x01  // left key press mask
#define R_KEY_MASK 0x02  // right key press mask
#define M_KEY_MASK 0x04  // middle key press mask
#define X_N_MASK 0x10    // 1 for X axis negative
#define Y_N_MASK 0x20    // 1 for Y axis negative
//#define X_O_MASK 0x40    // 1 for X axis overflow
//#define Y_O_MASK 0x80    // 1 for Y axis overflow
//direction
#define GO_LEFT  0x01
#define GO_RIGHT 0x02 
#define GO_UP    0x04 
#define GO_DOWN  0x08
#define WIN_MODE 0xff

unsigned char step = 1;

void mDelayS(unsigned char sec){
	char a = 0;
	while(sec--){
		for(a=0;a<4;a++){
			mDelaymS(250);
		}
	}
}

void HIDMousesend(){
	FLAG = 0;
	Mouse_Send();    //if mouse key is set,then send mouse event
	while(FLAG == 0); 
}

void MoveMouse(char direction,unsigned char x,unsigned char y,unsigned char loop_time){
	memset(HIDMouse,0,sizeof(HIDMouse));
	HIDMouse[0] |= 0x08;
	if(direction != WIN_MODE){
		if(direction & GO_LEFT == GO_LEFT){
			HIDMouse[0] |= X_N_MASK;
			x = ~x;// x is complemental
			x++;
		}
		if(direction & GO_UP == GO_UP){
			HIDMouse[0] |= Y_N_MASK;
			y = ~y;
			y++;
		}
	}
	HIDMouse[1] = x;
	HIDMouse[2] = y;
	while(loop_time--){
		HIDMousesend();
	}
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
			MoveMouse(WIN_MODE,step,0,1); //mouse goes left
			mDelayS(2);
			MoveMouse(WIN_MODE,0,step,1); //mouse goes down 
			mDelayS(2);
			MoveMouse(WIN_MODE,-step,0,1); //mouse goes right
			mDelayS(2);
			MoveMouse(WIN_MODE,0,-step,1);  //mouse goes up
			mDelayS(2); // delay 2 seconds
		}
		else
		{
			//这里是USB未枚举成功处理
		}
	}
}
