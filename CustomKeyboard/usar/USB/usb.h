#ifndef __usb__
#define __usb__

#include "ch552.h"
#include "Debug.H"
#include "string.h"
//#include "flash.h"


#define VID 0x5131
#define PID 0x2019

extern UINT8 Ready,FLAG;


/* �û��Զ������� */
extern UINT8X User_Ep2Buf_send[64];	//�û��ϱ����ݻ�����
extern UINT8X User_Ep2Buf_rev[64];	//������λ�����ݻ�����
extern UINT8 HID_Busy;				//���ͱ�־λ
extern UINT8 HID_Rev;				//���ձ�־λ
void HID_Send( );					//�ϱ�����

/*��������*/
extern UINT8 HIDKey[8];
void Keyboard_Send(UINT8 len);		//���������ϱ�
/*�������*/
extern UINT8 HIDMouse[4];
void Mouse_Send( );			//��������ϱ�
/* ��ý������ */
extern UINT8 HIDMultimedia[1];
void Multimedia_Send( );	//��ý�������ϱ�


void USBDeviceInit(void);	//USB��ʼ��
void USBDevWakeup(void);	//��������



#endif
