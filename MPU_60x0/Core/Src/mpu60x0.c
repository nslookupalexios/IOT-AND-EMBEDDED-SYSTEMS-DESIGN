/*
 * mpu60x0.c
 *
 *  Created on: Oct 23, 2023
 *      Author: alewi
 */

#include "mpu60x0.h"
#include "uart_tools.h"

#define CHECK_HAL_STATUS(status) do { if((status) != HAL_OK) return HAL_ERROR; } while(0)


HAL_StatusTypeDef MPU60X0_I2C_who_am_i(I2C_HandleTypeDef *hi2c, uint8_t *result, I2C_ReadFuncType readFunc, uint32_t timeout) {
    HAL_StatusTypeDef ret = HAL_ERROR;
    if (readFunc != NULL) {
        ret = readFunc(hi2c, MPU60X0_ADDRESS, WHO_AM_I, 1, result, 1, timeout);
        if (ret == HAL_OK) {
            *result = (*result & 0b01111110) << 1;
        }
    }
    return ret;
}

HAL_StatusTypeDef MPU60X0_I2C_reset(I2C_HandleTypeDef *hi2c, I2C_ReadFuncType readFunc, I2C_WriteFuncType writeFunc, uint32_t timeout) {
    uint8_t reg_status;
    uint8_t command;
    uint8_t tries;

    // Reset the MPU60X0
    command = DEVICE_RESET; // BIT_H_RESET
    CHECK_HAL_STATUS(writeFunc(hi2c, MPU60X0_ADDRESS, PWR_MGMT_1, 1, &command, 1, timeout));
    //HAL_Delay(100); // dovrebbe esserci dell'attesa per il reset

    tries = 10;
    while(--tries){ //controllo se il bit di reset è settato a 0
    	CHECK_HAL_STATUS(readFunc(hi2c, MPU60X0_ADDRESS, PWR_MGMT_1, 1, &reg_status, 1, timeout));
    	if (reg_status == PWR_MGMT_1_DEFAULT_STATUS) break;
    }

    if (reg_status != PWR_MGMT_1_DEFAULT_STATUS) return HAL_ERROR;

    // Wake up the device and set the internal clock source
    command = CLKSEL_0;
    CHECK_HAL_STATUS(writeFunc(hi2c, MPU60X0_ADDRESS, PWR_MGMT_1, 1, &command, 1, timeout));
    HAL_Delay(1); // attendere 1 ms

    // Configurare DLPF
    CHECK_HAL_STATUS(readFunc(hi2c, MPU60X0_ADDRESS, CONFIG, 1, &reg_status, 1, timeout));
    command = (reg_status & 0b11111000) | DLPF_CFG_0;
    CHECK_HAL_STATUS(writeFunc(hi2c, MPU60X0_ADDRESS, CONFIG, 1, &command, 1, timeout));

    // Configurare scala del giroscopio
    CHECK_HAL_STATUS(readFunc(hi2c, MPU60X0_ADDRESS, GYRO_CONFIG, 1, &reg_status, 1, timeout));
    command = reg_status & 0b11100111;
    CHECK_HAL_STATUS(writeFunc(hi2c, MPU60X0_ADDRESS, GYRO_CONFIG, 1, &command, 1, timeout));

    // Configurare scala dell'accelerometro
    CHECK_HAL_STATUS(readFunc(hi2c, MPU60X0_ADDRESS, ACCEL_CONFIG, 1, &reg_status, 1, timeout));
    command = reg_status & 0b11100111;
    CHECK_HAL_STATUS(writeFunc(hi2c, MPU60X0_ADDRESS, ACCEL_CONFIG, 1, &command, 1, timeout));

    // Abilitare interrupt
    command = DATA_RDY_EN;
    CHECK_HAL_STATUS(writeFunc(hi2c, MPU60X0_ADDRESS, INT_ENABLE, 1, &command, 1, timeout));
    return HAL_OK;
}
