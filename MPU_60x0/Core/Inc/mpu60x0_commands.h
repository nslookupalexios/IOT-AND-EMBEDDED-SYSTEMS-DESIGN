/*
 * mpu60x0_commands.h
 *
 *  Created on: Oct 25, 2023
 *      Author: alewi
 */

#ifndef INC_MPU60X0_COMMANDS_H_
#define INC_MPU60X0_COMMANDS_H_

// 107, PWR_MGMT_1, RW

#define DEVICE_RESET         0b10000000  // 128U
#define SLEEP                0b01000000  // 64U
#define CYCLE                0b00100000  // 32U
#define TEMP_DIS             0b00001000  // 8U

#define CLKSEL_0             0b00000000  // 0U
#define CLKSEL_1             0b00000001  // 1U
#define CLKSEL_2             0b00000010  // 2U
#define CLKSEL_3             0b00000011  // 3U
#define CLKSEL_4             0b00000100  // 4U
#define CLKSEL_5             0b00000101  // 5U
#define CLKSEL_6             0b00000110  // 6U (Reserved, ma può essere utile definirlo per completezza)
#define CLKSEL_7             0b00000111  // 7U



// 26, CONFIG, RW
//// DLPF_CFG
#define DLPF_CFG_0               0b00000000  // 0U
#define DLPF_CFG_1               0b00000001  // 1U
#define DLPF_CFG_2               0b00000010  // 2U
#define DLPF_CFG_3               0b00000011  // 3U
#define DLPF_CFG_4               0b00000100  // 4U
#define DLPF_CFG_5               0b00000101  // 5U
#define DLPF_CFG_6               0b00000110  // 6U
#define DLPF_CFG_7               0b00000111  // 7U (Reserved, ma può essere utile definirlo per completezza)
//// EXT_SYNC_SET
#define EXT_SYNC_SET_DISABLED    0b00000000  // 0U
#define EXT_SYNC_SET_TEMP_OUT_L  0b00001000  // 1U
#define EXT_SYNC_SET_GYRO_XOUT_L 0b00010000  // 2U
#define EXT_SYNC_SET_GYRO_YOUT_L 0b00011000  // 3U
#define EXT_SYNC_SET_GYRO_ZOUT_L 0b00100000  // 4U
#define EXT_SYNC_SET_ACCEL_XOUT_L 0b00101000  // 5U
#define EXT_SYNC_SET_ACCEL_YOUT_L 0b00110000  // 6U
#define EXT_SYNC_SET_ACCEL_ZOUT_L 0b00111000  // 7U


//56, INT_ENABLE register, RW
#define FIFO_OFLOW_EN										1U
#define I2C_MST_INT_EN 										4U
#define DATA_RDY_EN 										8U


#endif /* INC_MPU60X0_COMMANDS_H_ */
