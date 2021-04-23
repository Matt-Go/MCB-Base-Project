/*
 * remote.c
 *
 * This file provides functions and variables related to the remote control
 * input that the user uses to drive the robot.
 */

#include "remote.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
#include "stm32f4xx_hal.h"

// The parsing code from DJI
int remote_parse_buf(uint8_t  *buf, remote_info_t *RC) {
  RC->rc.ch0 = (buf[0] | buf[1] << 8) & 0x07FF;
  RC->rc.ch0 -= 1024;
  RC->rc.ch1 = (buf[1] >> 3 | buf[2] << 5) & 0x07FF;
  RC->rc.ch1 -= 1024;
  RC->rc.ch2 = (buf[2] >> 6 | buf[3] << 2 | buf[4] << 10) & 0x07FF;
  RC->rc.ch2 -= 1024;
  RC->rc.ch3 = (buf[4] >> 1 | buf[5] << 7) & 0x07FF;
  RC->rc.ch3 -= 1024;

  RC->rc.s1 = ((buf[5] >> 4) & 0x000C) >> 2;
  RC->rc.s2 = (buf[5] >> 4) & 0x0003;

  if ((abs(RC->rc.ch0) > 660) || \
      (abs(RC->rc.ch1) > 660) || \
      (abs(RC->rc.ch2) > 660) || \
      (abs(RC->rc.ch3) > 660))
  {
    //memset(RC, 0, sizeof(remote_info_t));
    return 0;
  }

  RC->mouse.x = buf[6] | (buf[7] << 8); // x axis
  RC->mouse.y = buf[8] | (buf[9] << 8);
  RC->mouse.z = buf[10] | (buf[11] << 8);

  RC->mouse.press_l = buf[12];
  RC->mouse.press_r = buf[13];

  RC->key.v = buf[14] | buf[15] << 8; // keyboard code
  return 1;
}

void remote_to_string(char *buf, uint32_t len, const remote_info_t *RC) {
  const char *format = "rc:\n ch0:%d\n ch1:%d\n ch2:%d\n ch3:%d\n s1:%u\n s2:%u\n";
  snprintf(buf, len, format, RC->rc.ch0, RC->rc.ch1, RC->rc.ch2, RC->rc.ch3, RC->rc.s1, RC->rc.s2);
}

void remote_mouse_to_string(char *buf, uint32_t len, const remote_info_t *RC) {
  const char *format = "mouse:\n x:%d\n y:%d\n z:%d\n press_l:%u\n press_r:%u\n key:%u\n";
  snprintf(buf, len, format, RC->mouse.x, RC->mouse.y, RC->mouse.z, RC->mouse.press_l, RC->key.v);
}

void remote_uart_it_init(void) {
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

int remote_equals(remote_info_t r1, remote_info_t r2) {
  return ((r1.rc.ch0 == r2.rc.ch0) &&
      (r1.rc.ch1 == r2.rc.ch1) &&
      (r1.rc.ch2 == r2.rc.ch2) &&
      (r1.rc.ch3 == r2.rc.ch3) &&
      (r1.rc.s1 == r2.rc.s1) &&
      (r1.rc.s2 == r2.rc.s2));
}
