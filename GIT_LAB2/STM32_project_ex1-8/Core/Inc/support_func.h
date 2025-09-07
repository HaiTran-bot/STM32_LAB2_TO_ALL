/*
 * support_func.h
 *
 *  Created on: Sep 7, 2025
 *      Author: haitran
 */

#ifndef INC_SUPPORT_FUNC_H_
#define INC_SUPPORT_FUNC_H_

#include "main.h"
int SEG_PATTERN[11][7] = {
    {0, 0, 0, 0, 0, 0, 1}, //0
    {1, 0, 0, 1, 1, 1, 1}, //1
    {0, 0, 1, 0, 0, 1, 0}, //2
    {0, 0, 0, 0, 1, 1, 0}, //3
    {1, 0, 0, 1, 1, 0, 0}, //4
    {0, 1, 0, 0, 1, 0, 0}, //5
    {0, 1, 0, 0, 0, 0, 0}, //6
    {0, 0, 0, 1, 1, 1, 1}, //7
    {0, 0, 0, 0, 0, 0, 0}, //8
    {0, 0, 0, 0, 1, 0, 0}, //9
	{1, 1, 1, 1, 1, 1, 1}
};
void display7SEG(int num){
	for (int i = 0; i < 7; i++) {
		if (num >= 0 && num <= 9){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, SEG_PATTERN[num][i]);
		}
		else for (int state = 0; state < 7; state++){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, SEG_PATTERN[10][i]); //all led for case not 0->9
		}
	 }
 }

//ex1
int count_clock = 50; //50 * 10ms = 500ms
int currentLED = 0;
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
	count_clock--;
	if(count_clock <= 0){
		if(currentLED == 0){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			display7SEG(2);
			currentLED = 1;
		}
		else{
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			display7SEG(1);
			currentLED = 0;

		}
		count_clock = 50;
	}
}
#endif /* INC_SUPPORT_FUNC_H_ */
