/* USER CODE BEGIN 0 */

#include "main.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "task.h"
#include "oled.h"
#include "atk-mw8266.h"
#include "atk_idm750.h"
#include "pwr.h"
#include <string.h>



uint16_t time_us = 0;    //微秒
uint16_t time_ms = 0;    //毫秒

uint8_t open_flag = 0;  //开锁标志
uint8_t close_flag = 0; //关锁标志

uint8_t car_flag = 0;   //停车标志

uint8_t mode = 0;
uint16_t detection = 0;
uint8_t detection_flag = 0;

void SystemClock_Config(void);


/* USER CODE END 0 */


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    MX_TIM3_Init();
    HAL_TIM_Base_Start_IT(&htim3);

    MX_USART1_UART_Init();
    HAL_UART_Receive_IT(&huart1, (uint8_t *)UART1_temp, REC_LENGTH);
    printf("USART1 Init");

    MX_USART3_UART_Init();
    HAL_UART_Receive_IT(&huart3, &UART3_data, 1);
    HAL_UART_Transmit(&huart3, "USART3 Init", 11, HAL_MAX_DELAY); 

    MX_I2C1_Init();
    OLED_Init();
    OLED_ShowString_fun("OLED_OK!");
    
    // Pwr_Init();
    
    
    mode = READ_KEY;
    
    if(mode == 0)
    {
        OLED_ShowString_fun("4G_Mode");
        IMD750_TASK();
    }
    
    else if(mode == 1)
    {
        OLED_ShowString_fun("Wifi_Mode");
        ESP8266_TASK();
    }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief 串口中断回调函数
  * @param 调用回调函数的串口
  * @note  串口每次收到数据以后都会关闭中断，如需重复使用，必须再次开启
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 判断是哪个串口触发的中断 */
    if(huart->Instance == USART1)
    {
        if ((UART1_Rx_cnt & 0x8000) == 0)       /* 接收未完成 */
        {
            if (UART1_Rx_cnt & 0x4000)      /* 接收到了0x0d（即回车键） */
            {
                if (UART1_temp[0] != 0x0a)      /* 接收到的不是0x0a（即不是换行键） */
                {
                    UART1_Rx_cnt = 0;       /* 接收错误,重新开始 */
                }
                else        /* 接收到的是0x0a（即换行键） */
                {
                    UART1_Rx_cnt |= 0x8000;     /* 接收完成了 */
                }
            }
            else        /* 还没收到0X0d（即回车键） */
            {
                if (UART1_temp[0] == 0x0d)
                    UART1_Rx_cnt |= 0x4000;
                else
                {
                    UART1_Rx_Buf[UART1_Rx_cnt & 0X3FFF] = UART1_temp[0];
                    UART1_Rx_cnt++;

                    if (UART1_Rx_cnt > (MAX_REC_LENGTH - 1))
                    {
                        UART1_Rx_cnt = 0;       /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }

        //等待下一次接收中断
        HAL_UART_Receive_IT(&huart1, (uint8_t *)UART1_temp, REC_LENGTH);
    }

    if(huart->Instance == USART3)
    {
        if(UART3_Rx_cnt < UART3_Rx_COUNT-1) /* 判断UART接收缓冲是否溢出,留出一位给结束符'\0' */
        {
            UART3_Rx_Buf[UART3_Rx_cnt] = UART3_data;    /* 将接收到的数据写入缓冲 */
            UART3_Rx_cnt++;     /* 更新接收到的数据长度 */
        }
        else
        {
            UART3_Rx_cnt = 0;
            UART3_Rx_Buf[UART3_Rx_cnt] = UART3_data;
            UART3_Rx_cnt++;
        }

        // 启动下一次接收
        HAL_UART_Receive_IT(&huart3, &UART3_data, 1);
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
