/*
 * main_task.c
 *
 * This file contains all code necessary for the robot control. It is executed
 * repeatedly every 5 milliseconds using the timer peripheral.
 *
 */

#include "main.h"

#include "dr16.h"
#include "drive.h"
#include "gimbal.h"
#include "imu.h"
#include "led.h"
#include "pwm.h"
#include "remote.h"
#include "switch.h"
#include "turret.h"
#include "chassis.h"

// This is the main task for our application
void main_task() {
  // sensor data references
  chassis_task();
}
