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

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* TIM1 init function */
void MX_TIM1_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 7200 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 10000 - 1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */
}
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
/* TIM3 init function */
void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 1895 - 1;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 947;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */
	HAL_TIM_MspPostInit(&htim3);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (tim_baseHandle->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspInit 0 */

		/* USER CODE END TIM1_MspInit 0 */
		/* TIM1 clock enable */
		__HAL_RCC_TIM1_CLK_ENABLE();
		/* USER CODE BEGIN TIM1_MspInit 1 */

		/* USER CODE END TIM1_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM2)
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
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspInit 0 */

		/* USER CODE END TIM3_MspInit 0 */
		/* TIM3 clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		/* USER CODE BEGIN TIM3_MspInit 1 */

		/* USER CODE END TIM3_MspInit 1 */
	}
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (timHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspPostInit 0 */

		/* USER CODE END TIM3_MspPostInit 0 */

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM3 GPIO Configuration
		PA6     ------> TIM3_CH1
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM3_MspPostInit 1 */

		/* USER CODE END TIM3_MspPostInit 1 */
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspDeInit 0 */

		/* USER CODE END TIM1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM1_CLK_DISABLE();
		/* USER CODE BEGIN TIM1_MspDeInit 1 */

		/* USER CODE END TIM1_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM2)
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
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspDeInit 0 */

		/* USER CODE END TIM3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();
		/* USER CODE BEGIN TIM3_MspDeInit 1 */

		/* USER CODE END TIM3_MspDeInit 1 */
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

// ---------------------------------------------------- TIME1 BEGIN ----------------------------------------------------

void HAL_Delay_us(uint32_t nus)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_ENABLE(&htim1);
	while (__HAL_TIM_GET_COUNTER(&htim1) < nus)
	{
	}
	__HAL_TIM_DISABLE(&htim1);

//	HAL_TIM_Base_Start(&htim1);
//	__HAL_TIM_SetCounter(&htim1, 0); // 先把计数清零
//	while (nus > __HAL_TIM_GetCounter(&htim1))
//	{
//	}
//	HAL_TIM_Base_Stop(&htim1);
}

// ---------------------------------------------------- TIME1 END ----------------------------------------------------

// ---------------------------------------------------- TIME2 BEGIN ----------------------------------------------------

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

// ---------------------------------------------------- TIME2 END ----------------------------------------------------

// ---------------------------------------------------- TIME3 BEGIN ----------------------------------------------------

void IR_LED_SendBit(uint8_t bit)
{
	if (bit)
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 947);
		HAL_Delay_us(560);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		HAL_Delay_us(1680);
	}
	else
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 947);
		HAL_Delay_us(560);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		HAL_Delay_us(560);
	}
}

void IR_LED_SendNEC(uint8_t user, uint8_t key)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 947);
	HAL_Delay_us(9000);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	HAL_Delay_us(4500);

	uint32_t data = ((~key & 0xFF) << 24) | ((key & 0xFF) << 16) | ((~user & 0xFF) << 8) | (user & 0xFF);

	uint8_t i;
	for (i = 0; i <= 32; i++)
	{
		IR_LED_SendBit(data & 0x01);
		data >>= 1;
	}
}

// ---------------------------------------------------- TIME3 END ----------------------------------------------------

/* USER CODE END 1 */
