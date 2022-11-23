#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"


HIDMouse

void HIDMousesend(){
	if(CUR_MOUSE_KEY == 0xff && KEY_CHANGE == 0xff){
		FLAG = 0;
		Mouse_Send();    //if mouse key is set,then send mouse event
		while(FLAG == 0); 
	}
}



void main(){
	CfgFsys();                    //CH552时钟选择配置
	mDelaymS(50);                 //修改主频等待内部晶振稳定,必加
	USBDeviceInit();              //USB设备模式初始化
	initKeyValue();              	//intialize key 
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
