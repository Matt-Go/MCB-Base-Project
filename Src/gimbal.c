/*
 * gimbal.c
 *
 * This code is responsible for the definition and handling of the pitch
 * and yaw motors used in the turret gimbal. A total of two of these
 * RM6623 motors can be used on a single can bus at once.
 */

#include "can.h"
#include "gimbal.h"
#include "string.h"
#include "remote.h"

// Stores information about all the gimbal motors on bus can1
// Ordered: 0x205 (YAW), 0x206 (PITCH)
gimbal_motor_info_t gimbal_can1_motors[GIMBAL_NUM_MOTORS];

// Provides access to read the motor sensor information
const gimbal_motor_info_t *gimbal_get_motor_info(gimbal_motor_t motor) {
  switch(motor) {
    case GIMBAL_MOTOR_CAN1_205: return &gimbal_can1_motors[0];
    case GIMBAL_MOTOR_CAN1_206: return &gimbal_can1_motors[1];
    case GIMBAL_MOTOR_CAN2_205: return NULL;
    case GIMBAL_MOTOR_CAN2_206: return NULL;
  }
  return NULL;
}

// Provides access to write the motor output information 
void gimbal_set_motor_output(gimbal_motor_t motor, int16_t output) {
  switch(motor) {
    case GIMBAL_MOTOR_CAN1_205: gimbal_can1_motors[0].motor_output = output; break;
    case GIMBAL_MOTOR_CAN1_206: gimbal_can1_motors[1].motor_output = output; break;
    case GIMBAL_MOTOR_CAN2_205:
    case GIMBAL_MOTOR_CAN2_206: break;
  }
}

static uint8_t gimbal_can_tx(CAN_HandleTypeDef *hcan, int16_t gimbal_values[GIMBAL_NUM_MOTORS]) {
  uint8_t data[8];
  for (int i = 0; i < GIMBAL_NUM_MOTORS; i++) {
    int16_t val = gimbal_values[i];
    data[2*i] = (val >> 8);
    data[(2*i) + 1] = (val & 0x00FF);
  }
  
  // Set the control command mode byte
  data[6] = 0x00;
  
  return can_tx_message(hcan, GIMBAL_CAN_TX_ID, data);
}

// This function initializes the gimbal motor data structures
void gimbal_init() {
  memset(gimbal_can1_motors, 0, sizeof(gimbal_motor_info_t) * GIMBAL_NUM_MOTORS);
  for (uint8_t i = 0; i < GIMBAL_NUM_MOTORS; i++) {
    gimbal_can1_motors[i].id = GIMBAL_MOTOR_CAN1_205 + i;
  }
}

/*
 * This function is called in the timer motor task. It sends the current motor
 * values to the gimbal motors on the given can bus.
 */
void gimbal_handle_motors(CAN_HandleTypeDef *hcan) {
  if (hcan == &hcan1) {
    int16_t gimbal_values[GIMBAL_NUM_MOTORS];
    for (int i = 0; i < GIMBAL_NUM_MOTORS; i++) {
      gimbal_values[i] = gimbal_can1_motors[i].motor_output;
    }
    gimbal_can_tx(hcan, gimbal_values);
  }
}

/*
 * This function is called when a can message is received from the gimbal motors.
 * It updates the gimbal motor information structs on the given can bus.
 */
void gimbal_can_rx_handler(CAN_HandleTypeDef *hcan) {
  if (hcan == &hcan1) {
    uint8_t i = hcan->pRxMsg->StdId - GIMBAL_CAN_YAW; // Index of the motor
    gimbal_can1_motors[i].enc = (hcan->pRxMsg->Data[0] << 8) | (hcan->pRxMsg->Data[1]);
    gimbal_can1_motors[i].torque_actual = (hcan->pRxMsg->Data[2] << 8) | (hcan->pRxMsg->Data[3]);
    gimbal_can1_motors[i].torque_desired = (hcan->pRxMsg->Data[4] << 8) | (hcan->pRxMsg->Data[5]);
    gimbal_can1_motors[i].update_counter++;
  }
}
