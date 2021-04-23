/*
 * drive.c
 *
 * This file is repsonsible for controlling drive motors (RM3510).
 * This file is abstracted for the most basic drive motor interaction,
 * providing data structures for each drive motor being used in the system
 * on can1 and can2.
 * It defines the callback functions that read new encoder data and update
 * the motor info structures.
 * It also defines the transmit method functions that send CAN messages.
 * Finally, it defines part of the Timer callback that will read the current motor transmit
 * values (calculated in the main loop with PID algorithm) and sends the CAN
 * messages.
 */

#include "stm32f4xx_hal.h"
#include "can.h"
#include "drive.h"
#include "remote.h"
#include "string.h"
#include "led.h"

// Stores information about all the drive motors on bus can1
// Ordered 0x201, 0x202, 0x203, 0x204
drive_motor_info_t drive_can1_motors[DRIVE_NUM_MOTORS];
drive_motor_info_t drive_can2_motors[DRIVE_NUM_MOTORS];

// Use this function to access motor feedback.
const drive_motor_info_t * drive_get_motor_info(drive_motor_t motor) {
  switch (motor) {
    case DRIVE_MOTOR_CAN1_201: return &drive_can1_motors[0];
    case DRIVE_MOTOR_CAN1_202: return &drive_can1_motors[1];
    case DRIVE_MOTOR_CAN1_203: return &drive_can1_motors[2];
    case DRIVE_MOTOR_CAN1_204: return &drive_can1_motors[3];
    case DRIVE_MOTOR_CAN2_201: return &drive_can2_motors[0];
    case DRIVE_MOTOR_CAN2_202: return &drive_can2_motors[1];
    case DRIVE_MOTOR_CAN2_203: return &drive_can2_motors[2];
    case DRIVE_MOTOR_CAN2_204: return &drive_can2_motors[3];
  }
  return NULL;
}

// Use this function to set motor output values
void drive_set_motor_output(drive_motor_t motor, int16_t output) {
  switch (motor) {
    case DRIVE_MOTOR_CAN1_201: drive_can1_motors[0].motor_output = output; break;
    case DRIVE_MOTOR_CAN1_202: drive_can1_motors[1].motor_output = output; break;
    case DRIVE_MOTOR_CAN1_203: drive_can1_motors[2].motor_output = output; break;
    case DRIVE_MOTOR_CAN1_204: drive_can1_motors[3].motor_output = output; break;
    case DRIVE_MOTOR_CAN2_201: drive_can2_motors[0].motor_output = output; break;
    case DRIVE_MOTOR_CAN2_202: drive_can2_motors[1].motor_output = output; break;
    case DRIVE_MOTOR_CAN2_203: drive_can2_motors[2].motor_output = output; break;
    case DRIVE_MOTOR_CAN2_204: drive_can2_motors[3].motor_output = output; break;
  }
}

void drive_init() {
  memset(drive_can1_motors, 0, sizeof(drive_motor_info_t) * DRIVE_NUM_MOTORS);
  memset(drive_can2_motors, 0, sizeof(drive_motor_info_t) * DRIVE_NUM_MOTORS);
  for (uint8_t i = 0; i < DRIVE_NUM_MOTORS; i++) {
    drive_can1_motors[i].id = DRIVE_MOTOR_CAN1_201 + i;
    drive_can2_motors[i].id = DRIVE_MOTOR_CAN2_201 + i;
  }
}

/*
 * Sends a CAN message to the given can bus to control the 4 drive motors
 * with the given drive values. drive_values must be an array of 4 values.
 */
uint8_t drive_can_tx(CAN_HandleTypeDef *hcan, int16_t drive_values[DRIVE_NUM_MOTORS]) {
  uint8_t data[8];
  for (int i = 0; i < DRIVE_NUM_MOTORS; i++) {
    int16_t val = drive_values[i];
    data[2*i] = (val >> 8);
    data[(2*i) + 1] = (val & 0x00FF);
  }
  
  return can_tx_message(hcan, DRIVE_CAN_TX_ID, data);
}

// This function sends a new can message based on the current values in
// the drive motors array datastructure on the given can bus. This function
// is called in the designated timer task for motors (TIM6).
void drive_handle_motors(CAN_HandleTypeDef *hcan) {
  if (hcan == &hcan1) {
    int16_t drive_values[DRIVE_NUM_MOTORS];
    for (int i = 0; i < DRIVE_NUM_MOTORS; i++) {
      drive_values[i] = drive_can1_motors[i].motor_output;
    }
    drive_can_tx(hcan, drive_values);
  } else if (hcan == &hcan2) {
    int16_t drive_values[DRIVE_NUM_MOTORS];
    for (int i = 0; i < DRIVE_NUM_MOTORS; i++) {
      drive_values[i] = drive_can2_motors[i].motor_output;
    }
    drive_can_tx(hcan, drive_values);
  }
}

/*
 * This function is called to handle received messages concerning the drive
 * motors. This function is called in the CAN callback function
 */
void drive_can_rx_handler(CAN_HandleTypeDef *hcan) {
  if (hcan == &hcan1) {
    uint8_t i = hcan->pRxMsg->StdId - DRIVE_CAN_ID1; // The index of the motor
    drive_can1_motors[i].update_counter++;
    drive_can1_motors[i].enc = (hcan->pRxMsg->Data[0] << 8) | (hcan->pRxMsg->Data[1]);
    drive_can1_motors[i].rpm = (hcan->pRxMsg->Data[2] << 8) | (hcan->pRxMsg->Data[3]);
  } else if (hcan == &hcan2) {
    uint8_t i = hcan->pRxMsg->StdId - DRIVE_CAN_ID1; // The index of the motor
    drive_can2_motors[i].update_counter++;
    drive_can2_motors[i].enc = (hcan->pRxMsg->Data[0] << 8) | (hcan->pRxMsg->Data[1]);
    drive_can2_motors[i].rpm = (hcan->pRxMsg->Data[2] << 8) | (hcan->pRxMsg->Data[3]);
  }
}
