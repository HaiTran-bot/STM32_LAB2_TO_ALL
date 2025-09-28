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
};
void display7SEG(int num){
	for (int i = 0; i < 7; i++) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, SEG_PATTERN[num][i]);
	 }
 }

//ex1
//int count_clock = 50; //50 * 10ms = 500ms
//int currentLED = 0;
//void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
//	count_clock--;
//	if(count_clock <= 0){
//		if(currentLED == 0){
//			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
//			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
//			display7SEG(1);
//			currentLED = 1;
//		}
//		else{
//			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
//			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
//			display7SEG(2);
//			currentLED = 0;
//
//		}
//		count_clock = 50;
//	}
//}

//ex2
//int clock_led = 100; //10ms*100 = 1s
//int clock_7seg = 50; //same as above
//int stage = 0; //init
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim){
//	clock_led--;
//	if(clock_led <= 0){
//		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
//		clock_led = 100;
//	}
//	clock_7seg--;
//	if(clock_7seg <= 0){
//		switch(stage){
//		case 0:
//		{
//			HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 0);
//			HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 1);
//			HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 1);
//			HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 1);
//			display7SEG(1);
//			stage = 1;
//			break;
//		}
//		case 1:
//		{
//			HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 1);
//			HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 0);
//			HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 1);
//			HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 1);
//			display7SEG(2);
//			stage = 2;
//			break;
//		}
//		case 2:
//		{
//			HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 1);
//			HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 1);
//			HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 0);
//			HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 1);
//			display7SEG(3);
//			stage = 3;
//			break;
//		}
//		case 3:
//		{
//			HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 1);
//			HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 1);
//			HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 1);
//			HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 0);
//			display7SEG(0);
//			stage = 0;
//			break;
//		}
//		}
//		clock_7seg = 50;
//	}
//
//}

//ex3
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

void update7SEG(int index) {
	if (index_led >= MAX_LED) index_led = 0;
    switch (index) {
        case 0:
            // Display the first 7SEG with led_buffer[0]
        	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 0);
        	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 1);
        	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 1);
        	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 1);
        	display7SEG(led_buffer[0]);
            break;
        case 1:
            // Display the second 7SEG with led_buffer[1]
        	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 1);
        	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 0);
        	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 1);
        	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 1);
        	display7SEG(led_buffer[1]);
            break;
        case 2:
            // Display the third 7SEG with led_buffer[2]
        	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 1);
        	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 1);
        	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 0);
        	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 1);
        	display7SEG(led_buffer[2]);
            break;
        case 3:
            // Display the fourth 7SEG with led_buffer[3]
        	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, 1);
        	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, 1);
        	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, 1);
        	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, 0);
        	display7SEG(led_buffer[3]);
            break;
        default:
            break;
    }
}
//int clock_led = 50;
//int clock_dot = 100;
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    clock_led--;
//    clock_dot--;
//
//    if (clock_led <= 0) {
//        update7SEG(index_led++);
//        clock_led = 50;
//    }
//     if (clock_dot <= 0) {
//         HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
//         clock_dot = 100;
//     }
//}

//ex4 and take ex3 upper part
//int clock_led = 25;
//int clock_dot = 100;
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    clock_led--;
//    clock_dot--;
//
//    if (clock_led <= 0) {
//        update7SEG(index_led++);
//        clock_led = 25;
//    }
//     if (clock_dot <= 0) {
//         HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
//         clock_dot = 100;
//     }
//}

/* USER CODE BEGIN 0 */
//ex5, ex6 and ex7 and ex8 ***take upd led7seg from ex3
int hour = 22, minute = 15, second = 55;
void updateClockBuffer(){
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}

int timer0_counter = 0;
int timer0_flag = 0;
int timer1_counter = 0;
int timer1_flag = 0;
int TIMER_CYCLE = 10;

void setTimer0(int duration) {
    timer0_counter = duration / TIMER_CYCLE;
    timer0_flag = 0;
}
void setTimer1(int duration) {
    timer1_counter = duration / TIMER_CYCLE;
    timer1_flag = 0;
}
void timer_run() {
    if (timer0_counter > 0) {
        timer0_counter--;
        if (timer0_counter == 0) {
            timer0_flag = 1;
        }
    }
    if (timer1_counter > 0) {
        timer1_counter--;
        if (timer1_counter == 0) {
              timer1_flag = 1;
           	   }
        }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
 timer_run();
 }
/* USER CODE END 0 */

#endif /* INC_SUPPORT_FUNC_H_ */
