/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#define OPEN_TIME   5  //开锁时间
#define CLOSE_TIME  5  //关锁时间

#define WIFI_ID         "H3C_58D6A5"//"vivo X80"         //WIFI名称
#define WIFI_PASSWORD   "Hwang13522595103"//"YQY1122334455"    //WIFI密码

#define WIFI_SERVER_ID        "39135820043068758276"    //原子云设备编号
#define WIFI_SERVER_PASSWORD  "12345678"                //原子云设备密码

#define DEMO_DTU_TEST_DATA                      "ALIENTEK ATK-IDM750C TEST" //服务器数据格式
#define DEMO_DTU_TCP_SERVER_DOMAIN_NAME         "cloud.alientek.com"    //第一路连接默认参数
#define DEMO_DTU_TCP_SERVER_PORT_NUMBER         "59666"                 //第一路连接默认参数
#define DEMO_DTU_TCP_YUANZI_DEVICE_NUMEBER      "97633500194055990311"  //原子云设备编号
#define DEMO_DTU_TCP_YUANZI_DEVICE_PASSWORD     "12345678"              //原子云设备密码


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

extern uint16_t time_us;
extern uint16_t time_ms;

extern uint8_t open_flag;
extern uint8_t close_flag;

extern uint8_t car_flag;

extern uint8_t mode;
extern uint16_t detection;
extern uint8_t detection_flag;



#define LED_GPIO_Port   GPIOC
#define LED_Pin         GPIO_PIN_13

#define RELAY_OPEN_GPIO_Port    GPIOB
#define RELAY_OPEN_Pin          GPIO_PIN_1

#define RELAY_CLOSE_GPIO_Port   GPIOB
#define RELAY_CLOSE_Pin         GPIO_PIN_0

#define ATK_MW8266D_RST_GPIO_Port   GPIOA
#define ATK_MW8266D_RST_Pin    GPIO_PIN_5

#define KEY_GPIO_Port    GPIOB
#define KEY_Pin          GPIO_PIN_14

#define KEY1_GPIO_Port   GPIOA
#define KEY1_Pin         GPIO_PIN_7

#define KEY2_GPIO_Port   GPIOA
#define KEY2_Pin         GPIO_PIN_6

#define HW_GPIO_Port    GPIOB
#define HW_Pin          GPIO_PIN_13

#define MOT_GPIO_Port   GPIOB
#define MOT_Pin         GPIO_PIN_12
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define printf_usart3(str)  (HAL_UART_Transmit(&huart3, str, strlen(str), 1000))

#define READ_KEY     (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) ? 1 : 0)
#define READ_KEY1    (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) ? 1 : 0)
#define READ_KEY2    (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) ? 1 : 0)

#define READ_HW    (HAL_GPIO_ReadPin(HW_GPIO_Port, HW_Pin) ? 0 : 1)

#define READ_MOT    (HAL_GPIO_ReadPin(MOT_GPIO_Port, MOT_Pin) ? 0 : 1)


#define LED(a)  (a ? HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET))
#define LED_TOGGLE()   do{ HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); }while(0)

#define RELAY_OPEN(a)   (a ? HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_SET))

#define RELAY_CLOSE(a)  (a ? HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_SET))


#define delay_ms(x)     HAL_Delay(x)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
