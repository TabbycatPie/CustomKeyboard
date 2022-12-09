#include "MouseContrl.h"
#include "stdlib.h"


void HIDMousesend(){
	FLAG = 0;
	Mouse_Send();    //if mouse key is set,then send mouse event
	while(FLAG == 0); 
}



void MoveMouse(char direction,unsigned char x,unsigned char y,unsigned char loop_time){
	memset(HIDMouse,0,sizeof(HIDMouse));
	HIDMouse[0] |= 0x08;
	if(direction != WIN_MODE){
		if(direction & GO_LEFT == GO_LEFT){
			HIDMouse[0] |= X_N_MASK;
			x = ~x;// x is complemental
			x++;
		}
		if(direction & GO_UP == GO_UP){
			HIDMouse[0] |= Y_N_MASK;
			y = ~y;
			y++;
		}
	}
	HIDMouse[1] = x;
	HIDMouse[2] = y;
	while(loop_time--){
		HIDMousesend();
	}
}


unsigned char rect_step = 0x00;
void MoveMouseRect(unsigned char step_len){
	switch(rect_step){
		case 0:
			MoveMouse(WIN_MODE,step_len,0,1); //move right
			break;
		case 1:
			MoveMouse(WIN_MODE,0,step_len,1); //move down
			break;
		case 2:
			MoveMouse(WIN_MODE,-step_len,0,1); //move left
			break;
		case 3:
			MoveMouse(WIN_MODE,0,-step_len,1); //move up
			break;
	}
	rect_step ++;
	rect_step %= 4;
}


#define RMAX 250
#define RMIN 10

void MoveMouseRandomly(){
	char x,y;
	srand(seed);
	x = ((unsigned char)(rand()%(RMAX+1-RMIN)+RMIN))-130;
	srand(seed+x);
	y = ((unsigned char)(rand()%(RMAX+1-RMIN)+RMIN))-130;
	
	MoveMouse(WIN_MODE,x,y,1);
	
}