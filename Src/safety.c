/*
 *
 * safety.c
 *
 *
 * This file defines all safety functions for the MCB.
 */

#include "can.h"
#include "drive.h"
#include "gimbal.h"
#include "safety.h"

const int16_t safety_drive_can1_max[DRIVE_NUM_MOTORS] = {10000, 10000, 10000, 10000};
const int16_t safety_drive_can1_min[DRIVE_NUM_MOTORS] = {-10000, -10000, -10000, -10000};

const int16_t safety_gimbal_can1_max[GIMBAL_NUM_MOTORS] = {1000, 1000};
const int16_t safety_gimbal_can1_min[GIMBAL_NUM_MOTORS] = {-1000, -1000};

static void safety_clamp_drive(CAN_HandleTypeDef *hcan) {
  const drive_motor_info_t *motor;
  if (hcan == &hcan1) {
    for (uint8_t i = 0; i < DRIVE_NUM_MOTORS; i++) {
      motor = drive_get_motor_info(DRIVE_MOTOR_CAN1_201 + i);
      if (motor->motor_output > safety_drive_can1_max[i]) {
        drive_set_motor_output(motor->id, safety_drive_can1_max[i]);
      } else if (motor->motor_output < safety_drive_can1_min[i]) {
        drive_set_motor_output(motor->id, safety_drive_can1_min[i]);
      }
    }
  }
}

static void safety_clamp_gimbal(CAN_HandleTypeDef *hcan) {
  const gimbal_motor_info_t *motor;
  if (hcan == &hcan1) {
    for (uint8_t i = 0; i < GIMBAL_NUM_MOTORS; i++) {
      motor = gimbal_get_motor_info(GIMBAL_MOTOR_CAN1_205 + i);
      if (motor->motor_output > safety_gimbal_can1_max[i]) {
        gimbal_set_motor_output(motor->id, safety_gimbal_can1_max[i]);
      } else if (motor->motor_output < safety_gimbal_can1_min[i]) {
        gimbal_set_motor_output(motor->id, safety_gimbal_can1_min[i]);
      }
    }
  }
}

void safety_clamp_outputs() {
  safety_clamp_drive(&hcan1);
  safety_clamp_drive(&hcan2);
  safety_clamp_gimbal(&hcan1);
  safety_clamp_gimbal(&hcan2);
}
