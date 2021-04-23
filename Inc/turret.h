/*
 *
 *
 *turret.h
 *
 * This is the h file for turret.c
 */

#ifndef _TURRET_
#define _TURRET_

#include "main.h"
#include "arm_math.h"
#include "gimbal.h"

typedef struct {
  gimbal_motor_t id;
  const gimbal_motor_info_t *vals;
  arm_pid_instance_f32 pid;
  int16_t setpoint;
} turret_motor_t;

const turret_motor_t *turret_get_motor_info(gimbal_motor_t motor);
void turret_task(void);
void turret_init(void);

#endif // _TURRET_H_
