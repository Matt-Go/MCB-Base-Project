/*
 * switch.c
 *
 * This file implements functions to read from switches connected to GPIO pins.
 */

#include "main.h"
#include "gpio.h"
#include "switch.h"
#include "led.h"

GPIO_PinState switch_read(switch_read_t pin) {
  switch (pin) {
    case SWITCH_ONBOARD_KEY: return HAL_GPIO_ReadPin(ONBOARD_KEY_GPIO_Port, ONBOARD_KEY_Pin);
    case SWITCH_P9_19: return HAL_GPIO_ReadPin(P9_19_GPIO_Port, P9_19_Pin);
    case SWITCH_P9_18: return HAL_GPIO_ReadPin(P9_18_GPIO_Port, P9_18_Pin);
    case SWITCH_P9_17: return HAL_GPIO_ReadPin(P9_17_GPIO_Port, P9_17_Pin);
    case SWITCH_P9_16: return HAL_GPIO_ReadPin(P9_16_GPIO_Port, P9_16_Pin);
    case SWITCH_P9_9: return HAL_GPIO_ReadPin(P9_9_GPIO_Port, P9_9_Pin);
    case SWITCH_P9_8: return HAL_GPIO_ReadPin(P9_8_GPIO_Port, P9_8_Pin);
    case SWITCH_P9_7: return HAL_GPIO_ReadPin(P9_7_GPIO_Port, P9_7_Pin);
    case SWITCH_P9_6: return HAL_GPIO_ReadPin(P9_6_GPIO_Port, P9_6_Pin);
  }
  return GPIO_PIN_RESET;
}

void switch_write(switch_write_t pin, GPIO_PinState state) {
  GPIO_TypeDef *group;
  uint16_t pin_number;
  switch (pin) {
    case SWITCH_P11_1: group = P11_1_GPIO_Port; pin_number = P11_1_Pin; break;
    case SWITCH_P11_2: group = P11_2_GPIO_Port; pin_number = P11_2_Pin; break;
    case SWITCH_P11_3: group = P11_3_GPIO_Port; pin_number = P11_3_Pin; break;
    case SWITCH_P11_4: group = P11_4_GPIO_Port; pin_number = P11_4_Pin; break;
    case SWITCH_P11_5: group = P11_5_GPIO_Port; pin_number = P11_5_Pin; break;
    case SWITCH_P11_6: group = P11_6_GPIO_Port; pin_number = P11_6_Pin; break;
    case SWITCH_P11_7: group = P11_7_GPIO_Port; pin_number = P11_7_Pin; break;
    case SWITCH_P11_8: group = P11_8_GPIO_Port; pin_number = P11_8_Pin; break;
    default: return;
  }
  HAL_GPIO_WritePin(group, pin_number, state);
}

void switch_toggle(switch_write_t pin) {
  GPIO_TypeDef *group;
  uint16_t pin_number;
  switch (pin) {
    case SWITCH_P11_1: group = P11_1_GPIO_Port; pin_number = P11_1_Pin; break;
    case SWITCH_P11_2: group = P11_2_GPIO_Port; pin_number = P11_2_Pin; break;
    case SWITCH_P11_3: group = P11_3_GPIO_Port; pin_number = P11_3_Pin; break;
    case SWITCH_P11_4: group = P11_4_GPIO_Port; pin_number = P11_4_Pin; break;
    case SWITCH_P11_5: group = P11_5_GPIO_Port; pin_number = P11_5_Pin; break;
    case SWITCH_P11_6: group = P11_6_GPIO_Port; pin_number = P11_6_Pin; break;
    case SWITCH_P11_7: group = P11_7_GPIO_Port; pin_number = P11_7_Pin; break;
    case SWITCH_P11_8: group = P11_8_GPIO_Port; pin_number = P11_8_Pin; break;
    default: return;
  }
  HAL_GPIO_TogglePin(group, pin_number);
}

void switch_test() {  
  if (switch_read(SWITCH_ONBOARD_KEY)) {
    led_green_on();
  } else {
    led_green_off();
  }
}
