#ifndef __usb__
#define __usb__

#include "ch552.h"
#include "Debug.H"
#include "string.h"
//#include "flash.h"


#define VID 0x5131
#define PID 0x2019

extern UINT8 Ready,FLAG;

/*�������*/
extern UINT8 HIDMouse[4];
void Mouse_Send( );			//��������ϱ�


void USBDeviceInit(void);	//USB��ʼ��
void USBDevWakeup(void);	//��������



#endif
