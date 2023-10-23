/*
 * huart_tools.c
 *
 *  Created on: Oct 23, 2023
 *      Author: alewi
 */

#include "uart_tools.h"
#include <string.h>

HAL_StatusTypeDef UART_TransmitString(UART_HandleTypeDef *huart, const char *str, uint32_t timeout){
	return HAL_UART_Transmit(huart, (uint8_t*)str, strlen(str), timeout);
}
