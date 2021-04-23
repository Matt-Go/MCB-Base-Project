/*
 * serial.h
 *
 * This file contains convenience function declarations for using usart2 as a blocking serial IO port.
 */

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "remote.h"
#include "stm32f4xx_hal.h"

#include "stdint.h"

#define SERIAL_HUART huart2

typedef enum {
  SERIAL_TX = 0,
  SERIAL_RX = 1,
  SERIAL_IT_BUSY,
} serial_mode_t;

// Sets the mode that serial is in
void serial_set_mode(serial_mode_t m);

// Returns the current mode of serial
serial_mode_t serial_get_mode(void);

// Called to set the mode to serial's next mode
void serial_update_mode(void);

// Print a buffer of characters.
// Returns 0 on success, -1 on failure.
int serial_print_buf(char *buf, uint32_t len);

// Print a c-style string (null terminated)
// next_mode is the mode to change into upon completion (RX or TX)
// Returns 0 on success, -1 on failure.
int serial_print(char *buf, serial_mode_t next);

// Waits until the serial port is ready
void serial_wait_ready(void);

// Print an remote_info_t
// Returns 0 on success, -1 on failure.
int serial_print_remote_info_t(const remote_info_t *remote);

// Handles receiving data from usart
void serial_rxne_handler(UART_HandleTypeDef *huart);

// Returns 1 if a serial command has been read, 0 otherwise
uint8_t serial_read_command(void);

// Runs the read command
void serial_do_command(void);

#endif // _SERIAL_H_
