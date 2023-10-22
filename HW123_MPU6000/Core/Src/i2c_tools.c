/*
 * i2c_tools.c
 *
 *  Created on: Oct 21, 2023
 *      Author: teodo
 */

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"

#define I2C_MAX_ADDRESS 127
#define BUFFER_SIZE 30

static uint8_t buffer[BUFFER_SIZE];

// HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)

uint8_t i2c_ports_scan(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef* huart, uint32_t timeout,uint32_t trials){
	uint8_t i = 0;
	uint8_t status = HAL_OK;
	uint16_t address;

	for(; i <= I2C_MAX_ADDRESS ; i++){
		address = i << 1;
	    if (HAL_I2C_IsDeviceReady(hi2c,address,trials,timeout) == HAL_OK)
	    {
	      sprintf((char*)buffer,"Response on address %d\r\n",i);
	      status = HAL_UART_Transmit( huart, buffer, BUFFER_SIZE, timeout);
	    }
	}

	if (i==127){
		status = HAL_OK;
	}else{
		status = HAL_ERROR;
	}
	return status;
}


