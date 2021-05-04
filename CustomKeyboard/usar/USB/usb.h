#ifndef __usb__
#define __usb__


/*用户自定义数据*/
extern UINT8X UserEp2Buf[64];
extern UINT8X Ep2Buffer[];
/*键盘数据*/
extern UINT8 HIDKey[8];
/*鼠标数据*/
extern UINT8 HIDMouse[4];


extern UINT8 SetupReq,SetupLen,Ready,Count,FLAG,UsbConfig;
extern UINT8 Endp2Rev;
extern UINT8 Endp2Busy;


void USBDeviceInit(void);
void Enp1IntIn( );
void Enp2IntIn( );
void Enp3IntIn( );

#endif
