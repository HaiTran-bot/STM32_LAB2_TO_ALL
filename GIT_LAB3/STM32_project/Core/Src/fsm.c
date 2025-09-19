/*
 * fsm.c
 *
 *  Created on: Sep 19, 2025
 *      Author: acer
 */
#include "global.h"

int autoStateH = INIT; //mode tu dong
int autoStateV = INIT;
int man_state = IDLE;

int red_duration = 5;
int yel_duration = 2;
int green_duration = 3;

int tempRed = 1;
int tempYel = 1;
int tempGrn = 1;

int horCount = 0;
int verCount = 0;
int scan = 0;
void segmentUpdateAuto(){ //update cho trang thai tu dong
	updateSegment2Digits(horCount, verCount);
}
void fsm_run(){
	fsm_auto_hor();
	fsm_auto_ver();
	fsm_man();
}
void button0_Signal(){ //first button pressed
	resetTimer(-1); // reset all state
	horCount = 0;
	verCount = 0;
	updateSegment(IDLE, IDLE, IDLE, IDLE);
	scan = 0;
	setLedH(IDLE);
	setLedV(IDLE);
	autoStateH = IDLE;
	autoStateV = IDLE;
	man_state = MAN_RED; //manual cua red vao dau tien
	set1(100);
	set3(100);
	return;

}
void fsm_auto_hor(){
	switch(autoStateH){
		case INIT:
			set1(red_duration*1000); //timer1 for hor state
			set2(1000); //for counter (1s)
			set3(100); //scanning LEDs
			horCount = red_duration - 1;
			autoStateH = RED;
			break;
		case RED:
			setLedH(RED);
			if(flag2 == 1){
				horCount--;
				if(verCount < 0) verCount;
				set2(1000);
			}
		   if(flag1 == 1){
			  set1(green_duration*1000);
			  horCount = green_duration - 1;
			  autoStateH = GRN;
		   }
		   if(flag3 == 1){
			   segmentUpdateAuto();
//			   scan = (scan == 1) ? 0 : 1;
			   scan = (scan + 1) % 2;
			   scanLED(scan);
			   set3(100);
		   }
		   button0_Signal();
		   break;
		case GRN:
			setLedH(GRN);
			if(flag2 == 1){
			horCount--;
			if(verCount < 0) verCount;
				set2(1000);
			}
			if(flag1 == 1){
				set1(yel_duration*1000);
				horCount = yel_duration - 1;
				autoStateH = YEL;
			}
			if(flag3 == 1){
				segmentUpdateAuto();
		//		scan = (scan == 1) ? 0 : 1;
				scan = (scan + 1) % 2;
				scanLED(scan);
				set3(100);
			}
			button0_Signal();
			break;

	}
}
