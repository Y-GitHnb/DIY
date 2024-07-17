/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

// while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) != SET);   /* �ȴ����ͽ��� */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"


/* USER CODE BEGIN 0 */
#if 1

#pragma import(__use_no_semihosting)

//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;
};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}

//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((USART1->SR & 0X40) == 0); //ѭ������,ֱ���������
    USART1->DR = (uint8_t) ch;
    return ch;
}
#endif


// USART1
uint8_t UART1_Rx_Buf[MAX_REC_LENGTH] = {0}; //USART1�洢��������
uint16_t UART1_Rx_cnt = 0;                  //USART1�������ݼ�����
uint8_t UART1_temp[REC_LENGTH] = {0};       //USART1�������ݻ���
uint8_t UART1_Rx_flg = 0;                   //USART3������ɱ�־

// UART3
uint8_t UART3_Rx_Buf[UART3_Rx_COUNT] = {0}; //USART3�洢��������
uint8_t UART3_data = 0;       //USART3�������ݻ���
uint16_t UART3_Rx_cnt = 0;                  //USART3�������ݼ�����
uint8_t UART3_Rx_flg = 0;                   //USART3������ɱ�־

uint8_t UART3_Tx_Buf[UART3_Tx_COUNT] = {0}; //USART3���ͻ���


/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;


/* USART1 init function */

void MX_USART1_UART_Init(void)
{
    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */
    
    /* USER CODE END USART1_Init 2 */
}



/* USART3 init function */

void MX_USART3_UART_Init(void)
{
    /* USER CODE BEGIN USART3_Init 0 */

    /* USER CODE END USART3_Init 0 */

    /* USER CODE BEGIN USART3_Init 1 */

    /* USER CODE END USART3_Init 1 */
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART3_Init 2 */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);//�����ж�ʹ��
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);//�����ж�ʹ��
    /* USER CODE END USART3_Init 2 */
}



void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(uartHandle->Instance==USART1)
    {
        /* USER CODE BEGIN USART1_MspInit 0 */

        /* USER CODE END USART1_MspInit 0 */
        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 2, 2);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        /* USER CODE BEGIN USART1_MspInit 1 */

        /* USER CODE END USART1_MspInit 1 */
    }
    else if(uartHandle->Instance==USART3)
    {
        /* USER CODE BEGIN USART3_MspInit 0 */

        /* USER CODE END USART3_MspInit 0 */
        /* USART3 clock enable */
        __HAL_RCC_USART3_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**USART3 GPIO Configuration
        PB10     ------> USART3_TX
        PB11     ------> USART3_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* USART3 interrupt Init */
        HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
        
        /* USER CODE BEGIN USART3_MspInit 1 */
        
        /* USER CODE END USART3_MspInit 1 */
    }
}



void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

    if(uartHandle->Instance==USART1)
    {
        /* USER CODE BEGIN USART1_MspDeInit 0 */

        /* USER CODE END USART1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

        /* USART1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
        /* USER CODE BEGIN USART1_MspDeInit 1 */

        /* USER CODE END USART1_MspDeInit 1 */
    }
    else if(uartHandle->Instance==USART3)
    {
        /* USER CODE BEGIN USART3_MspDeInit 0 */

        /* USER CODE END USART3_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USART3_CLK_DISABLE();

        /**USART3 GPIO Configuration
        PB10     ------> USART3_TX
        PB11     ------> USART3_RX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

        /* USART3 interrupt Deinit */
        HAL_NVIC_DisableIRQ(USART3_IRQn);
        /* USER CODE BEGIN USART3_MspDeInit 1 */

        /* USER CODE END USART3_MspDeInit 1 */
    }
}


/* USER CODE BEGIN 1 */


// ������
void USART_CLOSE(void)
{
    uint8_t len;

    if (UART1_Rx_cnt & 0x8000)        /* ���յ�������? */
    {
        len = UART1_Rx_cnt & 0x3fff;  /* �õ��˴ν��յ������ݳ��� */
        printf("\r\n�����͵���ϢΪ:\r\n");

        HAL_UART_Transmit(&huart1, (uint8_t*)UART1_Rx_Buf, len, 1000);     /* ���ͽ��յ������� */
        while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) != SET);           /* �ȴ����ͽ��� */

        printf("\r\n\r\n");             /* ���뻻�� */
        UART1_Rx_cnt = 0;
    }

    if(UART3_Rx_flg)
    {
        HAL_UART_Transmit(&huart3, UART3_Rx_Buf, UART3_Rx_cnt, 0x10);    //���ͽ��յ�������
        memset(UART3_Rx_Buf, 0, sizeof(UART3_Rx_Buf));
        UART3_Rx_cnt = 0;
        UART3_Rx_flg = 0;
    }
}



/* -------------------------------------------------------------------------------------------------- */


/**
 * @brief   UART3 printf
 * @param   fmt: ����ӡ������
 * @retval  ��
 */
void usart3_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    
    va_start(ap, fmt);
    vsprintf((char *)UART3_Tx_Buf, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)UART3_Tx_Buf);
    HAL_UART_Transmit(&huart3, UART3_Tx_Buf, len, HAL_MAX_DELAY);
}


/**
 * @brief   UART3 ���־λ
 * @param   ��
 * @retval  ��
 */
void usart3_close_flag(void)
{
    UART3_Rx_cnt = 0;
    UART3_Rx_flg = 0;
}


/**
 * @brief   UART3 ���յ���һ֡����
 * @param   ��
 * @retval  NULL: δ���յ�һ֡����
 *          ����: ���յ���һ֡����
 */
uint8_t *usart3_uart_dat(void)
{
    if (UART3_Rx_flg == 1)
    {
        UART3_Rx_Buf[UART3_Rx_cnt] = '\0';
        return UART3_Rx_Buf;
    }
    else
    {
        return NULL;
    }
}


/**
 * @brief       ��ȡ UART3 ���յ���һ֡���ݵĳ���
 * @param       ��
 * @retval      0   : δ���յ�һ֡����
 *              ����: ���յ���һ֡���ݵĳ���
 */
uint16_t usart3_uart_dat_len(void)
{
    if (UART3_Rx_flg == 1)
    {
        return UART3_Rx_cnt;
    }
    else
    {
        return 0;
    }
}


/* USER CODE END 1 */
