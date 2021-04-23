/*
 *
 *
 *chassis.c
 *
 * This controls the motors and uses the pid algorithm
 */

#include "main.h" 
#include "chassis.h"
#include "arm_math.h"
#include "dr16.h"

#define PID_KP_DRIVE 0.0f
#define PID_KI_DRIVE 0.0f
#define PID_KD_DRIVE 0.0f

chassis_motor_t drive_201;
chassis_motor_t drive_202;
chassis_motor_t drive_203;
chassis_motor_t drive_204;

void chassis_task() {
  const remote_info_t *remote = dr16_get_remote();
  const drive_motor_info_t *can2_motor = drive_get_motor_info(DRIVE_MOTOR_CAN2_201);
  drive_set_motor_output(can2_motor->id, remote->rc.ch1 * 20);
}

void chassis_init() {
  drive_201.id = DRIVE_MOTOR_CAN1_201;
  drive_202.id = DRIVE_MOTOR_CAN1_202;
  drive_203.id = DRIVE_MOTOR_CAN1_203;
  drive_204.id = DRIVE_MOTOR_CAN1_204;  
  chassis_const_init(drive_201);
  chassis_const_init(drive_202);
  chassis_const_init(drive_203);
  chassis_const_init(drive_204);
  drive_201.vals = drive_get_motor_info(drive_201.id);
  drive_202.vals = drive_get_motor_info(drive_202.id);
  drive_203.vals = drive_get_motor_info(drive_203.id);
  drive_204.vals = drive_get_motor_info(drive_204.id); 
  arm_pid_init_f32(&(drive_201.pid),  1);
  arm_pid_init_f32(&(drive_202.pid),  1);
  arm_pid_init_f32(&(drive_203.pid),  1);
  arm_pid_init_f32(&(drive_204.pid),  1);
 
}

void chassis_const_init(chassis_motor_t motor) {
  motor.pid.Kp = PID_KP_DRIVE;
  motor.pid.Ki = PID_KI_DRIVE;
  motor.pid.Kd = PID_KD_DRIVE;
}
