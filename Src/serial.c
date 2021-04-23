/*
 * serial.c
 *
 * This file contains convenience functions for using usart2 as a blocking serial IO port.
 */

#include "usart.h"

#include "stm32f4xx_hal.h"
#include "command.h"
#include "serial.h"
#include "string.h"
#include "led.h"

#define TIMEOUT 100
#define RC_STRING_LEN 200
#define MAX_RX_LEN 100
#define DMA_BYTES 2

char rx_buf[MAX_RX_LEN];
uint8_t rx_buf_size = 0;

volatile serial_mode_t serial_mode = SERIAL_TX;
serial_mode_t next_mode = SERIAL_TX;

// This function is called to begin reading data
static void serial_read_init() {
  // Clear current buffer
  rx_buf_size = 0;
  // Enable interrupts
  __HAL_UART_ENABLE_IT(&SERIAL_HUART, UART_IT_RXNE);
}

// This function is called to stop reading data
static void serial_read_deinit() {
  // Clear current buffer
  rx_buf_size = 0;
  // Enable interrupts
  __HAL_UART_DISABLE_IT(&SERIAL_HUART, UART_IT_RXNE);
}

void serial_set_mode(serial_mode_t m) {
  if ((serial_mode == SERIAL_TX || serial_mode == SERIAL_IT_BUSY) &&
      m == SERIAL_RX) {
    serial_mode = SERIAL_RX;
    // Start reading bytes
    serial_read_init();
  } else if (serial_mode == SERIAL_RX && m == SERIAL_TX) {
    // Stop reading bytes
    serial_read_deinit();
    serial_mode = SERIAL_TX;
  } else if (serial_mode == SERIAL_IT_BUSY && m == SERIAL_TX) {
    serial_mode = m;
  }
}

serial_mode_t serial_get_mode() {
  return serial_mode;
}

void serial_update_mode() {
  serial_set_mode(next_mode);
}

int serial_print_buf(char *buf, uint32_t len) {
  // Sends a message only if something isn't currently being sent.
  if (serial_mode == SERIAL_TX) {
    serial_mode = SERIAL_IT_BUSY;
    HAL_UART_Transmit_IT(&SERIAL_HUART, (uint8_t *) buf, len);
    return 0;
  }
  return -1;
}

int serial_print(char *buf, serial_mode_t next) {
  if (serial_mode == SERIAL_RX ||
      (serial_mode == SERIAL_IT_BUSY && next_mode == SERIAL_RX)) {
    // We are in RX mode (or are going to be) so error
    return -1;
  }
  // We are either in TX mode or busy mode
  while (serial_mode == SERIAL_IT_BUSY) {
    // Spin, blocking until we are back in TX mode
  }
  next_mode = next;
  return serial_print_buf(buf, strlen(buf));
}

void serial_wait_ready() {
  while (serial_mode == SERIAL_IT_BUSY);
}

int serial_print_remote_info_t(const remote_info_t *r) {
  char msg[RC_STRING_LEN];
  
  sprintf(msg, "remote_rc: ch0:%d, ch1:%d, ch2:%d, ch3:%d, s1:%d, s2:%d\nremote_mouse: x:%d, y:%d z:%d l:%s r:%s v:%u\nremote_counter: %d\n",
      r->rc.ch0, r->rc.ch1, r->rc.ch2, r->rc.ch3, r->rc.s1, r->rc.s2,
      r->mouse.x, r->mouse.y, r->mouse.z, r->mouse.press_l ? "on" : "off", r->mouse.press_r ? "on" : "off",
      r->key.v, r->update_counter);
  serial_print(msg, SERIAL_TX);
  serial_wait_ready();
  return 1;
}

void serial_rxne_handler(UART_HandleTypeDef *huart) {
  led_red_on(); // Signifies we have started to read in bytes.
  // Get current byte and store it in rx_buf
  rx_buf[rx_buf_size] = huart->Instance->DR;
  rx_buf_size++;
  if (rx_buf_size >= MAX_RX_LEN || rx_buf[rx_buf_size - 1] == '\n') {
    rx_buf[rx_buf_size - 1] = '\0';
    led_red_off(); // Signifies we have stopped reading in bytes.
    serial_set_mode(SERIAL_TX);
  }
}

void serial_do_command() {
  command_do(rx_buf);
}
