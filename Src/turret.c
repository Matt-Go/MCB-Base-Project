/* 
 *
 *
 *turret.c
 *
 * 
 * This is where we process turret data to get motor outputs
 */

#include "main.h"
#include "turret.h"
#include "imu.h"
#include "arm_math.h"

#define PID_KP_PITCH 0.75f
#define PID_KI_PITCH 0.0f
#define PID_KD_PITCH 0.0f

#define PID_KP_YAW 0.0f
#define PID_KI_YAW 0.0f
#define PID_KD_YAW 0.0f

// measured against the imu accel in ay
#define SETPOINT -800

// Two motors that are defined for one turret
turret_motor_t pitch_motor;
turret_motor_t yaw_motor;

// This function initiates all of the values in the pitch and yaw motors that are needed
void turret_init(){
  pitch_motor.pid.Kp = PID_KP_PITCH;
  pitch_motor.pid.Ki = PID_KI_PITCH;
  pitch_motor.pid.Kd = PID_KD_PITCH;
  pitch_motor.id = GIMBAL_MOTOR_CAN1_206;
  pitch_motor.vals = gimbal_get_motor_info(GIMBAL_MOTOR_CAN1_206);
  arm_pid_init_f32(&(pitch_motor.pid),  1);

  yaw_motor.pid.Kp = PID_KP_YAW;
  yaw_motor.pid.Ki = PID_KI_YAW;
  yaw_motor.pid.Kd = PID_KD_YAW;
  yaw_motor.id = GIMBAL_MOTOR_CAN1_205;
  yaw_motor.vals = gimbal_get_motor_info(GIMBAL_MOTOR_CAN1_205);
  arm_pid_init_f32(&(yaw_motor.pid),  1);
}

// Used for debugging/reading pid values
const turret_motor_t *turret_get_motor_info(gimbal_motor_t motor) {
  switch(motor) {
    case GIMBAL_MOTOR_CAN1_205: return &yaw_motor;
    case GIMBAL_MOTOR_CAN1_206: return &pitch_motor;
    case GIMBAL_MOTOR_CAN2_205: return NULL;
    case GIMBAL_MOTOR_CAN2_206: return NULL;
  }
  return NULL;
}

// This function will use the pid arm function to give outputs to
// the turret motors
void turret_task(){
  //This allows me to get the imu value that I want, in this case, ay
  const imu_data_t *imu = imu_get_imu();

  // This is going to be using the ay value
  pitch_motor.setpoint = SETPOINT;
  
  // This is going to be the error given to the PID
  float32_t pid_error = pitch_motor.setpoint - imu->ay;
  
  // get back a motor value
  float32_t turret_result = arm_pid_f32(&pitch_motor.pid, pid_error);
  
  // send values to the motors
  gimbal_set_motor_output(pitch_motor.id, turret_result);
  gimbal_set_motor_output(yaw_motor.id, 0);
}
