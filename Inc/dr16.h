/*
 * dr16.c
 *
 * This file contains code for interfacing with the DR16 receiver to read
 * the controller data.
 */

#ifndef _DR16_H_
#define _DR16_H_

#include "usart.h"
#include "remote.h"

#define DR16_PACKET_LEN 18
#define DR16_MAX_LEN    50

// Public API:
const remote_info_t *dr16_get_remote(void);

// Backend functions
// Starts the dma collection of remote control data
void dr16_dma_init(UART_HandleTypeDef *huart);

// Handles the data when the dma interrupt triggers
void dr16_dma_handler(UART_HandleTypeDef *huart);

// Handles any triggered idle interrupts
void dr16_idle_handler(UART_HandleTypeDef *huart);

#endif // _DR16_H_
