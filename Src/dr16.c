/*
 * dr16.c
 *
 * This file contains code for interfacing with the DR16 receiver to read
 * the controller data.
 */

#include "dr16.h"
#include "remote.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"

uint8_t dr16_rx_buf[DR16_MAX_LEN];
remote_info_t dr16_remote;

// Returns a reference to the remote control
const remote_info_t *dr16_get_remote() {
  return &dr16_remote;
}

static void dr16_process_buf(uint8_t start) {
  remote_parse_buf(dr16_rx_buf + start, &dr16_remote);
  dr16_remote.update_counter++;
}

void dr16_dma_init(UART_HandleTypeDef *huart) {
  if (huart->RxState != HAL_UART_STATE_READY) {
    // Something is wrong, so hang
    while (1) {
    }
  }

  // Enable IDLE interrupt
  __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

  // Configure huart to point to dr16_rx_buf and have correct size
  huart->pRxBuffPtr = dr16_rx_buf;
  huart->RxXferSize = DR16_MAX_LEN;

  huart->ErrorCode  = HAL_UART_ERROR_NONE;

  // Enable DMA to read in MAX_LEN bytes
  HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR,
                  (uint32_t) dr16_rx_buf, DR16_MAX_LEN);
  
  SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);
}

void dr16_dma_handler(UART_HandleTypeDef *huart) {
  // Doesn't need to do anything, since we expect to process buffer on idle trigger
}

void dr16_idle_handler(UART_HandleTypeDef *huart) {
  // Clear Idle flag
  __HAL_UART_CLEAR_IDLEFLAG(huart);
  // Check which huart this is
  if (huart == &huart1) {
    // Disable DMA stream temporarily
    __HAL_DMA_DISABLE(huart->hdmarx);
    // Check how many bytes left to be read by the DMA stream
    uint16_t num_data_to_read = __HAL_DMA_GET_COUNTER(huart->hdmarx);
    if ((DR16_MAX_LEN - DR16_PACKET_LEN) == num_data_to_read) {
      // Read exactly DR16_PACKET_LEN bytes
      dr16_process_buf(0);
    }
    // Reset DMA stream count
    __HAL_DMA_SET_COUNTER(huart->hdmarx, DR16_MAX_LEN);
    // Enable DMA stream
    __HAL_DMA_ENABLE(huart->hdmarx);
  }
}
