#ifndef __PWR_H
#define __PWR_H


#include "main.h"



#define PWR_RX_GPIO_PORT              GPIOB
#define PWR_RX_GPIO_PIN               GPIO_PIN_11
#define PWR_RX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */
  
#define PWR_RX_INT_IRQn               EXTI15_10_IRQn
#define PWR_RX_INT_IRQHandler         EXTI15_10_IRQHandler


void Pwr_Init(void);    /* ���Ѱ�����ʼ�� */
void Pwr_Stop(void);       /* ����ֹͣģʽ */


#endif
