/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
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

/* Includes ------------------------------------------------------------------*/
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "drive.h"
#include "gimbal.h"
#include "led.h"

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SJW = CAN_SJW_1TQ;
  hcan1.Init.BS1 = CAN_BS1_3TQ;
  hcan1.Init.BS2 = CAN_BS2_5TQ;
  hcan1.Init.TTCM = DISABLE;
  hcan1.Init.ABOM = ENABLE;
  hcan1.Init.AWUM = DISABLE;
  hcan1.Init.NART = DISABLE;
  hcan1.Init.RFLM = DISABLE;
  hcan1.Init.TXFP = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 5;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SJW = CAN_SJW_1TQ;
  hcan2.Init.BS1 = CAN_BS1_3TQ;
  hcan2.Init.BS2 = CAN_BS2_5TQ;
  hcan2.Init.TTCM = DISABLE;
  hcan2.Init.ABOM = ENABLE;
  hcan2.Init.AWUM = DISABLE;
  hcan2.Init.NART = DISABLE;
  hcan2.Init.RFLM = DISABLE;
  hcan2.Init.TXFP = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
  
    /**CAN1 GPIO Configuration    
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
  
    /**CAN2 GPIO Configuration    
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    /* Be sure that all peripheral instances that share the same clock need to be disabled */
    /**  HAL_RCC_CAN1_CLK_ENABLED--;
    *  if(HAL_RCC_CAN1_CLK_ENABLED==0){
    *    __HAL_RCC_CAN1_CLK_DISABLE();
    **/
  
    /**CAN1 GPIO Configuration    
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX 
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    /* Be sure that all peripheral instances that share the same clock need to be disabled */
    /**  HAL_RCC_CAN1_CLK_ENABLED--;
    *  if(HAL_RCC_CAN1_CLK_ENABLED==0){
    *    __HAL_RCC_CAN1_CLK_DISABLE();
    **/
  
    /**CAN2 GPIO Configuration    
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* User Static Functions Begin */

// initializes the receive filter for the given can handle
static void can_filter_init(CAN_HandleTypeDef *hcan) {
  CAN_FilterConfTypeDef  can_filter;
  if (hcan == &hcan1 || hcan == &hcan2) {
    can_filter.FilterNumber         = 0;
    can_filter.FilterMode           = CAN_FILTERMODE_IDMASK;
    can_filter.FilterScale          = CAN_FILTERSCALE_32BIT;
    can_filter.FilterIdHigh         = 0x0000;
    can_filter.FilterIdLow          = 0x0000;
    can_filter.FilterMaskIdHigh     = 0x0000;
    can_filter.FilterMaskIdLow      = 0x0000;
    can_filter.FilterFIFOAssignment = CAN_FilterFIFO0;
    can_filter.BankNumber           = 14;
    can_filter.FilterActivation     = ENABLE;
    HAL_CAN_ConfigFilter(hcan, &can_filter);
  }
}

// initializes the transmit and receive message data structures
// for the given can handle
static void can_messages_init(CAN_HandleTypeDef *hcan) {
  static CanTxMsgTypeDef can1_tx_message;
  static CanTxMsgTypeDef can2_tx_message;
  static CanRxMsgTypeDef can1_rx_message;
  static CanRxMsgTypeDef can2_rx_message;

  if (hcan == &hcan1) {
    hcan->pTxMsg = &can1_tx_message;
    hcan->pRxMsg = &can1_rx_message;
  } else if (hcan == &hcan2) {
    hcan->pTxMsg = &can2_tx_message;
    hcan->pRxMsg = &can2_rx_message;
  }
}

static void can_receive_start(CAN_HandleTypeDef *hcan) {
  __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
}

/* User Static Functions End */

/* User Public Functions Begin */

// intializes the given can handle
void can_handle_init(CAN_HandleTypeDef *hcan) {
  can_filter_init(hcan);
  can_messages_init(hcan);
  can_receive_start(hcan);
}

// Called whenever a message is received 
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan) {
  uint32_t id;
  if (hcan->pRxMsg->IDE == CAN_ID_STD) {
    id = hcan->pRxMsg->StdId;
  } else {
    id = hcan->pRxMsg->ExtId;
  }
  if (hcan == &hcan1) {
    switch (id) {
      case DRIVE_CAN_ID1:
      case DRIVE_CAN_ID2:
      case DRIVE_CAN_ID3:
      case DRIVE_CAN_ID4:
        drive_can_rx_handler(hcan);
        break;
      case GIMBAL_CAN_YAW:
      case GIMBAL_CAN_PITCH:
        gimbal_can_rx_handler(hcan);
        break;
    }
  }
  // Re-enable receive message interrupt
  __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
}

// This function sends a message on the given can handle with id and
// data given
uint8_t can_tx_message(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t data[8]) {
  hcan->pTxMsg->StdId = id;
  hcan->pTxMsg->IDE = CAN_ID_STD;
  hcan->pTxMsg->RTR = CAN_RTR_DATA;
  hcan->pTxMsg->DLC = 8;
  
  for (int i = 0; i < 8; i++) {
    hcan->pTxMsg->Data[i] = data[i];
  }
  
  HAL_CAN_Transmit_IT(hcan);
  __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
  return 0;
}

/* User Public Functions End */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
