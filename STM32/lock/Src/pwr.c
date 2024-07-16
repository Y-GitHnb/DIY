#include "pwr.h"



/**
 * @brief       低功耗模式下的按键初始化(用于唤醒睡眠模式/停止模式)
 * @param       无
 * @retval      无
 */
void Pwr_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    PWR_RX_GPIO_CLK_ENABLE();                           /* 时钟使能 */

    gpio_init_struct.Pin = PWR_RX_GPIO_PIN;             /* 引脚 */
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;        /* 中断,上升沿 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;              /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
    HAL_GPIO_Init(PWR_RX_GPIO_PORT, &gpio_init_struct); /* WKUP引脚初始化 */

    HAL_NVIC_SetPriority(PWR_RX_INT_IRQn, 2, 2);        /* 抢占优先级2，子优先级2 */
    HAL_NVIC_EnableIRQ(PWR_RX_INT_IRQn);
}



/**
 * @brief       外部中断服务程序
 * @param       无
 * @retval      无
 */
void PWR_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PWR_RX_GPIO_PIN);
}



/**
 * @brief       进入CPU睡眠模式
 * @param       无
 * @retval      无
 */
void Pwr_Sleep(void)
{
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); /* 执行WFI指令, 进入待机模式 */
}



/**
 * @brief       外部中断回调函数
 * @param       GPIO_Pin:中断线引脚
 * @note        此函数会被PWR_WKUP_INT_IRQHandler()调用
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == PWR_RX_GPIO_PIN)
    {
        /* HAL_GPIO_EXTI_IRQHandler()函数已经为我们清除了中断标志位，所以我们进了回调函数可以不做任何事 */
    }
}



/**
 * @brief       进入停止模式
 * @param       无
 * @retval      无
 */
void Pwr_Stop(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();     /* 使能电源时钟 */
    
    /* 进入停止模式，设置稳压器为低功耗模式，等待中断唤醒 */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}
