/*
 * drive.h
 *
 * This file is repsonsible for constants related to the drive motors (RM3510)
 * which are used for the Chassis control.
 */
 
#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "stm32f4xx_hal.h"
#include "remote.h"

#define DRIVE_CAN_TX_ID 0x200

#define DRIVE_CAN_ID1 0x201
#define DRIVE_CAN_ID2 0x202
#define DRIVE_CAN_ID3 0x203
#define DRIVE_CAN_ID4 0x204

#define DRIVE_NUM_MOTORS 4

typedef enum {
  DRIVE_MOTOR_CAN1_201 = 1,
  DRIVE_MOTOR_CAN1_202,
  DRIVE_MOTOR_CAN1_203,
  DRIVE_MOTOR_CAN1_204,
  DRIVE_MOTOR_CAN2_201,
  DRIVE_MOTOR_CAN2_202,
  DRIVE_MOTOR_CAN2_203,
  DRIVE_MOTOR_CAN2_204,
} drive_motor_t;
  

typedef struct {
  // The motor id
  drive_motor_t id;

  // set values
  int16_t motor_output; // the value sent to the motor esc
  
  // measured values
  uint16_t enc; // ranges between 0 and 8191
  int16_t rpm;
  
  // meta data
  volatile uint32_t update_counter;
} drive_motor_info_t;

// Public API:
const drive_motor_info_t * drive_get_motor_info(drive_motor_t motor);
void drive_set_motor_output(drive_motor_t motor, int16_t output);

// Initialization and backend functions:
void drive_init(void);
uint8_t drive_can_tx(CAN_HandleTypeDef *hcan, int16_t *drive_values);
void drive_can_rx_handler(CAN_HandleTypeDef *hcan);
void drive_handle_motors(CAN_HandleTypeDef *hcan);

#endif // _DRIVE_H_
