/*
 * mpu60x0_registers.h
 *
 *  Created on: Oct 23, 2023
 *      Author: alewi
 */

#ifndef INC_MPU60X0_REGISTERS_H_
#define INC_MPU60X0_REGISTERS_H_

#define MPU60X0_ADDRESS					208U
#define SELFTESTX 						13U
#define SELFTESTY 						14U
#define SELFTESTZ 						15U
#define SELFTESTA 						16U
#define SAMPLERATEDIVIDER 				25U
#define CONFIG 							26U
#define GYROSCOPECONFIG 				27U
#define ACCELEROMETERCONFIG 			28U
#define FREEFALLACCELERATIONTHRESHOLD 	29U
#define FREEFALLDURATION 				30U
#define MOTIONDETECTIONTHRESHOLD 		31U
#define MOTIONDETECTIONDURATION 		32U
#define ZEROMOTIONDETECTIONTHRESHOLD 	33U
#define ZEROMOTIONDETECTIONDURATION 	34U
#define FIFOENABLE 						35U
#define I2CMASTERCTRL 					36U
#define I2CSLAVE0_RW_ADDRESS 			37U
#define I2CSLAVE0_REGISTER 				38U
#define I2CSLAVE0_CONTROL 				39U
#define I2CSLAVE1_RW_ADDRESS 			40U
#define I2CSLAVE1_REGISTER 				41U
#define I2CSLAVE1_CONTROL 				42U
#define I2CSLAVE2_RW_ADDRESS 			43U
#define I2CSLAVE2_REGISTER 				44U
#define I2CSLAVE2_CONTROL 				45U
#define I2CSLAVE3_RW_ADDRESS 			46U
#define I2CSLAVE3_REGISTER 				47U
#define I2CSLAVE3_CONTROL 				48U
#define I2CSLAVE4_RW_ADDRESS 			49U
#define I2CSLAVE4_REGISTER 				50U
#define I2CSLAVE4_D0 					51U
#define I2CSLAVE4_CONTROL 				52U
#define I2CSLAVE4_D1 					53U
#define I2CMASTERSTATUS 				54U
#define INTERRUPTPINCONFIG 				55U
#define INTERRUPTENABLE 				56U
#define INTERRUPTSTATUS 				58U
#define ACCELEROMETERX_OUTH 			59U
#define ACCELEROMETERX_OUTL 			60U
#define ACCELEROMETERY_OUTH 			61U
#define ACCELEROMETERY_OUTL 			62U
#define ACCELEROMETERZ_OUTH 			63U
#define ACCELEROMETERZ_OUTL 			64U
#define TEMPERATUREOUTH 				65U
#define TEMPERATUREOUTL 				66U
#define GYROSCOPEX_OUTH 				67U
#define GYROSCOPEX_OUTL 				68U
#define GYROSCOPEY_OUTH 				69U
#define GYROSCOPEY_OUTL 				70U
#define GYROSCOPEZ_OUTH 				71U
#define GYROSCOPEZ_OUTL 				72U
#define EXTERNALSENSORDATA0 			73U
#define EXTERNALSENSORDATA1 			74U
#define EXTERNALSENSORDATA2 			75U
#define EXTERNALSENSORDATA3 			76U
#define EXTERNALSENSORDATA4 			77U
#define EXTERNALSENSORDATA5 			78U
#define EXTERNALSENSORDATA6 			79U
#define EXTERNALSENSORDATA7 			80U
#define EXTERNALSENSORDATA8 			81U
#define EXTERNALSENSORDATA9 			82U
#define EXTERNALSENSORDATA10 			83U
#define EXTERNALSENSORDATA11 			84U
#define EXTERNALSENSORDATA12 			85U
#define EXTERNALSENSORDATA13 			86U
#define EXTERNALSENSORDATA14 			87U
#define EXTERNALSENSORDATA15 			88U
#define EXTERNALSENSORDATA16 			89U
#define EXTERNALSENSORDATA17 			90U
#define EXTERNALSENSORDATA18 			91U
#define EXTERNALSENSORDATA19 			92U
#define EXTERNALSENSORDATA20 			93U
#define EXTERNALSENSORDATA21 			94U
#define EXTERNALSENSORDATA22 			95U
#define EXTERNAL_SENSOR_DATA_23   		96U
#define MOTION_DETECTION_STATUS   		97U
#define I2C_SLAVE0_DATA_OUT       		99U
#define I2C_SLAVE1_DATA_OUT       		100U
#define I2C_SLAVE2_DATA_OUT       		101U
#define I2C_SLAVE3_DATA_OUT       		102U
#define I2C_MASTER_DELAY_CONTROL  		103U
#define SIGNAL_PATH_RESET         		104U
#define MOTION_DETECTION_CONTROL  		105U
#define USER_CONTROL              		106U
#define POWER_MANAGEMENT_1        		107U
#define POWER_MANAGEMENT_2        		108U
#define FIFO_COUNT_H              		114U
#define FIFO_COUNT_L              		115U
#define FIFO_READ_WRITE           		116U
#define WHO_AM_I                  		117U
#define POWER_MNG_1_DEFAULT_STAUTS		64U
#define EN_INTERNAL_CLOCK				0U

#endif /* INC_MPU60X0_REGISTERS_H_ */
