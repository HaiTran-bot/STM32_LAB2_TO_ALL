/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define MAX_BUFFER_SIZE 30
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		buffer[index_buffer++] = temp;
		if(index_buffer == 30) index_buffer = 0;
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}
uint8_t read_pos = 0;
uint8_t command_flag = 0; //0 = none, 1 = RST, 2 = OK
uint32_t uc_last_send_time = 0;
const uint32_t UC_TIMEOUT_MS = 3000;
char uc_tx_packet[32];
uint16_t uc_last_adc_value = 0;
uint8_t uc_state = 0; // 0 IDLE, 1 SEND_ADC, 2 WAIT_ACK, 3 RESEND
void command_parser_fsm(void){
	  static char token[32];
	  static uint8_t in_token = 0; // 0: not in token, 1: inside ! ... #
	  static uint8_t tpos = 0;

	  if(buffer_flag == 0) return;

	  while(read_pos != index_buffer){
	    uint8_t c = buffer[read_pos++];
	    if(read_pos == MAX_BUFFER_SIZE) read_pos = 0;
	    if(!in_token){
	      if(c == '!'){
	        in_token = 1;
	        tpos = 0;
	      }
	    } else {
	      if(c == '#'){
	        token[tpos] = '\0';
	        if(strcmp(token, "RST") == 0){
	          command_flag = 1; // RST
	        } else if(strcmp(token, "OK") == 0){
	          command_flag = 2; // OK
	        }
	        in_token = 0;
	        tpos = 0;
	      } else {
	        if(tpos < (sizeof(token)-1)){
	          token[tpos++] = (char)c;
	        } else {
	          // token overflow
	        }
	      }
	    }
	  }
	  buffer_flag = 0;
}
//void uart_communiation_fsm(void)
//{
//  uint32_t now = HAL_GetTick();
//
//  switch(uc_state){
//    case 0: // UC_IDLE
//      if(command_flag == 1){
//        command_flag = 0;
//        uc_last_adc_value = 0;
//        HAL_ADC_Start(&hadc1);
//        if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK){
//          uc_last_adc_value = (uint16_t)HAL_ADC_GetValue(&hadc1);
//        }
//        HAL_ADC_Stop(&hadc1);
//        snprintf(uc_tx_packet, sizeof(uc_tx_packet), "!ADC=%u#\r\n", (unsigned)uc_last_adc_value);
//        uc_state = 1;
//      }
//      break;
//
//    case 1: // UC_SEND_ADC
//      HAL_UART_Transmit(&huart2, (uint8_t*)uc_tx_packet, (uint16_t)strlen(uc_tx_packet), 200);
//      uc_last_send_time = HAL_GetTick();
//      uc_state = 2;
//      break;
//
//    case 2: // UC_WAIT_ACK
//      if(command_flag == 2){ // OK
//        command_flag = 0;
//        uc_state = 0;
//      } else {
//        if((now - uc_last_send_time) >= UC_TIMEOUT_MS){
//          uc_state = 3; // RESEND
//        }
//      }
//      break;
//
//    case 3: // UC_RESEND
//      HAL_UART_Transmit(&huart2, (uint8_t*)uc_tx_packet, (uint16_t)strlen(uc_tx_packet), 200);
//      uc_last_send_time = HAL_GetTick();
//      uc_state = 2;
//      break;
//
//    default:
//      uc_state = 0; break;
//  }
//}
void uart_communiation_fsm(void)
{
  uint32_t now = HAL_GetTick();

  switch(uc_state){
    case 0: // UC_IDLE
      if(command_flag == 1){   //RST
        command_flag = 0;
        HAL_ADC_Start(&hadc1);
        if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK){
          uc_last_adc_value = (uint16_t)HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);
        snprintf(uc_tx_packet, sizeof(uc_tx_packet), "!ADC=%u#\r\n", (unsigned)uc_last_adc_value);
        uc_state = 1;
      }
      break;

    case 1: // UC_SEND_ADC
      HAL_UART_Transmit(&huart2, (uint8_t*)uc_tx_packet, (uint16_t)strlen(uc_tx_packet), 200);
      uc_last_send_time = HAL_GetTick();
      uc_state = 2;
      break;

    case 2: // UC_WAIT_ACK
      if(command_flag == 2){ //OK
        command_flag = 0;
        uc_state = 0; //IDLE
      } else {
        if((now - uc_last_send_time) >= UC_TIMEOUT_MS){
          HAL_ADC_Start(&hadc1);
          if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK){
            uc_last_adc_value = (uint16_t)HAL_ADC_GetValue(&hadc1);
          }
          HAL_ADC_Stop(&hadc1);
          snprintf(uc_tx_packet, sizeof(uc_tx_packet), "!ADC=%u#\r\n", (unsigned)uc_last_adc_value);
          uc_state = 3;
        }
      }
      break;

    case 3: // UC_RESEND
      HAL_UART_Transmit(&huart2, (uint8_t*)uc_tx_packet, (uint16_t)strlen(uc_tx_packet), 200);
      uc_last_send_time = HAL_GetTick();
      uc_state = 2;
      break;

    default:
      uc_state = 0;
      break;
  }
}

/* USER CODE END 0 */
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_UART_Receive_IT(&huart2, &temp, 1);
//  HAL_ADC_Start(&hadc1);
  while (1)
  {
    /* USER CODE END WHILE */
	  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	  if(buffer_flag == 1){
	  command_parser_fsm();
	  buffer_flag = 0;
	  }
	  uart_communiation_fsm();
	  HAL_Delay(500);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_RED_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
