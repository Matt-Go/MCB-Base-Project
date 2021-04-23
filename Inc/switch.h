/*
 * switch.h
 *
 * This function declares functions and types to read from switches connected
 * to gpio pins.
 */

#ifndef _SWITCH_H_
#define _SWITCH_H_

// Switch pin names match the name given in STM32CubeMx and in main.h
typedef enum {
  SWITCH_ONBOARD_KEY = 1,
  SWITCH_P9_19,
  SWITCH_P9_18,
  SWITCH_P9_17,
  SWITCH_P9_16,
  SWITCH_P9_9,
  SWITCH_P9_8,
  SWITCH_P9_7,
  SWITCH_P9_6,
} switch_read_t;

typedef enum {
  SWITCH_P11_1 = 1,
  SWITCH_P11_2,  
  SWITCH_P11_3,  
  SWITCH_P11_4,  
  SWITCH_P11_5,  
  SWITCH_P11_6,  
  SWITCH_P11_7,  
  SWITCH_P11_8,  
} switch_write_t;

// Reads the value of the pin
GPIO_PinState switch_read(switch_read_t pin);

// Writes a value to a pin
void switch_write(switch_write_t pin, GPIO_PinState state);

// Toggles a value on a pin
void switch_toggle(switch_write_t pin);

// Tests the switch for each pin.
void switch_test(void);

#endif // _SWITCH_H_
