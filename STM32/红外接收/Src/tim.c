/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

uint8_t g_remote_sta = 0;
uint32_t g_remote_data = 0;
uint8_t g_remote_cnt = 0;

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_IC_InitTypeDef sConfigIC = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 72 - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 10000 - 1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 8;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

	/* USER CODE END TIM2_Init 2 */
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspInit 0 */

		/* USER CODE END TIM2_MspInit 0 */
		/* TIM2 clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM2 GPIO Configuration
		PA0-WKUP     ------> TIM2_CH1
		*/
		GPIO_InitStruct.Pin = TIME2_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TIME2_GPIO_Port, &GPIO_InitStruct);

		/* TIM2 interrupt Init */
		HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
		/* USER CODE BEGIN TIM2_MspInit 1 */

		/* USER CODE END TIM2_MspInit 1 */
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspDeInit 0 */

		/* USER CODE END TIM2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM2_CLK_DISABLE();

		/**TIM2 GPIO Configuration
		PA0-WKUP     ------> TIM2_CH1
		*/
		HAL_GPIO_DeInit(TIME2_GPIO_Port, TIME2_Pin);

		/* TIM2 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
		/* USER CODE BEGIN TIM2_MspDeInit 1 */

		/* USER CODE END TIM2_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		if (g_remote_sta & 0x80)
		{
			g_remote_sta &= ~0X10;

			if ((g_remote_sta & 0X0F) == 0X00)
			{
				g_remote_sta |= 1 << 6;
			}

			if ((g_remote_sta & 0X0F) < 14)
			{
				g_remote_sta++;
			}
			else
			{
				g_remote_sta &= ~(1 << 7);
				g_remote_sta &= 0XF0;
			}
		}
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		uint16_t dval;

		if (HAL_GPIO_ReadPin(TIME2_GPIO_Port, TIME2_Pin))
		{
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			g_remote_sta |= 0X10;
		}
		else
		{
			dval = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);

			if (g_remote_sta & 0X10)
			{
				if (g_remote_sta & 0X80)
				{

					if (dval > 300 && dval < 800)
					{
						g_remote_data >>= 1;
						g_remote_data &= ~(0x80000000);
					}
					else if (dval > 1400 && dval < 1800)
					{
						g_remote_data >>= 1;
						g_remote_data |= 0x80000000;
					}
					else if (dval > 2000 && dval < 3000)
					{
						g_remote_cnt++;
						g_remote_sta &= 0XF0;
					}
				}
				else if (dval > 4200 && dval < 4700)
				{
					g_remote_sta |= 1 << 7;
					g_remote_cnt = 0;
				}
			}

			g_remote_sta &= ~(1 << 4);
		}
	}
}

uint8_t remote_scan(void)
{
	uint8_t sta = 0;
	uint8_t t1, t2;

	if (g_remote_sta & 0x40)
	{
		t1 = g_remote_data;
		t2 = (g_remote_data >> 8) & 0xff;

		if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID)
		{
			t1 = (g_remote_data >> 16) & 0xff;
			t2 = (g_remote_data >> 24) & 0xff;

			if (t1 == (uint8_t)~t2)
			{
				sta = t1;
			}
		}

		if ((sta == 0) || ((g_remote_sta & 0X80) == 0))
		{
			g_remote_sta &= ~(1 << 6);
			g_remote_cnt = 0;
		}
	}

	return sta;
}

/* USER CODE END 1 */
