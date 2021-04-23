/*
 * pwm.c
 *
 * This file provides functions to start and stop pwm generation on
 * various pins on the MCB.
 */

#include "tim.h"
#include "pwm.h"

void pwm_write(pwm_pin_t pin, uint8_t duty) {
  TIM_HandleTypeDef *htim;
  uint32_t channel;
  TIM_OC_InitTypeDef sConfigOC;

  switch (pin) {
    case PWM_P10_1: htim = &htim4; channel = TIM_CHANNEL_1; break;
    case PWM_P10_2: htim = &htim4; channel = TIM_CHANNEL_2; break;
    case PWM_P10_3: htim = &htim4; channel = TIM_CHANNEL_3; break;
    case PWM_P10_4: htim = &htim4; channel = TIM_CHANNEL_4; break;
    case PWM_P10_5: htim = &htim5; channel = TIM_CHANNEL_1; break;
    case PWM_P10_6: htim = &htim5; channel = TIM_CHANNEL_2; break;
    case PWM_P10_7: htim = &htim5; channel = TIM_CHANNEL_3; break;
    case PWM_P10_8: htim = &htim5; channel = TIM_CHANNEL_4; break;
    case PWM_P1_1: htim = &htim1; channel = TIM_CHANNEL_1; break;
    case PWM_P2_1: htim = &htim1; channel = TIM_CHANNEL_2; break;
    case PWM_P3_1: htim = &htim1; channel = TIM_CHANNEL_3; break;
    case PWM_P4_1: htim = &htim1; channel = TIM_CHANNEL_4; break;
    default: return;
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = duty;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel);
  if (duty != 0) {
    HAL_TIM_PWM_Start(htim, channel);
  } else {
    HAL_TIM_PWM_Stop(htim, channel);
  }
}

void pwm_test() {
  pwm_write(PWM_P10_1, 0);
  pwm_write(PWM_P10_2, 32);
  pwm_write(PWM_P10_3, 64);
  pwm_write(PWM_P10_4, 96);
  pwm_write(PWM_P10_5, 128);
  pwm_write(PWM_P10_6, 160);
  pwm_write(PWM_P10_7, 192);
  pwm_write(PWM_P10_8, 224);
}
