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
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

	/* USER CODE BEGIN Includes */

#include <stdio.h>
#include "string.h"

	/* USER CODE END Includes */

	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart2;
	extern UART_HandleTypeDef huart3;

	/* USER CODE BEGIN Private defines */

#define USART_RX_LEN 200 /* 最大接收字节数 200 */

	extern uint8_t rx_buff; // 接收数据缓存

	extern uint8_t usart_rx1_buf[USART_RX_LEN]; // 串口1接收缓存
	extern uint8_t usart_rx1_sta;				// 接收标志位

	/* USER CODE END Private defines */

	void MX_USART1_UART_Init(void);
	void MX_USART2_UART_Init(void);
	void MX_USART3_UART_Init(void);

	/* USER CODE BEGIN Prototypes */

	/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
