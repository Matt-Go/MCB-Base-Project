/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file imu.h
 *  @version 1.0
 *  @date Apr 2017
 *
 *  @brief Configuration MPU6500 and Read the Accelerator
 *         and Gyrometer data using SPI interface
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 * imu.h
 *
 * This file is responsible for declaring all code specific to controlling the
 * imu built into the MCB.
 * This is comprised of an MPU6500 and an IST8310. The MPU6500 is connected
 * with the MCB over SPI5, and the IST8310 is connected to the MPU6500 as a
 * slave through I2C.
 */

#ifndef _IMU_H_
#define _IMU_H_

#include "main.h"
#include "stm32f4xx_hal.h"

#define IMU_SPI_HANDLE      hspi5
#define IMU_CSS_PIN         SPI5_NSS_Pin
#define IMU_CSS_GPIO_GROUP  SPI5_NSS_GPIO_Port

#define IMU_START_DELAY_MS  100 // Max time until register read/write is online
#define IMU_SPI_TIMEOUT     55  // Timeout for SPI communication
#define IMU_SPI_DELAY_MS    2   // Time to wait between SPI writes
#define IMU_IST_DELAY_MS    10  // Time to wait between IST writes

#define IMU_READ_LEN 20

typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t mx;
    int16_t my;
    int16_t mz;

    int16_t temp;

    int16_t gx;
    int16_t gy;
    int16_t gz;
    
    int16_t ax_offset;
    int16_t ay_offset;
    int16_t az_offset;
  
    int16_t gx_offset;
    int16_t gy_offset;
    int16_t gz_offset;
    
} mpu_data_t;

typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t mx;
    int16_t my;
    int16_t mz;

    float temp;
    float temp_ref;
  
    float wx;
    float wy;
    float wz;

    float vx;
    float vy;
    float vz;
  
    float rol;
    float pit;
    float yaw;
    
    volatile uint32_t update_counter;
} imu_data_t;

// Public API:
const mpu_data_t *imu_get_mpu(void);
const imu_data_t *imu_get_imu(void);

// Initialization functions
void imu_init(void);

// Interrupt handlers
void imu_initiate_read(void);
void imu_spi_rx_handler(void);

void imu_enable_it(void);
void imu_disable_it(void);

// Polling mode functions
uint8_t mpu_write_reg(uint8_t const reg, uint8_t const data);
uint8_t mpu_read_reg(uint8_t const reg);
void imu_register_dump(void);
void    mpu_get_data(void);
void    mpu_offset_cal(void);

#endif // _IMU_H_
