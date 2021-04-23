/*
 * gimbal.h
 *
 * This code is responsible for the declaration of motor information and
 * handler functions of the pitch and yaw motors used in the turret gimbal.
 */

#ifndef _GIMBAL_H_
#define _GIMBAL_H_

#include "remote.h"
#include "can.h"

#define GIMBAL_CAN_TX_ID 0x1FF

// TODO: Relabel pitch and yaw
#define GIMBAL_CAN_YAW   0x205
#define GIMBAL_CAN_PITCH   0x206

#define GIMBAL_NUM_MOTORS 2

typedef enum gimbal_motor_enum {
  GIMBAL_MOTOR_CAN1_205 = 1,
  GIMBAL_MOTOR_CAN1_206,
  GIMBAL_MOTOR_CAN2_205,
  GIMBAL_MOTOR_CAN2_206,
} gimbal_motor_t;

typedef struct {
  // The motor's id
  gimbal_motor_t id;
  // motor output
  int16_t motor_output;

  // motor feedback values
  uint16_t enc;
  int16_t torque_actual;
  int16_t torque_desired;
  
  volatile uint32_t update_counter;
} gimbal_motor_info_t;

// Public API:
const gimbal_motor_info_t *gimbal_get_motor_info(gimbal_motor_t motor);
void gimbal_set_motor_output(gimbal_motor_t motor, int16_t output);

// Initializers and backend functions:
void gimbal_init(void);
void gimbal_handle_motors(CAN_HandleTypeDef *hcan);
void gimbal_can_rx_handler(CAN_HandleTypeDef *hcan);

#endif // _GIMBAL_H_
