#ifndef __usb__
#define __usb__

#include "ch552.h"
#include "Debug.H"
#include "string.h"
//#include "flash.h"


#define VID 0x5131
#define PID 0x2019

extern UINT8 Ready,FLAG;

/*鼠标数据*/
extern UINT8 HIDMouse[4];
void Mouse_Send( );			//鼠标数据上报


void USBDeviceInit(void);	//USB初始化
void USBDevWakeup(void);	//唤醒主机



#endif
