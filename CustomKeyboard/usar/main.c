#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"

UINT8X MARCO_KEYCODE [50]= { 0x15,0x06,0x10,0x07,0x58,0x15,0x10,0x16,0x17,0x16,  //Win+r,c,m,d,Enter,Win+r,m,s,t,s,
														 0x06,0x58,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	 //c,Enter,,,,,,,,,
														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
													 };  //marco keycode

UINT8X MARCO_SPLIT_INDX [5] = {0,5,12,19,19};  //split marco key position

UINT8X MARCO_SPE_KEYINDX [10] = {0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
UINT8X MARCO_SPE_KEYCODE [10] = {0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

UINT8X MARCO_DELAY_INDX  [10] = {0x00,0x04,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
UINT8X MARCO_DELAY       [10] = {0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

UINT8X MOUSE_CODE [10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //temporily used for mouse 
UINT8X KEY_CODE   [10] = {0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};  //temporily used for key 
UINT8X SP_KEY_CODE[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //temporily used for sepcial key

//unpressed : 0x00
//  pressed :key_pressed[n] == 0xff
//if key(n) is a marco key 

UINT8X KEY_PRESS  [10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  
UINT8X KEY_MARCO  [10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//delay time*100ms
void MarcoDelay(UINT8 time){
	while(time--)
		mDelaymS(100);
}

//report key code to computer
void HIDsend(){
	FLAG = 0;
	Enp3IntIn();      //send mouse event
	while(FLAG == 0); /*等待上一包传输完成*/
	Enp1IntIn();    //send keyboard event
	while(FLAG == 0); 
}

//send marco key
void HIDmarco(UINT8 key_num){
	UINT8 i,j,delay_n00ms;
	//init HIDKey[]
	HIDKey[0] = 0x00;  //special key
	HIDKey[1] = 0x00;  //reserved
	HIDKey[2] = 0x00;  //key
	HIDKey[3] = 0x00;  
	HIDKey[4] = 0x00;
	HIDKey[5] = 0x00;
	HIDKey[6] = 0x00;
	HIDKey[7] = 0x00;
	HIDKey[8] = 0x00;
	//HIDKeysend();
	for(i=0;i<(MARCO_SPLIT_INDX[key_num]-MARCO_SPLIT_INDX[key_num-1]);i++){
		//prepare special key
		delay_n00ms = 0;
		HIDKey[0] = 0x00;
		for(j=0;j<10;j++){
			if(!(MARCO_SPE_KEYINDX[j]|MARCO_SPE_KEYCODE[j]))
				break;
			if(MARCO_SPE_KEYINDX[j]<MARCO_SPLIT_INDX[key_num-1])
				continue;
			if(MARCO_SPE_KEYINDX[j]>MARCO_SPLIT_INDX[key_num])
				break;
			if(MARCO_SPE_KEYINDX[j] == (MARCO_SPLIT_INDX[key_num-1]+i)){
				HIDKey[0] = MARCO_SPE_KEYCODE[j];
				break;
			}
		}
		//prepare delay
		for(j=0;j<10;j++){
			if(!(MARCO_DELAY_INDX[j]|MARCO_DELAY[j]))
				break;
			if(MARCO_DELAY_INDX[j]<MARCO_SPLIT_INDX[key_num-1])
				continue;
			if(MARCO_DELAY_INDX[j]>MARCO_SPLIT_INDX[key_num])
				break;
			if(MARCO_DELAY_INDX[j] == (MARCO_SPLIT_INDX[key_num-1]+i)){
				delay_n00ms = MARCO_DELAY[j];
				break;
			}
		}
		//prepare normal key
		HIDKey [2] = MARCO_KEYCODE[MARCO_SPLIT_INDX[key_num-1]+i];
		HIDsend();
		//delay
		MarcoDelay(delay_n00ms);
		mDelaymS(5);
		//bounce up
		HIDKey[0] = 0x00;
		HIDKey[2] = 0x00;
		//HIDsend();
	}
	//clear buffer
	HIDKey[0] = 0x00;
	HIDKey[2] = 0x00;
	HIDsend();
	//wait marco-key bounce up
	mDelaymS(200);
}


//10-key maping 
sbit Key1  = P3^2;
sbit Key2  = P1^4;
sbit Key3  = P1^5;
sbit Key4  = P1^6;
sbit Key5  = P1^7;
sbit Key6  = P3^1;
sbit Key7  = P3^0;
sbit Key8  = P1^1;
sbit Key9  = P3^3;
sbit Key10 = P3^4;


void scanKey(){
	UINT8 i = 0;
	UINT8 mouse_code = 0x00;
	UINT8 sp_key_code = 0x00;
	UINT8 key_count = 0;
	if(!Key1){
		KEY_PRESS[0]=0xff;
	}
	else{
		KEY_PRESS[0]=0x00;
	}
	if(!Key2){
		KEY_PRESS[1]=0xff;
	}
	else{
		KEY_PRESS[1]=0x00;
	}
	if(!Key3){
		KEY_PRESS[2]=0xff;
	}
	else{
		KEY_PRESS[2]=0x00;
	}
	if(!Key4){
		KEY_PRESS[3]=0xff;
	}
	else{
		KEY_PRESS[3]=0x00;
	}
	if(!Key5){
		KEY_PRESS[4]=0xff;
	}
	else{
		KEY_PRESS[4]=0x00;
	}
	if(!Key6){
		KEY_PRESS[5]=0xff;
	}
	else{
		KEY_PRESS[5]=0x00;
	}
	if(!Key7){
		KEY_PRESS[6]=0xff;
	}
	else{
		KEY_PRESS[6]=0x00;
	}
	if(!Key8){
		KEY_PRESS[7]=0xff;
	}
	else{
		KEY_PRESS[7]=0x00;
	}
	if(!Key9){
		KEY_PRESS[8]=0xff;
	}
	else{
		KEY_PRESS[8]=0x00;
	}
	if(!Key10){
		KEY_PRESS[9]=0xff;
	}
	else{
		KEY_PRESS[9]=0x00;
	}
	mDelaymS(6); //avoid jitter
	if(!Key1){
		if(KEY_PRESS[0]!=0xff){
			KEY_PRESS[0] =0x00;
		}
		else{
			if(KEY_MARCO[0]==0xff)
				HIDmarco(1);
		}
	}
	if(!Key2){
		if(KEY_PRESS[1]!=0xff){
			KEY_PRESS[1] =0x00;
		}
		else{
			if(KEY_MARCO[1]==0xff)
				HIDmarco(2);
		}
	}
	if(!Key3){
		if(KEY_PRESS[2]!=0xff){
			KEY_PRESS[2] =0x00;
		}
	}
	if(!Key4){
		if(KEY_PRESS[3]!=0xff){
			KEY_PRESS[3] =0x00;
		}
	}
	if(!Key5){
		if(KEY_PRESS[4]!=0xff){
			KEY_PRESS[4] =0x00;
		}
	}
	if(!Key6){
		if(KEY_PRESS[5]!=0xff){
			KEY_PRESS[5] =0x00;
		}
	}
	if(!Key7){
		if(KEY_PRESS[6]!=0xff){
			KEY_PRESS[6] =0x00;
		}
	}
	if(!Key8){
		if(KEY_PRESS[7]!=0xff){
			KEY_PRESS[7] =0x00;
		}
	}
	if(!Key9){
		if(KEY_PRESS[8]!=0xff){
			KEY_PRESS[8] =0x00;
		}
	}
	if(!Key10){
		if(KEY_PRESS[9]!=0xff){
			KEY_PRESS[9] =0x00;
		}
	}
	
	
	//get final result
	for(;i<10;i++){
		mouse_code  |= MOUSE_CODE[i] &KEY_PRESS[i]; //generate mouse_code
		sp_key_code |= SP_KEY_CODE[i]&KEY_PRESS[i]; //generate special_key_code
		//generate normal key_code
		if(key_count<6 && (KEY_PRESS[i]==0xff)){
			HIDKey[2+key_count]=KEY_CODE[i];
			key_count ++;
		}
	}
	
	//FINAL ASSIGNING
	//mouse codes
	HIDMouse[0] = mouse_code;
	//key codes
	HIDKey  [0] = sp_key_code; //special key Byte
	HIDKey  [1] = 0x00;        //reserved
	if(key_count<6){					 //fill blank
		for(i=7;i>=key_count+2;i--){
			HIDKey[i]=0x00;
		}
	}
	
}



void hadleReceive(){
	if(Endp2Rev != 0)
	{
		char i;
		Endp2Rev = 0;
		switch (Ep2Buffer[0]){
			case 0x01:
				//set_key_code
				for(i = 0; i< 10 ;i++){
				//copy normal key
					KEY_CODE[i]=Ep2Buffer[1+i];
				}
				WriteDataFlash(0x00,KEY_CODE,10);
				break;
			case 0x02:
				for(i = 0; i< 10 ;i++){
				//copy normal key
					SP_KEY_CODE[i]=Ep2Buffer[1+i];
				}
				WriteDataFlash(0x0a,SP_KEY_CODE,10);
		}
		
	}
}

void initKeyValue(){
	//read from data flash
	ReadDataFlash(0,10,KEY_CODE);
	ReadDataFlash(10,10,SP_KEY_CODE);
}

void main()
{
  CfgFsys( );                    //CH552时钟选择配置
  mDelaymS(20);                 //修改主频等待内部晶振稳定,必加

	/* 设置P1口为准双向IO口 */
	P1_MOD_OC = 0xff;
	P1_DIR_PU = 0xff;
	
	P3_MOD_OC = 0xFF;
	P3_DIR_PU = 0xFF;
	
	UEP1_T_LEN = 0;      //预使用发送长度一定要清空
	UEP2_T_LEN = 0;      //预使用发送长度一定要清空
	FLAG = 0;
	Ready = 0;
	
	USBDeviceInit();              //USB设备模式初始化
	
	initKeyValue();
	
	EA = 1;                       //允许单片机中断
	//等待USB枚举成功
	while(Ready == 0);
	while(1)
	{
		if(Ready)
		{
			scanKey();
			HIDsend();
			hadleReceive();
			FLAG = 0;
		}
	}
}
