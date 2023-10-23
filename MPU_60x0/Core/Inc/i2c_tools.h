/*
 * i2c_tools.h
 *
 *  Created on: Oct 21, 2023
 *      Author: teodo
 */

#ifndef INC_I2C_TOOLS_H_
#define INC_I2C_TOOLS_H_

#include "i2c.h"
#include "usart.h"





/**
 * Scansiona gli indirizzi I2C su una porta specifica per individuare dispositivi connessi.
 *
 * Questa funzione esegue una scansione di tutti gli indirizzi I2C possibili sulla porta specificata
 * utilizzando l'istanza `hi2c` e verifica se ci sono dispositivi I2C rispondenti. Ogni indirizzo I2C possibile
 * viene generato e tenta di inviare una richiesta I2C a quell'indirizzo.
 *
 * @param hi2c       Puntatore a una struttura I2C_HandleTypeDef configurata per la porta I2C di interesse.
 * @param huart      Puntatore a una struttura UART_HandleTypeDef per l'invio dei messaggi di risposta.
 * @param timeout    Tempo massimo di attesa per le operazioni I2C e UART.
 * @param trials     Numero di tentativi per ciascun indirizzo I2C.
 *
 * @return           Restituisce HAL_OK se almeno un dispositivo I2C risponde, altrimenti HAL_ERR.
 *
 * @note             La funzione invierà un messaggio UART per ciascun indirizzo I2C che risponde. Il timeout
 *                   specificato è utilizzato per controllare le operazioni I2C e UART. La funzione considera
 *                   gli indirizzi I2C da 0 a 127 (7 bit) e eseguirà il numero di tentativi specificato per ciascun
 *                   indirizzo.
 */
uint8_t i2c_ports_scan(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *huart, uint32_t timeout,uint32_t trials);


#endif /* INC_I2C_TOOLS_H_ */
