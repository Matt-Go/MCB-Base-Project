/*
 * pwm.h
 *
 * This function declares functions and types for PWM generation.
 */

#ifndef _PWM_H_
#define _PWM_H_

// Defines pwm capable pins.
// Corresponds to the pad and number as written on the MCB schematic sheet.
typedef enum pwm_pin_enum {
  PWM_P10_1 = 1,
  PWM_P10_2,
  PWM_P10_3,
  PWM_P10_4,
  PWM_P10_5,
  PWM_P10_6,
  PWM_P10_7,
  PWM_P10_8,
  PWM_P1_1,
  PWM_P2_1,
  PWM_P3_1,
  PWM_P4_1,  
} pwm_pin_t;

// Writes a pwm signal to the given pin. Duty cycle is out of 255 max.
void pwm_write(pwm_pin_t pin, uint8_t duty);

// Tests the pwm system on each pin.
void pwm_test(void);

#endif // _PWM_H_
