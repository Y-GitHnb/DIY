/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "oled.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;


/* USER CODE BEGIN Private defines */
#define MAX_REC_LENGTH  200
#define REC_LENGTH      1

#define UART3_Rx_COUNT  1024
#define UART3_Tx_COUNT  512


extern uint8_t UART1_Rx_Buf[MAX_REC_LENGTH];
extern uint16_t UART1_Rx_cnt;
extern uint8_t UART1_temp[REC_LENGTH];
extern uint8_t UART1_Rx_flg;

extern uint8_t UART3_Rx_Buf[UART3_Rx_COUNT];
extern uint8_t UART3_data;
extern uint16_t UART3_Rx_cnt;
extern uint8_t UART3_Rx_flg;
extern uint8_t UART3_Tx_Buf[UART3_Tx_COUNT];


/* USER CODE END Private defines */
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void USART_CLOSE(void);     // 清数据

void usart3_printf(char *fmt, ...); //发送数据
void usart3_close_flag(void);   //清标志位
uint8_t *usart3_uart_dat(void); //接收到一帧数据
uint16_t usart3_uart_dat_len(void); //接收到的一帧数据的长度
/* USER CODE END Prototypes */


#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
