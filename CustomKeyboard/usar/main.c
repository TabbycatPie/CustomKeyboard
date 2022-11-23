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
	CfgFsys();                    //CH552ʱ��ѡ������
	mDelaymS(50);                 //�޸���Ƶ�ȴ��ڲ������ȶ�,�ؼ�
	USBDeviceInit();              //USB�豸ģʽ��ʼ��
	initKeyValue();              	//intialize key 
	EA = 1;                       //����Ƭ���ж�

	while(1)
	{
		if(Ready)
		{
			//USBö�ٳɹ�����
			FLAG = 0;
		}
		else
		{
			//������USBδö�ٳɹ�����
		}
	}
}
