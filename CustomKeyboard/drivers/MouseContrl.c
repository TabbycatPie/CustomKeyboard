#include "MouseContrl.h"
#include "stdlib.h"

#define L_KEY_MASK 0x01  // left key press mask
#define R_KEY_MASK 0x02  // right key press mask
#define M_KEY_MASK 0x04  // middle key press mask
#define X_N_MASK 0x10    // 1 for X axis negative
#define Y_N_MASK 0x20    // 1 for Y axis negative
//#define X_O_MASK 0x40    // 1 for X axis overflow
//#define Y_O_MASK 0x80    // 1 for Y axis overflow


//used for generate a random number
unsigned int seed;

void HIDMousesend(){
	FLAG = 0;
	Mouse_Send();    //if mouse key is set,then send mouse event
	while(FLAG == 0); 
}



void MoveMouse(char direction,char x,char y,unsigned char loop_time){
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
  char x,y,fx,fy;
  //random num seed 
	seed ++;
  srand(seed);
  x = ((char)(rand()%(RMAX+1-RMIN)+RMIN))-130;
	seed ++;
  srand(seed);
  fx = (char)rand();
	if(fx%2==1){
		fx = -1;
	}
	else{
		fx = 1;
	}
	seed ++;
  srand(seed);
  fy = (char)rand();
	if(fy%2==1){
		fy = -1;
	}
	else{
		fy = 1;
	}
	seed ++;
  srand(seed);
  y = ((char)(rand()%(RMAX+1-RMIN)+RMIN))-130;
	MoveMouse(WIN_MODE,fx*x,fy*y,1);
}

void initSeed(){
	seed = 0;
}
void seedChange(unsigned int delta){
	seed += delta;
}