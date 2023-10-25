/*
 * mpu60x0.h
 *
 *  Created on: Oct 23, 2023
 *      Author: alewi
 */

#ifndef INC_MPU60X0_H_
#define INC_MPU60X0_H_

#include "mpu60x0_registers.h"
#include "mpu60x0_commands.h"
#include "i2c.h"

/**
  * @brief  Type definition for I2C read functions.
  *         This abstracts the I2C read operation, allowing the use of different methods (Polling, DMA, IT).
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address
  * @param  MemAddress Memory address in the target device
  * @param  MemAddSize Size of the memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be read
  * @param  Timeout Timeout duration for the operation. Ignored for IT and DMA.
  * @retval HAL status of the operation
  */
typedef HAL_StatusTypeDef (*I2C_ReadFuncType)(I2C_HandleTypeDef*, uint16_t, uint16_t, uint16_t, uint8_t*, uint16_t, uint32_t);


/**
  * @brief  Type definition for I2C write functions.
  *         This abstracts the I2C write operation, allowing the use of different methods (Polling, DMA, IT).
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address
  * @param  MemAddress Memory address in the target device
  * @param  MemAddSize Size of the memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be read
  * @param  Timeout Timeout duration for the operation. Ignored for IT and DMA.
  * @retval HAL status of the operation
  */
typedef HAL_StatusTypeDef (*I2C_WriteFuncType)(I2C_HandleTypeDef*, uint16_t, uint16_t, uint16_t, uint8_t*, uint16_t, uint32_t);


/**
  * @brief  Wrapper for HAL_I2C_Mem_Read in blocking mode (Polling)
  */
HAL_StatusTypeDef HAL_I2C_Mem_Read_Wrapper(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Wrapper for HAL_I2C_Mem_Read using interrupts (IT)
  */
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT_Wrapper(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Wrapper for HAL_I2C_Mem_Read using Direct Memory Access (DMA)
  */
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA_Wrapper(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Read the WHO_AM_I register of the MPU60X0 sensor
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  result Pointer to the buffer to store the result
  * @param  readFunc Function pointer specifying the I2C read method to use (Polling, DMA, IT)
  * @param  timeout Timeout for the operation. Ignored if DMA or IT is used.
  * @retval HAL status of the operation
  */
HAL_StatusTypeDef MPU60X0_I2C_who_am_i(I2C_HandleTypeDef *hi2c, uint8_t *result, I2C_ReadFuncType readFunc, uint32_t timeout);

HAL_StatusTypeDef MPU60X0_I2C_reset(I2C_HandleTypeDef *hi2c, I2C_ReadFuncType readFunc, I2C_WriteFuncType writeFunc, uint32_t timeout);

#endif /* INC_MPU60X0_H_ */
