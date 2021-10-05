#ifndef __usb__
#define __usb__

#include "ch552.h"
#include "Debug.H"
#include "string.h"
//#include "flash.h"


#define VID 0x5131
#define PID 0x2019

extern UINT8 Ready,FLAG;


/* 用户自定义数据 */
extern UINT8X User_Ep2Buf_send[64];	//用户上报数据缓冲区
extern UINT8X User_Ep2Buf_rev[64];	//接收上位机数据缓存区
extern UINT8 HID_Busy;				//发送标志位
extern UINT8 HID_Rev;				//接收标志位
void HID_Send( );					//上报数据

/*键盘数据*/
extern UINT8 HIDKey[8];
void Keyboard_Send( );		//键盘数据上报
/*鼠标数据*/
extern UINT8 HIDMouse[4];
void Mouse_Send( );			//鼠标数据上报
/* 多媒体数据 */
extern UINT8 HIDMultimedia[1];
void Multimedia_Send( );	//多媒体数据上报


void USBDeviceInit(void);	//USB初始化
void USBDevWakeup(void);	//唤醒主机



#endif
