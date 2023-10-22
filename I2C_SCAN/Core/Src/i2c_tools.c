/*
 * i2c_tools.c
 *
 *  Created on: Oct 22, 2023
 *      Author: guaro
 */

#include "stm32f4xx_hal.h"
#include "i2c_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For strlen

// Constants
#define I2C_MAX_ADDRESS 127
#define BUFFER_SIZE 30

// Static Variables
static uint8_t buffer[BUFFER_SIZE] = {0};
static const uint8_t SCAN_START_MESSAGE[] = "Starting I2C Scanning: \r\n";
static const uint8_t SPACE[] = {'.'};  // Defined as an array to avoid warnings

HAL_StatusTypeDef i2c_ports_scan(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef* huart, uint32_t timeout, uint32_t trials) {
    HAL_StatusTypeDef ret = HAL_ERROR;
    uint8_t n_devices = 0;

    // Transmit start message
    HAL_UART_Transmit(huart, SCAN_START_MESSAGE, sizeof(SCAN_START_MESSAGE) - 1, 10000);

    for(int i = 1; i <= I2C_MAX_ADDRESS; i++) {
        ret = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i << 1), trials, timeout);

        if (ret != HAL_OK) {  // No ACK Received At That Address
            HAL_UART_Transmit(huart, SPACE, sizeof(SPACE), 10000);
        } else if (ret == HAL_OK) {
            n_devices++;
            sprintf((char *)buffer, "0x%x", (uint16_t)(i << 1));
            HAL_UART_Transmit(huart, buffer, strlen((char *)buffer), 10000);
        }
    }

    // Transmit end message
    sprintf((char *)buffer, "\r\nDone! Founded %d devices\r\n\r\n", n_devices);
    HAL_UART_Transmit(huart, buffer, strlen((char *)buffer), 10000);

    return (n_devices < 1) ? HAL_ERROR : HAL_OK;
}
