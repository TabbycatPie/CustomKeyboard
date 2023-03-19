#include "MouseContrl.h"
#include "stdlib.h"
#include "math.h"

#define L_KEY_MASK 0x01  // left key press mask
#define R_KEY_MASK 0x02  // right key press mask
#define M_KEY_MASK 0x04  // middle key press mask
#define X_N_MASK 0x10    // 1 for X axis negative
#define Y_N_MASK 0x20    // 1 for Y axis negative

//#define X_O_MASK 0x40    // 1 for X axis overflow
//#define Y_O_MASK 0x80    // 1 for Y axis overflow


//used for generate a random number
extern unsigned int seed;

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
//#define MOVE_INTERVAL 20
//void MoveMouseSmoothly(int x,int y,unsigned int time_ms){
//	double a_max_x,a_max_y,time,sumx,sumy;
//	char dx,dy;
//	a_max_x = ((double)x)/(time_ms/MOVE_INTERVAL);
//	a_max_y = ((double)y)/(time_ms/MOVE_INTERVAL);
//	//lock main timer
//	TIMER_PASS = PASS;
//	time = 0.0;
//	sumx = 0.0;
//	sumy = 0.0;
//	while(time <= time_ms){
//		time += MOVE_INTERVAL;
//		sumx += a_max_x;
//		sumy += a_max_y;
//		if(sumy > 1.0 || sumy < -1.0 || sumx > 1.0 || sumx < -1.0){
//			dx = (char)(sumx);
//			dy = (char)(sumy);
//			sumx = 0.0;
//			sumy = 0.0;
//			MoveMouse(WIN_MODE,dx,dy,1);
//		}
//		mDelaymS(MOVE_INTERVAL); //delay 5ms
//	}
//	TIMER_PASS = DO_NOT_PASS;
//}




double a_max_x,a_max_y,sumx,sumy;
unsigned int time,timeunit;
char dx,dy;

#define MOUSE_LOOP_ENABLE 0x00
#define MOUSE_LOOP_DISABLE 0xff
unsigned char mouse_loop_en;


#define MOVE_INTERVAL 50
void MoveMouseSmoothly(int x,int y,unsigned int time_ms){
	//config timer and vars
	timeunit = time_ms/MOVE_INTERVAL;
	a_max_x = 1.5f * ((double)x)/(timeunit*timeunit*timeunit);
	a_max_y = 1.5f * ((double)y)/(timeunit*timeunit*timeunit);
	time = 0;
	sumx = 0.0;
	sumy = 0.0;
	mouse_loop_en = MOUSE_LOOP_ENABLE;
}



void SmoothMouseMoveLoop(){
	if(mouse_loop_en == MOUSE_LOOP_ENABLE && time <= timeunit){
		if(time<= (double)(timeunit/4.0)){
			sumx += 0.5f * a_max_x * time * time;
			sumy += 0.5f * a_max_y * time * time;
		}
		else if( time > (double)(timeunit/4.0) && time <= (double)(timeunit*3.0/4.0)){
			sumx += ((-0.5f)*a_max_x*time*time + a_max_x*(timeunit/2)*time) - (a_max_x*timeunit*timeunit/16);
			sumy += ((-0.5f)*a_max_y*time*time + a_max_y*(timeunit/2)*time) - (a_max_y*timeunit*timeunit/16);
		}
		else{
			sumx += 0.5f * a_max_x * (timeunit-time) * (timeunit-time);
			sumy += 0.5f * a_max_y * (timeunit-time) * (timeunit-time);
		}
		if(sumy > 1.0 || sumy < -1.0 || sumx > 1.0 || sumx < -1.0){
			dx = (char)(sumx+(sumx>0?0.5:(-0.5)));
			dy = (char)(sumy+(sumy>0?0.5:(-0.5)));
			sumx = 0.0;
			sumy = 0.0;
			MoveMouse(WIN_MODE,dx,dy,1);
		}
		//mDelaymS(MOVE_INTERVAL); //delay 50ms
		time ++;
	}
	else{
		mouse_loop_en = MOUSE_LOOP_DISABLE;
	}
	
}

unsigned char rect_step = 0x00;
void MoveMouseRect(int step_len){
	switch(rect_step){
		case 0x00:
			MoveMouseSmoothly(step_len,0,1000); //move right
			break;
		case 0x01:
			MoveMouseSmoothly(0,step_len,1000);//move down
			break;
		case 0x02:
			MoveMouseSmoothly(-step_len,0,1000); //move left
			break;
		case 0x03:
			MoveMouseSmoothly(0,-step_len,1000); //move up
			break;
	}
	rect_step ++;
	rect_step %= 4;
}

float VectorLen(int x,int y){
	return sqrt(x*x+y*y);
}
float VectorDot(int x1,int y1,int x2,int y2){
	return x1*x2 + y1*y2;
}

#define RMAX 800
#define RMIN (-800)
#define BOTTOM  -9000
#define TOP 9000
#define LEFTMAX -15000
#define RIGHTMAX 15000
#define PI 3.1416

int cur_x = 0;
int cur_y = 0;
int last_x = 1;
int last_y = 0;
float cos_ang = 0;
long sum_x = 0;
long sum_y = 0;
char first_flag = 0x01;
void MoveMouseRandomly(){
	//initial cursor position at first time
	if(first_flag == 0x01){
		first_flag = 0x00;
		MoveMouse(WIN_MODE,-100,-100,30);
		MoveMouse(WIN_MODE,100,60,3);
	}
  //random num seed 
	while(1){
		seed ++;
		srand(seed);
		cur_x = (int)(rand()%(RMAX+1-RMIN))+RMIN;
		cur_y = (int)(rand()%(RMAX+1-RMIN))+RMIN;
		//avoid divide by zero exception
		if(cur_x == 0 && cur_y == 0){
			cur_x = 1;
		}
		//angle limitation
		cos_ang = (VectorDot(last_x,last_y,cur_x,cur_y))/(VectorLen(last_x,last_y) * VectorLen(cur_x,cur_y));
		if(cos_ang >= 0.0)
			break;
	}
	//boder limitation
	if(sum_y > TOP){
		cur_y = -1*abs(cur_y);
	}
	if(sum_y < BOTTOM){
		cur_y = abs(cur_y);
	}
	if(sum_x>RIGHTMAX){
		cur_x = -1*abs(cur_x);
	}
	if(sum_x < LEFTMAX){
		cur_x = abs(cur_x);
	}
	sum_x += cur_x;
	sum_y += cur_y;
	MoveMouseSmoothly(cur_x,cur_y,1000);
	last_x = cur_x;
	last_y = cur_y;
}

void initMouse(){
	seed = 0;
	TIMER_PASS = DO_NOT_PASS;
	mouse_loop_en = MOUSE_LOOP_DISABLE;
}