#include "run.h"


/**
 * @brief       ����0���ܣ����ܲ���
 * @param       is_atkcld: 0��δ����ԭ����
 *                         1��������ԭ����
 * @retval      ��
 */
static void demo_key0_fun(uint8_t is_atkcld)
{
    uint8_t ret;
    
    if (is_atkcld == 0)
    {
        /* ����ATָ����� */
        ret = atk_mw8266d_at_test();
        if (ret == 0)
        {
            printf("AT test success!\r\n");
        }
        else
        {
            printf("AT test failed!\r\n");
        }
    }
    else
    {
        /* ������Ϣ��ԭ���Ʒ����� */
        atk_mw8266d_uart_printf("This ATK-MW8266D ALIENTEK Cloud Test.\r\n");
    }
}


/**
 * @brief       ����1���ܣ��л�ԭ��������״̬
 * @param       is_atkcld: 0��δ����ԭ����
 *                         1��������ԭ����
 * @retval      ��
 */
static void demo_key1_fun(uint8_t *is_atkcld)
{
    uint8_t ret;
    
    if (*is_atkcld == 0)
    {
        /* ����ԭ���� */
        ret = atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);
        if (ret == 0)
        {
            *is_atkcld = 1;
            printf("Connect to ALIENTEK cloud!\r\n");
        }
        else
        {
            printf("Error to connect ALIENTEK cloud!\r\n");
        }
    }
    else
    {
        /* �Ͽ�ԭ�������� */
        atk_mw8266d_disconnect_atkcld();
        *is_atkcld = 0;
        printf("Disconnect to ALIENTEK cloud!\r\n");
    }
}


/**
 * @brief       ����ԭ���ƺ󣬽�������ԭ���Ƶ����ݷ��͵����ڵ�������
 * @param       is_atkcld: 0��δ����ԭ����
 *                         1��������ԭ����
 * @retval      ��
 */
static void demo_upload_data(uint8_t is_atkcld)
{
    uint8_t *buf;
    
    if (is_atkcld == 1)
    {
        /* ��������ATK-MW8266D UART��һ֡���� */
        buf = atk_mw8266d_uart_rx_get_frame();
        if (buf != NULL)
        {
            printf("%s", buf);
            /* �ؿ���ʼ��������ATK-MW8266D UART������ */
            atk_mw8266d_uart_rx_restart();
        }
    }
}


/**
 * @brief       ������ʾ��ں���
 * @param       ��
 * @retval      ��
 */
void demo_run(void)
{
    uint8_t flag;       //���ر�־
    
//    flag  = atk_mw8266d_restore();                        /* �ָ��������� */
//    flag += atk_mw8266d_at_test();                        /* AT���� */
    flag = atk_mw8266d_set_mode(1);                         /* Stationģʽ */
    flag += atk_mw8266d_sw_reset();                         /* �����λ */
    flag += atk_mw8266d_ate_config(0);                      /* �رջ��Թ��� */
    flag += atk_mw8266d_join_ap(MY_WIFI, MY_WIFI_PASSWORD); /* ����WIFI */
    flag += atk_mw8266d_get_ip(ip_buf);                     /* ��ȡIP��ַ */
   
    
    atk_mw8266d_close();    /* ���־λ */
    
    while (1)
    {
            /* ���ܲ��� */
            demo_key0_fun(is_atkcld);
            
            /* �л�ԭ��������״̬ */
            demo_key1_fun(&is_atkcld);
        
        /* ���ͽ�����ԭ���Ƶ����ݵ����ڵ������� */
        demo_upload_data(is_atkcld);
        
        delay_ms(10);
    }
}
