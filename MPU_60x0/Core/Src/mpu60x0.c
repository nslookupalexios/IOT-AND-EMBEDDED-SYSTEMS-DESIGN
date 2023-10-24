/*
 * mpu60x0.c
 *
 *  Created on: Oct 23, 2023
 *      Author: alewi
 */

#include "mpu60x0.h"

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

#define DLPF_CONFIG_VAL     0x02  // Ad esempio, per una frequenza di taglio di 98 Hz
#define GYRO_SCALE_VAL      0x18  // Ad esempio, per ±2000°/s
#define ACCEL_SCALE_VAL     0x10  // Ad esempio, per ±8g
#define INT_ENABLE_VAL      0x01  // Abilita interrupt per "Raw Data Ready"

HAL_StatusTypeDef MPU60X0_I2C_reset(I2C_HandleTypeDef *hi2c, I2C_ReadFuncType readFunc, I2C_WriteFuncType writeFunc, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint8_t reg_status;
    uint8_t command;
    uint8_t tries;

    // Reset the MPU60X0
    command = 0x80; // BIT_H_RESET
    ret = writeFunc(hi2c, MPU60X0_ADDRESS, POWER_MANAGEMENT_1, 1, &command, 1, timeout);
    if(ret != HAL_OK) return ret;

    HAL_Delay(100);

    tries = 10;
    while(--tries){
    	ret = readFunc(hi2c, MPU60X0_ADDRESS, POWER_MANAGEMENT_1, 1, &reg_status, 1, timeout);
    	if(ret != HAL_OK) return ret;
    	if (reg_status == POWER_MNG_1_DEFAULT_STAUTS) break;
    }
    if (reg_status != POWER_MNG_1_DEFAULT_STAUTS) return HAL_ERROR;

    // Wake up the device and set the internal clock source
    command = EN_INTERNAL_CLOCK;
    ret = writeFunc(hi2c, MPU60X0_ADDRESS, POWER_MANAGEMENT_1, 1, &command, 1, timeout);
    if(ret != HAL_OK) return ret;
    HAL_Delay(1); // attendere 1 ms
    // Configurare DLPF
    ret = readFunc(hi2c, MPU60X0_ADDRESS, CONFIG, 1, &reg_status, 1, timeout);
    if(ret != HAL_OK) return ret;

    command = reg_status & 0b11111000;
    ret = writeFunc(hi2c, MPU60X0_ADDRESS, CONFIG, 1, &command, 1, timeout);
    if(ret != HAL_OK) return ret;

    // Configurare scala del giroscopio
    ret = readFunc(hi2c, MPU60X0_ADDRESS, GYROSCOPECONFIG, 1, &reg_status, 1, timeout);
    if(ret != HAL_OK) return ret;

    command = reg_status & 0b11100111;
    ret = writeFunc(hi2c, MPU60X0_ADDRESS, GYROSCOPECONFIG, 1, &command, 1, timeout);
    if(ret != HAL_OK) return ret;

    // Configurare scala dell'accelerometro
    ret = readFunc(hi2c, MPU60X0_ADDRESS, ACCELEROMETERCONFIG, 1, &reg_status, 1, timeout);
    if(ret != HAL_OK) return ret;
    command = reg_status & 0b11100111;
    ret = writeFunc(hi2c, MPU60X0_ADDRESS, ACCELEROMETERCONFIG, 1, &command, 1, timeout);
    if(ret != HAL_OK) return ret;

    // Abilitare interrupt
    command = 0b00000001;
    ret = writeFunc(hi2c, MPU60X0_ADDRESS, INTERRUPTENABLE, 1, &command, 1, timeout);
    if(ret != HAL_OK) return ret;

    return HAL_OK;
}
