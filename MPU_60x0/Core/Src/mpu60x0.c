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
