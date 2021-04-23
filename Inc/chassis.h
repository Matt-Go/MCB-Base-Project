/*
 *
 *
 *
 *chassis.h
 *
 * This is the header file for chassis.c
 */

#ifndef _CHASSIS_H_
#define _CHASSIS_H_

#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include "drive.h"


typedef struct {
  drive_motor_t id;
  const drive_motor_info_t *vals;
  arm_pid_instance_f32 pid;
  int16_t setpoint;
} chassis_motor_t;

void chassis_task(void);
void chassis_init(void);
void chassis_const_init(chassis_motor_t motor);

#endif //CHASSIS_H_
