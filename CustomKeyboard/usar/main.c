#include "ch552.H"                                                      
#include "Debug.H"
#include "DataFlash.h"
#include "usb.h"
#include "LED.h"
#include "MouseContrl.h"
#include "KeyHandler.h"


//MODES
#define DEF_MODE 0x00  //default mode: mouse move a rectangle with 100 as step
#define SRM_MODE 0x01  //small range mode:mouse move tiny steps with rectangle
#define RMM_MODE 0x02  //random move mode:mouse move randomly with 100 as step
#define MODE_COUNT 3;  //there are 3 modes
unsigned char mode = DEF_MODE;

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


//Config (stored in NVS)
#define NVS_GAP_CONFIG_LEN_PT 3;
unsigned char gap_config[4] = {TINY_GAP_PT,TINY_GAP_PT,TINY_GAP_PT,TINY_GAP_PT};


#define ENABLED 0xff
#define DISABLED 0x00
unsigned char enable_movement = DISABLED; //0x00 for false 0xff for true





void mDelayS(unsigned char sec){
	char a = 0;
	while(sec--){
		for(a=0;a<4;a++){
			mDelaymS(250);
		}
	}
}


void switchMode(){
	mode++;
	mode %= MODE_COUNT;//there are 3 modes in total
	//save mode to NVS
	WriteDataFlash(4,&mode,1); // LAST_MODE is stored in NVS address 3, len 1 byte
}

void switchGap(){
	gap_config[mode] ++;
	gap_config[mode] %= 4;
	//save config to NVS
	WriteDataFlash(mode,&mode,1); // "mode" config store in NVS address "$mode",len 1 byte
}


/* 50ms triggers once */
void run_timer_50ms(void){
	unsigned char trigger_time;
	time_unit ++;
	seed ++;
	cur_time_50ms ++;
	LedTimerLoop();
	if(time_unit >= 20){
		// 1 sec time hit,reset timer
		time_unit = 0;
		time_sec ++;
		trigger_time = gaps[gap_config[mode]];
		if(time_sec >= trigger_time){
			//enable movement
			enable_movement = ENABLED;
			//reset timer
			time_sec %= trigger_time;
		}
	}
	
}




void main(){

	
	CfgFsys();                    //CH552时钟选择配置
	mDelaymS(50);                 //修改主频等待内部晶振稳定,必加
	
		
  //init
	//initKey();
	initLED();
	
	
	USBDeviceInit();              //USB设备模式初始化
	EA = 1;                       //允许单片机中断
	
  LedTurnOn(mode + 1);
	
	
	
	while(1)
	{
		//KeyLoop();
		if(Ready)
		{
			//USB枚举成功处理
			FLAG = 0;

			if(enable_movement == ENABLED){
				if(mode == DEF_MODE){
					//default mode
					MoveMouseRect(100);
					LedBlinkStart(3,1);
				}
				else if(mode == SRM_MODE){
					//small range mode
					MoveMouseRect(10);
					LedBlinkStart(10,2);
				}
				else{
					//random mode
					MoveMouseRandomly();
					LedBlinkStart(10,2);
				}
				enable_movement = DISABLED;
			}
		}
		else
		{
			//这里是USB未枚举成功处理
		}
	}
}
