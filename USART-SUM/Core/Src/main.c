/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUFFER_SIZE (256)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern uint8_t UART2_buffer[]; //
extern volatile uint8_t pending_interrupt;
uint32_t main_buffer[BUFFER_SIZE] = {0};
char temp_buffer[BUFFER_SIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t is_a_digit(uint8_t data) {
    return (data >= '0' && data <= '9') ? 1 : 0;
}

uint32_t sum_array(const uint32_t* array, uint32_t length) {

	uint32_t sum = 0;

    for (uint32_t i = 0; i < length; ++i) {
        sum += array[i];
    }

    return sum;
}

uint32_t int_to_str(uint32_t num, uint8_t* buffer) {
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }

    int i = 0;
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    buffer[i] = '\0';  // Terminate the string
    uint32_t len = i;

    // Reverse the string since we've built it backwards
    for (int start = 0, end = i - 1; start < end; start++, end--) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
    }
    return len;
}



void console_log(const char* message, uint8_t new_line){
    int message_size = strlen(message);
    static char send[BUFFER_SIZE];
    // If the message is empty, simply return
    if(message_size > BUFFER_SIZE-3){
    	strcpy(send, "ConsoleLogError!\r\n");
    	HAL_UART_Transmit(&huart2, (uint8_t *)send, strlen(send),HAL_UART_MAX_TX_DELAY);
    	return;
    }

    // Create a buffer to hold the message and the "\r\n"

    strcpy(send, message);  // Copy the original message
    if(new_line == 1) strcat(send, "\r\n");  // Append the newline

    HAL_UART_Transmit(&huart2, (uint8_t *)send, strlen(send),HAL_UART_MAX_TX_DELAY);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t main_buffer[BUFFER_SIZE] = {0};
	char temp_buffer[BUFFER_SIZE];
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
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, UART2_buffer, HAL_UART_BUFFER_LEN);
  uint16_t main_buffer_index = 0;
  uint16_t temp_buffer_index = 0;
  HAL_GPIO_WritePin(GPIOA, LD2_Pin, 1);
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOA, LD2_Pin, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  console_log("\r\n---------------------\r\nInserisci un numero: ",0);
  while (1)
  {
	  if(pending_interrupt == TRUE){
		  if ((HAL_UART_Receive(&huart2, UART2_buffer, HAL_UART_BUFFER_LEN, HAL_UART_MAX_RCV_DELAY) == HAL_OK)){
			  if(is_a_digit(*UART2_buffer)){
				  HAL_UART_Transmit(&huart2, UART2_buffer, HAL_UART_BUFFER_LEN, HAL_UART_MAX_TX_DELAY);
				  temp_buffer[temp_buffer_index++] = (char)(*UART2_buffer);
			  }

			  else if((*UART2_buffer)==' '){
				  temp_buffer[temp_buffer_index] = '\0';
				  temp_buffer_index = 0;

				  char *endptr;
				  unsigned long value = strtoul(temp_buffer, &endptr, 10);

				  if (*endptr == '\0' && value <= UINT32_MAX) {
				      main_buffer[main_buffer_index++] = (uint32_t)value;
				  }
				  console_log("\r\nNumero acquisito con succeso.\r\nInserisci un numero: ",0);
			  }

			  else if ((*UART2_buffer)=='.'){
				  unsigned long sum = sum_array(main_buffer,main_buffer_index);
				  main_buffer_index = 0;
				  main_buffer[main_buffer_index] = 0;
				  char to_transmit[BUFFER_SIZE];
				  sprintf(to_transmit,"\r\nSomma computata: %lu",sum);
				  console_log(to_transmit,1);
				  console_log("\r\nInserisci un numero: ",0);
			  }
			  else {
				  console_log("\r\nImpossibile classificare il carattere.\r\nInserisci un numero:",0);
			  }
		  }
		  //pending_interrupt = FALSE; Non capisco perché se lo decommento non partono più le IT.
	  }
    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
