#ifndef __PWR_H
#define __PWR_H


#include "main.h"



#define PWR_RX_GPIO_PORT              GPIOB
#define PWR_RX_GPIO_PIN               GPIO_PIN_11
#define PWR_RX_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */
  
#define PWR_RX_INT_IRQn               EXTI15_10_IRQn
#define PWR_RX_INT_IRQHandler         EXTI15_10_IRQHandler


void Pwr_Init(void);    /* 唤醒按键初始化 */
void Pwr_Stop(void);       /* 进入停止模式 */


#endif
