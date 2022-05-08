#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"
#include "stdlib.h"

#define LED1_INTERVAL 0x03
#define LED2_INTERVAL 0x04
//UINT8X MARCO_KEYCODE [50]= { 0x15,0x06,0x10,0x07,0x58,0x15,0x10,0x16,0x17,0x16,  //Win+r,c,m,d,Enter,Win+r,m,s,t,s,
//														 0x06,0x58,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	 //c,Enter,,,,,,,,,
//														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//													 };  //marco keycode

UINT8X MARCO_KEYCODE [34]= {0x00};  //marco keycode

UINT8X MARCO_SPLIT_INDX [11] = {0};  //split marco key position

UINT8X MARCO_SPE_KEYINDX [10] = {0x00};
UINT8X MARCO_SPE_KEYCODE [10] = {0x00};

UINT8X MARCO_DELAY_INDX  [10] = {0x00};
UINT8X MARCO_DELAY       [10] = {0x00};

UINT8X MEDIA_CODE [10] = {0x00};
UINT8X MOUSE_CODE [10] = {0x00};  //temporily used for mouse 
UINT8 KEY_CODE   [10] = {0x00};  //temporily used for key 
UINT8 SP_KEY_CODE[10] = {0x00};  //temporily used for sepcial key

//unpressed : 0x00
//pressed :key_pressed[n] == 0xff
//if key(n) is a marco key 

UINT8 KEY_PRESS  [10] = {0x00};
UINT8 LST_PRESS  [10] = {0x00};
UINT8 KEY_MARCO  [10] = {0x00};

UINT8X LAST_MEDIA_KEY = 0xff;
UINT8X CUR_MEDIA_KEY = 0xff;
UINT8X CUR_MEDIA_LAG = 0x0a;

UINT8X CUR_MOUSE_KEY = 0x00; //0xff mouse-key is pressed ,0xf0 send blank
UINT8X CUR_KEYBOARD = 0x00;  //0xff keboard-key is pressed,0xf0 send blank

UINT8X LAST_MARCO_KEY = 0xff;
UINT8X CUR_MARCO_KEY = 0xff;
UINT8X CUR_MARCO_LAG = 0x0a;

UINT8X KEY_CHANGE = 0x00;


UINT8X LED_ENABLE = 0xff;

unsigned char LED1_COLOR = 0x01; //led color 0 is dark
unsigned char LED1_CHANGE_COLOR = LED1_INTERVAL; //led change time interval
unsigned char LED1_OFF = 0xff;// time interval to turn off led
unsigned char LED2_COLOR = 0x03;//led color 0 is dark
unsigned char LED2_CHANGE_COLOR = LED2_INTERVAL; //led change time interval
unsigned char LED2_OFF = 0xff;// time interval to turn off led

//function declear
void TurnOnLED1();
void TurnOnLED2();

//delay time*100ms
void MarcoDelay(UINT8 time){
	while(time--)
		mDelaymS(100);
}

void HIDMousesend(){
	if(CUR_MOUSE_KEY == 0xff && KEY_CHANGE == 0xff){
		FLAG = 0;
		Mouse_Send();    //if mouse key is set,then send mouse event
		while(FLAG == 0); 
	}
}

void HIDKeysend(){
	if(CUR_KEYBOARD == 0xff && KEY_CHANGE == 0xff){
		FLAG = 0;	
		//send keyboard event
		Keyboard_Send();     
		while(FLAG == 0); /*等待上一包传输完成*/
	}
	if(CUR_KEYBOARD == 0xff && KEY_PRESS[1] == 0xff){
		TurnOnLED1();
	}
	if(CUR_KEYBOARD == 0xff && KEY_PRESS[0] == 0xff){
		TurnOnLED2();
	}
}
//send message to computer
void HIDsendMessage(){
	HID_Busy = 0;
	HID_Send();    //send message
	while(HID_Busy == 0); 
}

void HIDmediasend(){
	if(CUR_MEDIA_KEY!= 0xff){
		//valid key triggered
		if(CUR_MEDIA_KEY!=LAST_MEDIA_KEY){
			FLAG = 0;
			//pressed frist time
			Multimedia_Send();   //send media event
			while(FLAG == 0);
			
			HIDMultimedia[0] = 0;
			FLAG = 0;
			Multimedia_Send();   //send media event
			while(FLAG == 0);
		}
		else if(CUR_MEDIA_LAG == 0){
			FLAG = 0;
			Multimedia_Send();   //send media event
			while(FLAG == 0);
			HIDMultimedia[0] = 0;
			FLAG = 0;
			Multimedia_Send();   //send media event
			while(FLAG == 0);
			CUR_MEDIA_LAG = 0x02;
		}
		else if(CUR_MEDIA_KEY!= 0xff && CUR_MEDIA_KEY==LAST_MEDIA_KEY){
			CUR_MEDIA_LAG--;
		}
		LAST_MEDIA_KEY = CUR_MEDIA_KEY;
	}
	else{
		CUR_MEDIA_LAG = 0x2f;
		LAST_MEDIA_KEY = 0xff;
	}
	
	
//	HIDMultimedia[0] = 0;
//	Enp4IntIn();   //send media event
//	while(FLAG == 0); 
}

void HIDsendACK(UINT8 info){
	User_Ep2Buf_send[0] = 0x55;
	User_Ep2Buf_send[1] = 0x55;
	User_Ep2Buf_send[2] = 0x55;
	User_Ep2Buf_send[3] = info;
	HIDsendMessage();
	User_Ep2Buf_send[0] = 0x00;
	User_Ep2Buf_send[1] = 0x00;
	User_Ep2Buf_send[2] = 0x00;
	User_Ep2Buf_send[3] = 0x00;
}
//send marco key
void HIDmarco(UINT8 key_num){
	UINT8 i,j,delay_n00ms;
	//get key_num position
	UINT8 pos = 0;
	for(i=0;i<key_num;i++){
		if(KEY_MARCO[i]==0xff){
			pos++;
		}
	}
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
	for(i=0;i<(MARCO_SPLIT_INDX[pos]-MARCO_SPLIT_INDX[pos-1]);i++){
		//prepare special key
		delay_n00ms = 0;
		HIDKey[0] = 0x00;
		for(j=0;j<10;j++){
			if(!(MARCO_SPE_KEYINDX[j]|MARCO_SPE_KEYCODE[j]))
				break;
			if(MARCO_SPE_KEYINDX[j]<MARCO_SPLIT_INDX[pos-1])
				continue;
			if(MARCO_SPE_KEYINDX[j]>MARCO_SPLIT_INDX[pos])
				break;
			if(MARCO_SPE_KEYINDX[j] == (MARCO_SPLIT_INDX[pos-1]+i)){
				HIDKey[0] = MARCO_SPE_KEYCODE[j];
				break;
			}
		}
		//prepare delay
		for(j=0;j<10;j++){
			if(!(MARCO_DELAY_INDX[j]|MARCO_DELAY[j]))
				break;
			if(MARCO_DELAY_INDX[j]<MARCO_SPLIT_INDX[pos-1])
				continue;
			if(MARCO_DELAY_INDX[j]>MARCO_SPLIT_INDX[pos])
				break;
			if(MARCO_DELAY_INDX[j] == (MARCO_SPLIT_INDX[pos-1]+i)){
				delay_n00ms = MARCO_DELAY[j];
				break;
			}
		}
		//send delay
		MarcoDelay(delay_n00ms);
		//send sp keys
		
		//prepare normal key
		HIDKey [2] = MARCO_KEYCODE[MARCO_SPLIT_INDX[pos-1]+i];
		Keyboard_Send();    //send keyboard event
		while(FLAG == 0); 
		//delay
		//wait 20ms to bounce up to simulate human clicking
		mDelaymS(20);
		
		//bounce up
		HIDKey[0] = 0x00;
		HIDKey[2] = 0x00;
		Keyboard_Send();    //send keyboard event
		while(FLAG == 0); 
		
		mDelaymS(5);
		
	}
	//clear buffer
//	HIDKey[0] = 0x00;
//	HIDKey[2] = 0x00;
//	Enp1IntIn();    //send keyboard event
//	while(FLAG == 0); 
	//wait marco-key bounce up
	mDelaymS(50);
}
void HIDmarcosend(){
	if(CUR_MARCO_KEY!= 0xff){
		//valid key triggered
		if(CUR_MARCO_KEY!=LAST_MARCO_KEY){
			//pressed frist time
			HIDmarco(CUR_MARCO_KEY);
		}
		else if(CUR_MARCO_LAG == 0){
			HIDmarco(CUR_MARCO_KEY);
			CUR_MARCO_LAG = 0x02;
		}
		else if(CUR_MARCO_KEY!= 0xff && CUR_MARCO_KEY==LAST_MARCO_KEY){
			CUR_MARCO_LAG--;
		}
		LAST_MARCO_KEY = CUR_MARCO_KEY;
	}
	else{
		CUR_MARCO_LAG = 0x2f;
		LAST_MARCO_KEY = 0xff;
	}
}
//report key code to computer
void HIDsend(){
	HIDKeysend();
	HIDMousesend();
	HIDmediasend();
	HIDmarcosend();
}



//10-key maping 
sbit Key1  = P3^2;
sbit Key2  = P1^4;
sbit Key3  = P1^5;
sbit Key4  = P1^6;
sbit RLED2  = P1^7;
sbit GLED2  = P3^1;
sbit BLED2  = P3^0;
sbit RLED1  = P1^1;
sbit GLED1  = P3^3;
sbit BLED1  = P3^4;
void TurnOnLED1(){
	LED1_OFF = 0xff;
}
void TurnOnLED2(){
	LED2_OFF = 0xff;
}
void TurnOffLED1(){
	if(LED1_OFF != 0){
		LED1_OFF--;
	}
}
void TurnOffLED2(){
	if(LED2_OFF != 0){
		LED2_OFF--;
	}
}
void ChangeColor1(){
	if(LED1_CHANGE_COLOR == 0x00){
		LED1_COLOR ++;
		LED1_CHANGE_COLOR = LED1_INTERVAL;
	}else{
		LED1_CHANGE_COLOR --;
	}
}
void ChangeColor2(){
	if(LED2_CHANGE_COLOR == 0x00){
		LED2_COLOR ++;
		LED2_CHANGE_COLOR = LED2_INTERVAL;
	}else{
		LED2_CHANGE_COLOR --;
	}
}

void LED1_Show(unsigned char led){
	RLED1 = 1;
	GLED1 = 1;
	BLED1 = 1;
	if(LED1_OFF != 0x00 && LED_ENABLE == 0xff){
		if((0x01&led)==0x01){
			//Blue
			BLED1 = 0;
		}
		if((0x02&led)==0x02){
			//Green
			GLED1 = 0;
		}
		if((0x04&led)==0x04){
			//Red
			RLED1 = 0;
		}
	}
}
void LED2_Show(unsigned char led){
	RLED2 = 1;
	GLED2 = 1;
	BLED2 = 1;
	if(LED2_OFF != 0x00 && LED_ENABLE == 0xff){
		if((0x01&led)==0x01){
			//Blue
			BLED2 = 0;
		}
		if((0x02&led)==0x02){
			//Green
			GLED2 = 0;
		}
		if((0x04&led)==0x04){
			//Red
			RLED2 = 0;
		}
	}
}





void scanKey(){
	UINT8 i = 0;
	UINT8 mouse_code = 0x00;
	UINT8 sp_key_code = 0x00;
	UINT8 media_code = 0x00;
	UINT8 temp_code=0x00;
	UINT8 key_count = 0;
	CUR_MARCO_KEY = 0xff;
	KEY_CHANGE = 0x00;
	//LED contrl
	ChangeColor1();
	TurnOffLED1();
	LED1_Show(LED1_COLOR);
	ChangeColor2();
	TurnOffLED2();
	LED2_Show(LED2_COLOR);
	//key scan
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
	mDelaymS(6); //avoid jitter
	if(!Key1){
		if(KEY_PRESS[0]!=0xff){
			KEY_PRESS[0] =0x00;
		}
		else{
			if(KEY_MARCO[0]==0xff)
				CUR_MARCO_KEY = 1;
		}
	}
	if(!Key2){
		if(KEY_PRESS[1]!=0xff){
			KEY_PRESS[1] =0x00;
		}
		else{
			if(KEY_MARCO[1]==0xff)
				CUR_MARCO_KEY = 2;
		}
	}
	if(!Key3){
		if(KEY_PRESS[2]!=0xff){
			KEY_PRESS[2] =0x00;
		}
		else{
			if(KEY_MARCO[2]==0xff)
				CUR_MARCO_KEY = 3;
		}
	}
	if(!Key4){
		if(KEY_PRESS[3]!=0xff){
			KEY_PRESS[3] =0x00;
		}
		else{
			if(KEY_MARCO[3]==0xff)
				CUR_MARCO_KEY = 4;
		}
	}
	
	CUR_MOUSE_KEY = 0x00;
	CUR_KEYBOARD = 0x00;
	CUR_MEDIA_KEY = 0xff;
	//get final result
	for(;i<10;i++){
		mouse_code  |= MOUSE_CODE [i]&KEY_PRESS[i]; //generate mouse_code
		sp_key_code |= SP_KEY_CODE[i]&KEY_PRESS[i]; //generate special_key_code
		temp_code  = MEDIA_CODE [i]&KEY_PRESS[i]; //generate meida_key_code
		if(temp_code!=0){
			media_code = temp_code;
			CUR_MEDIA_KEY=i;
		}
		if(mouse_code!=0x00){
			CUR_MOUSE_KEY = 0xff;
		}
		if(sp_key_code!=0x00){
			CUR_KEYBOARD = 0xff;
		}
		if(KEY_PRESS[i] != LST_PRESS[i]){
			KEY_CHANGE = 0xff;
			LST_PRESS[i] = KEY_PRESS[i];
		}
		//generate normal key_code
		if(key_count<6 && (KEY_PRESS[i]==0xff)){
			HIDKey[2+key_count]=KEY_CODE[i];
			key_count ++;
			CUR_KEYBOARD = 0xff;
		}
	}
	//FINAL ASSIGNING
	//mouse codes
	if(HIDMouse[0]!=0x00 && mouse_code==0x00)
		CUR_MOUSE_KEY = 0xff;
	HIDMouse[0] = mouse_code;
	//meida codes
	HIDMultimedia[0] = media_code;
	//key codes
	if(HIDKey[0]!=0x00 && sp_key_code==0x00)
		CUR_KEYBOARD = 0xff;
	HIDKey  [0] = sp_key_code; //special key Byte
	HIDKey  [1] = 0x00;        //reserved
	if(key_count<6){					 //fill blank
		for(i=7;i>=key_count+2;i--){
			if(HIDKey[i]!=0x00 && key_count == 0)
				CUR_KEYBOARD = 0xff;
			HIDKey[i]=0x00;
		}
	}
}

void setMarco(unsigned char hi,unsigned char lo){
    unsigned char cur = 0x01;
    unsigned char i = 0;
    for(;cur!=0x00;cur<<=1){
        if((lo&cur)==cur){
            KEY_MARCO[i] = 0xff;
        }
				else{
					 KEY_MARCO[i] = 0x00;
				}
        i++;
    }
    for(cur=0x01;cur!=0x04;cur<<=1){
        if((hi&cur)==cur){
            KEY_MARCO[i] = 0xff;
        }
				else{
					KEY_MARCO[i] = 0x00;
				}
        i++;
    }
		//LED_CONTRL
		if((hi&0x04)==0x04)
			LED_ENABLE = 0xff;
		else
			LED_ENABLE = 0x00;
}


void handleReceive(){
	if(HID_Rev != 0)
	{
		char i;
		UINT8 temp[2];
		HID_Rev = 0;
		switch (User_Ep2Buf_rev[0]){
			case 0x01:
				//set_key_code
				for(i = 0; i< 10 ;i++){
				//copy normal key
					KEY_CODE[i]=User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(0,KEY_CODE,10);
				HIDsendACK(0x01);
				break;
			case 0x02:
				for(i = 0; i< 10 ;i++){
				//copy normal key
					SP_KEY_CODE[i]=User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(10,SP_KEY_CODE,10);
				HIDsendACK(0x02);
				break;
			case 0x03:
				//set_marco_key
				//get marco byte
				temp[0] = User_Ep2Buf_rev[1];
				temp[1] = User_Ep2Buf_rev[2];
				setMarco(temp[0],temp[1]);
				WriteDataFlash(20,temp,2);
				HIDsendACK(0x03);
				break;
			case 0x04:
				//set marco key
				//get marco indeices
			  for(i=0;i<11;i++){
					MARCO_SPLIT_INDX[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(22,MARCO_SPLIT_INDX,11);
				HIDsendACK(0x04);
				break;
			case 0x05:
				//set marco key
				//set sp-keys content
				for(i=0;i<10;i++){
					MARCO_SPE_KEYCODE[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(33,MARCO_SPE_KEYCODE,10);
				HIDsendACK(0x05);
				break;
			case 0x06:
				//set marco key
				//set sp-keys indeices
				for(i=0;i<10;i++){
					MARCO_SPE_KEYINDX[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(43,MARCO_SPE_KEYINDX,10);
				HIDsendACK(0x06);
				break;
			case 0x07:
				//set marco key
				//set marco key code
				for(i=0;i<34;i++){
					MARCO_KEYCODE[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(53,MARCO_KEYCODE,34);
				HIDsendACK(0x07);
				break;
			case 0x08:
				//set marco key
				//set mouse key code
				for(i=0;i<10;i++){
					MOUSE_CODE[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(87,MOUSE_CODE,10);
				HIDsendACK(0x08);
				break;
			case 0x09:
				//set marco key
				//set media key code
				for(i=0;i<10;i++){
					MEDIA_CODE[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(97,MEDIA_CODE,10);
				HIDsendACK(0x09);
				break;
			case 0x0a:
				//set marco key
				//set delay key code
				for(i=0;i<10;i++){
					MARCO_DELAY[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(107,MARCO_DELAY,10);
				HIDsendACK(0x0a);
				break;
			case 0x0b:
				//set marco key
				//set delay index key
				for(i=0;i<10;i++){
					MARCO_DELAY_INDX[i] = User_Ep2Buf_rev[1+i];
				}
				WriteDataFlash(117,MARCO_DELAY_INDX,10);
				HIDsendACK(0x0b);
				break;
			case 0x0c:
				//ack test
				HIDsendACK(0x0c);
				break;
			case 0x0d:
				User_Ep2Buf_send[0] = 0x01;
				HIDsendMessage();
				User_Ep2Buf_send[0] = 0x00;
				break;
			case 0x0f:
				//rgb LED on-off contrl
				ReadDataFlash(20,2,temp);
				if(User_Ep2Buf_rev[1]==0x01){
					LED_ENABLE = 0xff;
					temp[0]|=0x04;
				}else{
					LED_ENABLE = 0x00;
					temp[0]&=0x03;
				}
				WriteDataFlash(20,temp,2);
				HIDsendACK(0x0f);
				break;
		}
	}
}

void initKeyValue(){
	//read from data flash
	UINT8 _temp[2];
	ReadDataFlash(0,10,KEY_CODE);
	ReadDataFlash(10,10,SP_KEY_CODE);
	ReadDataFlash(20,2,_temp);
	setMarco(_temp[0],_temp[1]);
	ReadDataFlash(22,11,MARCO_SPLIT_INDX);
	ReadDataFlash(33,10,MARCO_SPE_KEYCODE);
	ReadDataFlash(43,10,MARCO_SPE_KEYINDX);
	ReadDataFlash(53,34,MARCO_KEYCODE);
  //if mouse key is used send mouse every time
	ReadDataFlash(87,10,MOUSE_CODE);
	ReadDataFlash(97,10,MEDIA_CODE);
	ReadDataFlash(107,10,MARCO_DELAY);
	ReadDataFlash(117,10,MARCO_DELAY_INDX);
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
			scanKey();
			HIDsend();
			handleReceive();
			FLAG = 0;
		}
		else
		{
			//这里是USB未枚举成功处理
		}
	}
}
