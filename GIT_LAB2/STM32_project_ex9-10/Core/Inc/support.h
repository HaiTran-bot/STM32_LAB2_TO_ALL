/*
 * support.h
 *
 *  Created on: Sep 9, 2025
 *      Author: acer
 */

#ifndef INC_SUPPORT_H_
#define INC_SUPPORT_H_
#include "main.h"

//ex9
//const int MAX_LED_MATRIX = 8;
//int index_led_matrix = 0;
//
////uint8_t matrix_buffer[8] = {0x01, 0x02, 0x03, 0x04,0x05, 0x06, 0x07, 0x08};
//uint8_t matrix_buffer_A[8] = {
//  0x3C, // 00111100
//  0x66, // 01100110
//  0x66, // 01100110
//  0x7E, // 01111110
//  0x66, // 01100110
//  0x66, // 01100110
//  0x66, // 01100110
//  0x00 //all 0
//};
//void resetState() {
//    for (int i = 0; i < MAX_LED_MATRIX; i++) {
//        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin << i, RESET);
//    }
//}
//
//void updateLEDMatrix() {
//	    for (int i = 0; i < MAX_LED_MATRIX; i++) {
//	        HAL_GPIO_WritePin(GPIOA, ENM0_Pin << i, GPIO_PIN_RESET);
//	    }
//	    for (int i = 0; i < MAX_LED_MATRIX; i++) {
//	        HAL_GPIO_WritePin(GPIOB, ROW0_Pin << i, GPIO_PIN_RESET);
//	    }
//
//	    int row_data = 0;
//	    switch (index_led_matrix) {
//	        case 0:
//	            row_data = matrix_buffer_A[0];
//	            break;
//	        case 1:
//	            row_data = matrix_buffer_A[1];
//	            break;
//	        case 2:
//	            row_data = matrix_buffer_A[2];
//	            break;
//	        case 3:
//	            row_data = matrix_buffer_A[3];
//	            break;
//	        case 4:
//	            row_data = matrix_buffer_A[4];
//	            break;
//	        case 5:
//	            row_data = matrix_buffer_A[5];
//	            break;
//	        case 6:
//	            row_data = matrix_buffer_A[6];
//	            break;
//	        case 7:
//	            row_data = matrix_buffer_A[7];
//	            break;
//	        default:
//	            row_data = 0x00;
//	            break;
//	    }
//
//	    //to column
//	    for (int bit = 0; bit < MAX_LED_MATRIX; bit++) {
//	        GPIO_PinState state = (row_data & (1 << bit)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
//	        HAL_GPIO_WritePin(GPIOB, ROW0_Pin << bit, state);
//	    }
//
//	    //current column
//	    HAL_GPIO_WritePin(GPIOA, ENM0_Pin << index_led_matrix, GPIO_PIN_SET);
//}
//void displayLEDMatrix() {
//	  updateLEDMatrix();
//	  index_led_matrix++;
//	  if (index_led_matrix >= MAX_LED_MATRIX){
//	    index_led_matrix = 0;
//	  }
//}
//int counter = 0, flag = 0;
//int const cycle = 10;
//void setTimer(int dur){
//	counter = dur/cycle;
//	flag = 0;
//}
//void runTimer(){
//	counter--;
//	if(counter == 0) flag = 1;
//}
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	runTimer();
//}

//ex10
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;

//uint8_t matrix_buffer[8] = {0x01, 0x02, 0x03, 0x04,0x05, 0x06, 0x07, 0x08};
uint8_t matrix_buffer_A[8] = {
  0x3C, // 00111100
  0x66, // 01100110
  0x66, // 01100110
  0x7E, // 01111110
  0x66, // 01100110
  0x66, // 01100110
  0x66, // 01100110
  0x00 //all 0
};
void resetState() {
    for (int i = 0; i < MAX_LED_MATRIX; i++) {
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin << i, RESET);
    }
}

void updateLEDMatrix() {
	    for (int i = 0; i < MAX_LED_MATRIX; i++) {
	        HAL_GPIO_WritePin(GPIOA, ENM0_Pin << i, GPIO_PIN_RESET);
	    }
	    for (int i = 0; i < MAX_LED_MATRIX; i++) {
	        HAL_GPIO_WritePin(GPIOB, ROW0_Pin << i, GPIO_PIN_RESET);
	    }

	    int row_data = 0;
	    switch (index_led_matrix) {
	        case 0:
	            row_data = matrix_buffer_A[0];
	            break;
	        case 1:
	            row_data = matrix_buffer_A[1];
	            break;
	        case 2:
	            row_data = matrix_buffer_A[2];
	            break;
	        case 3:
	            row_data = matrix_buffer_A[3];
	            break;
	        case 4:
	            row_data = matrix_buffer_A[4];
	            break;
	        case 5:
	            row_data = matrix_buffer_A[5];
	            break;
	        case 6:
	            row_data = matrix_buffer_A[6];
	            break;
	        case 7:
	            row_data = matrix_buffer_A[7];
	            break;
	        default:
	            row_data = 0x00;
	            break;
	    }

	    //to column
	    for (int bit = 0; bit < MAX_LED_MATRIX; bit++) {
	        GPIO_PinState state = (row_data & (1 << bit)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	        HAL_GPIO_WritePin(GPIOB, ROW0_Pin << bit, state);
	    }

	    //current column
	    HAL_GPIO_WritePin(GPIOA, ENM0_Pin << index_led_matrix, GPIO_PIN_SET);
}
void displayLEDMatrix() {
	  updateLEDMatrix();
	  index_led_matrix++;
	  if (index_led_matrix >= MAX_LED_MATRIX){
	    index_led_matrix = 0;
	  }
}

void shiftLeftMatrixCircular() {
    for (int i = 0; i < MAX_LED_MATRIX; i++) {
        uint8_t msb = (matrix_buffer_A[i] & 0x80) >> 7;
        matrix_buffer_A[i] <<= 1;
        matrix_buffer_A[i] |= msb;
    }
}
int counter = 0, flag = 0;
int const cycle = 10;
void setTimer(int dur){
	counter = dur/cycle;
	flag = 0;
}
void runTimer(){
	counter--;
	if(counter == 0) flag = 1;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	runTimer();
}



#endif /* INC_SUPPORT_H_ */
