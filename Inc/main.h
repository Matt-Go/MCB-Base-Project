/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define IST_SET_Pin GPIO_PIN_2
#define IST_SET_GPIO_Port GPIOE
#define MPU_INT_Pin GPIO_PIN_1
#define MPU_INT_GPIO_Port GPIOE
#define MPU_INT_EXTI_IRQn EXTI1_IRQn
#define P7_3_Pin GPIO_PIN_6
#define P7_3_GPIO_Port GPIOD
#define P11_7_Pin GPIO_PIN_7
#define P11_7_GPIO_Port GPIOI
#define P11_6_Pin GPIO_PIN_6
#define P11_6_GPIO_Port GPIOI
#define P11_5_Pin GPIO_PIN_5
#define P11_5_GPIO_Port GPIOI
#define P7_4_Pin GPIO_PIN_5
#define P7_4_GPIO_Port GPIOD
#define P11_8_Pin GPIO_PIN_2
#define P11_8_GPIO_Port GPIOI
#define P9_9_Pin GPIO_PIN_9
#define P9_9_GPIO_Port GPIOI
#define P2_1_Pin GPIO_PIN_9
#define P2_1_GPIO_Port GPIOA
#define P1_1_Pin GPIO_PIN_8
#define P1_1_GPIO_Port GPIOA
#define SPI5_NSS_Pin GPIO_PIN_6
#define SPI5_NSS_GPIO_Port GPIOF
#define P9_19_Pin GPIO_PIN_10
#define P9_19_GPIO_Port GPIOF
#define P9_6_Pin GPIO_PIN_0
#define P9_6_GPIO_Port GPIOC
#define P9_7_Pin GPIO_PIN_1
#define P9_7_GPIO_Port GPIOC
#define P11_2_Pin GPIO_PIN_1
#define P11_2_GPIO_Port GPIOA
#define P11_1_Pin GPIO_PIN_0
#define P11_1_GPIO_Port GPIOA
#define P9_8_Pin GPIO_PIN_4
#define P9_8_GPIO_Port GPIOA
#define P9_16_Pin GPIO_PIN_4
#define P9_16_GPIO_Port GPIOC
#define P3_1_Pin GPIO_PIN_13
#define P3_1_GPIO_Port GPIOE
#define ONBOARD_KEY_Pin GPIO_PIN_10
#define ONBOARD_KEY_GPIO_Port GPIOD
#define P11_3_Pin GPIO_PIN_2
#define P11_3_GPIO_Port GPIOA
#define P9_18_Pin GPIO_PIN_5
#define P9_18_GPIO_Port GPIOA
#define P9_17_Pin GPIO_PIN_5
#define P9_17_GPIO_Port GPIOC
#define P4_1_Pin GPIO_PIN_14
#define P4_1_GPIO_Port GPIOE
#define P11_4_Pin GPIO_PIN_3
#define P11_4_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_14
#define LED_GREEN_GPIO_Port GPIOF
#define LED_RED_Pin GPIO_PIN_7
#define LED_RED_GPIO_Port GPIOE

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define ARM_MATH_CM4
/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
