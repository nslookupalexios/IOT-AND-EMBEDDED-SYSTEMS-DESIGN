/*
 * uart_tools.h
 *
 *  Created on: Oct 22, 2023
 *      Author: alewi
 */

#ifndef INC_UART_TOOLS_H_
#define INC_UART_TOOLS_H_



#include "usart.h"
#include <string.h>
#include <stdint.h>

/**
 * @brief Transmit a null-terminated string via UART.
 *
 * @param huart UART handle
 * @param str Null-terminated string to transmit
 * @param timeout Timeout duration
 * @return HAL_StatusTypeDef Status of UART transmission
 */
HAL_StatusTypeDef UART_TransmitString(UART_HandleTypeDef *huart, const char *str, uint32_t timeout);

#endif /* INC_UART_TOOLS_H_ */
