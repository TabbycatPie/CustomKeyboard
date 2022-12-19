#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"
#include "LED.h"
#include "MouseContrl.h"
#include "KeyHandler.h"


//SYSTEM
#define SYS_SHUT_DOWN 0x00
#define SYS_START     0x0f
unsigned char SYSTEM_STAT;

//MODES
#define DEF_MODE 0x00  //default mode: mouse move a rectangle with 100 as step
#define SRM_MODE 0x01  //small range mode:mouse move tiny steps with rectangle
#define RMM_MODE 0x02  //random move mode:mouse move randomly with 100 as step
#define MODE_COUNT 3;  //there are 3 modes
#define MODE_NVS_ADDR 5;
UINT8 mode = DEF_MODE;

//Movement time gap
#define DEF_GAP_VAL 30  //default 30sec
#define LON_GAP_VAL 120 //long    120sec
#define SML_GAP_VAL 5   //small   5sec
#define TINY_GAP_VAL 1  //tiny    1sec
#define DEF_GAP_PT 0    //pointor to DEF_GAP_VAL
#define LON_GAP_PT 1    //pointor to LON_GAP_VAL
#define SML_GAP_PT 2    //pointor to SML_GAP_VAL
#define TINY_GAP_PT 3   //pointor to TINY_GAP_VAL
const unsigned char gaps[4] = {DEF_GAP_VAL,LON_GAP_VAL,SML_GAP_PT,TINY_GAP_VAL}; // read only e.g: access val using gap_val = gaps[DEF_GAP_PT]

unsigned char time_sec = 0;
unsigned char time_unit = 0; // ++ every 50ms


////Config (stored in NVS)
UINT8 gap_config = DEF_GAP_VAL;
//--deleted
//#define NVS_GAP_CONFIG_LEN_PT 3;
//unsigned char gap_config[4] = {DEF_GAP_VAL,DEF_GAP_VAL,DEF_GAP_VAL,DEF_GAP_VAL};


#define ENABLED 0xff
#define DISABLED 0x00
unsigned char enable_movement = DISABLED; //0x00 for false 0xff for true

void gapBlink();

//void mDelayS(unsigned char sec){
//	char a = 0;
//	while(sec--){
//		for(a=0;a<4;a++){
//			mDelaymS(250);
//		}
//	}
//}


void switchMode(){
	mode++;
	mode %= MODE_COUNT;//there are 3 modes in total
	//save mode to NVS
	WriteDataFlash(5,&mode,1); // LAST_MODE is stored in NVS address 4, len 1 byte
}

//@deleted
//void _switchGap(){
//	gap_config[mode] ++;
//	gap_config[mode] %= 4;
//	//save config to NVS
//	WriteDataFlash(mode,gap_config + mode ,1); // "mode" config store in NVS address "$mode",len 1 byte
//}
void _switchGap(){
	gap_config ++;
	gap_config %= 4;
	//save config to NVS
	WriteDataFlash(0,&gap_config,1); // "mode" config store in NVS address "$mode",len 1 byte
}



/* 50ms triggers once */
void run_timer_50ms(void){
	unsigned char trigger_time;
	time_unit ++;
	KeyTimerTick();
	seedChange(1); //seed ++
	LedTimerLoop();
	if(time_unit >= 20){
		// 1 sec time hit,reset timer
		time_unit = 0;
		time_sec ++;
		trigger_time = gaps[gap_config];
		if(time_sec >= trigger_time){
			//enable movement
			enable_movement = ENABLED;
			//reset timer
			time_sec %= trigger_time;
		}
	}
}


void long_press(){
	if(SYSTEM_STAT == SYS_SHUT_DOWN){
		SYSTEM_STAT = SYS_START;
		LedTurnOn(mode + 1);
	}
	else{
		SYSTEM_STAT = SYS_SHUT_DOWN;
		LedTurnOffAll();
	}
}
void double_click(){
	switchGap();
	//blink led
	gapBlink();
}
void gapBlink(){
	switch(gap_config){
		case TINY_GAP_PT: // tiny 1s
			LedBlinkStart(1,11,FORCE_BLINK); //blink very fast for 3s
			break;
		case SML_GAP_PT: //small 5s	
			LedBlinkStart(3,7,FORCE_BLINK); //blink fast for 3s
			break;
		case DEF_GAP_PT: //defualt 30s	
			LedBlinkStart(7,5,FORCE_BLINK); //blink slow for 3s
			break;
		case LON_GAP_PT: //long 120s	
			LedBlinkStart(11,3,FORCE_BLINK); //blink very slow for 3s
			break;
	}
}

void click(){
	switchMode();
	//refresh led 
	LedTurnOn(mode + 1);
	gapBlink();
}
//load last config from NVS
void loadConfig(){
	ReadDataFlash(0,1,&gap_config);
	ReadDataFlash(5,1,&mode);
}

void fakeDeath(){
	while(SYSTEM_STAT == SYS_SHUT_DOWN){
		KeyLoop();
	}
}

void main(){
	
	unsigned int start_up = 500;
	
	CfgFsys();                    //CH552时钟选择配置
	mDelaymS(50);                 //修改主频等待内部晶振稳定,必加
	
	
	
  //init
	initKey();
	initLED();
	initMouse();
	
  EA = 1; //enable interrupt
	mDelaymS(100);  //wait interrupts to statble 
	
//	SYSTEM_STAT = SYS_SHUT_DOWN;
	
	//wait for long-press start signal
//	while(SYSTEM_STAT == SYS_SHUT_DOWN){
//		if(readKey() == KEY_PRESSED){
//			start_up --;
//		}
//		else{
//			start_up = 500;
//		}
//		if(start_up == 0){
//			SYSTEM_STAT = SYS_START;
//			break;
//		}
//	}
	

	USBDeviceInit();              //USB设备模式初始化
                     
	//load config for nvs
	loadConfig();
	LedTurnOn(mode + 1);
	gapBlink();
	
	while(1)
	{
		if(Ready)
		{
			//USB枚举成功处理
			FLAG = 0;
			KeyLoop();
			SmoothMouseMoveLoop();
			fakeDeath();
			if(enable_movement == ENABLED){
				if(mode == DEF_MODE){
					//default mode
					MoveMouseRect(1000);
					LedBlinkStart(1,1,NORMAL_BLINK);
				}
				else if(mode == SRM_MODE){
					//small range mode
					MoveMouseRect(160);
					LedBlinkStart(1,1,NORMAL_BLINK);
				}
				else{
					//random mode
					MoveMouseRandomly();
					LedBlinkStart(1,1,NORMAL_BLINK);
				}
				enable_movement = DISABLED;
			}
		}
		else
		{
			//这里是USB未枚举成功处理
			LedBlinkStart(10,1,NORMAL_BLINK);
		}
	}
}
