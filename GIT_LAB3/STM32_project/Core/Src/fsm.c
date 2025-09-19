/*
 * fsm.c
 *
 *  Created on: Sep 19, 2025
 *      Author: acer
 */
#include "global.h"

int autoStateH = INIT; //mode tu dong
int autoStateV = INIT;

int red_duration = 5;
int yel_duration = 2;
int green_duration = 3;

int tempRed = 1;
int tempYel = 1;
int tempGrn = 1;

int horCount = 0;
int verCount = 0;
int scan = 0;
void segmentUpdateAuto(){
	updateSegment2Digits(horCount, verCount);
}
