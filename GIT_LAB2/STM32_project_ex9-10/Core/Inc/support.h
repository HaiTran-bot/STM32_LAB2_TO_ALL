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


//ex10
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
//
//void shiftLeftMatrixCircular() {
//    for (int i = 0; i < MAX_LED_MATRIX; i++) {
//        uint8_t msb = (matrix_buffer_A[i] & 0x80) >> 7;
//        matrix_buffer_A[i] <<= 1;
//        matrix_buffer_A[i] |= msb;
//    }
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

//ex9
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {0b00000000, 0b11111100, 0b00010010,
		0b00010001, 0b00010001, 0b00010010, 0b11111100, 0b00000000}; //8 col, each bit is 1 row, bit ngoai cung la row 0
void displayLEDMtrix(uint8_t value)
{
    if (value & (1U << 0))
        HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, GPIO_PIN_RESET);

    if (value & (1U << 1))
        HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, GPIO_PIN_RESET);

    if (value & (1U << 2))
        HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, GPIO_PIN_RESET);

    if (value & (1U << 3))
        HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, GPIO_PIN_RESET);

    if (value & (1U << 4))
        HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, GPIO_PIN_RESET);

    if (value & (1U << 5))
        HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, GPIO_PIN_RESET);

    if (value & (1U << 6))
        HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, GPIO_PIN_RESET);

    if (value & (1U << 7))
        HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, GPIO_PIN_RESET);
}

void updateLEDMatrix(int index)
{
    switch (index)
    {
    case 0:
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 1:
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 2:
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 3:
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 4:
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 5:
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 6:
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    case 7:
        HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);
        displayLEDMtrix(matrix_buffer[index]);
        break;
    default:
        break;
    }
}
void updateMatrixBuffer()
{
	uint8_t temp = matrix_buffer[0];
	matrix_buffer[0] = matrix_buffer[1];
	matrix_buffer[1] = matrix_buffer[2];
	matrix_buffer[2] = matrix_buffer[3];
	matrix_buffer[3] = matrix_buffer[4];
	matrix_buffer[4] = matrix_buffer[5];
	matrix_buffer[5] = matrix_buffer[6];
	matrix_buffer[6] = matrix_buffer[7];
	matrix_buffer[7] = temp;
}
int counter0 = 0, flag0 = 0;
int counter1 = 0, flag1 = 0;
int const cycle = 10;
void setTimer0(int dur_ms){ counter0 = dur_ms / cycle; flag0 = 0; }
void setTimer1(int dur_ms){ counter1 = dur_ms / cycle; flag1 = 0; }
void runTimer(void){
    if (counter0>0) counter0--;
    if (counter1>0) counter1--;

    if (counter0 == 0) flag0 = 1;
    if (counter1 == 0) flag1 = 1;

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    runTimer();
}
#endif /* INC_SUPPORT_H_ */
