#include "pwr.h"



/**
 * @brief       �͹���ģʽ�µİ�����ʼ��(���ڻ���˯��ģʽ/ֹͣģʽ)
 * @param       ��
 * @retval      ��
 */
void Pwr_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    PWR_RX_GPIO_CLK_ENABLE();                           /* ʱ��ʹ�� */

    gpio_init_struct.Pin = PWR_RX_GPIO_PIN;             /* ���� */
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;        /* �ж�,������ */
    gpio_init_struct.Pull = GPIO_PULLDOWN;              /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* ���� */
    HAL_GPIO_Init(PWR_RX_GPIO_PORT, &gpio_init_struct); /* WKUP���ų�ʼ�� */

    HAL_NVIC_SetPriority(PWR_RX_INT_IRQn, 2, 2);        /* ��ռ���ȼ�2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(PWR_RX_INT_IRQn);
}



/**
 * @brief       �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void PWR_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PWR_RX_GPIO_PIN);
}



/**
 * @brief       ����CPU˯��ģʽ
 * @param       ��
 * @retval      ��
 */
void Pwr_Sleep(void)
{
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); /* ִ��WFIָ��, �������ģʽ */
}



/**
 * @brief       �ⲿ�жϻص�����
 * @param       GPIO_Pin:�ж�������
 * @note        �˺����ᱻPWR_WKUP_INT_IRQHandler()����
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == PWR_RX_GPIO_PIN)
    {
        /* HAL_GPIO_EXTI_IRQHandler()�����Ѿ�Ϊ����������жϱ�־λ���������ǽ��˻ص��������Բ����κ��� */
    }
}



/**
 * @brief       ����ֹͣģʽ
 * @param       ��
 * @retval      ��
 */
void Pwr_Stop(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();     /* ʹ�ܵ�Դʱ�� */
    
    /* ����ֹͣģʽ��������ѹ��Ϊ�͹���ģʽ���ȴ��жϻ��� */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}
