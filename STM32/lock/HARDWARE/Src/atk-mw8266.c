#include "atk-mw8266.h"


/**
 * @brief       ATK-MW8266DӲ����λ
 * @param       ��
 * @retval      ��
 */
void atk_mw8266d_reset(void)
{
    HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_Port, ATK_MW8266D_RST_Pin, GPIO_PIN_RESET);
    delay_ms(100);
    HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_Port, ATK_MW8266D_RST_Pin, GPIO_PIN_SET);
    delay_ms(500);
}


/**
 * @brief       ATK-MW8266D����ATָ��
 * @param       cmd    : �����͵�ATָ��
 *              ack    : �ȴ�����Ӧ
 *              timeout: �ȴ���ʱʱ��
 * @retval      0: ����ִ�гɹ�
 *              2: �ȴ�����Ӧ��ʱ������ִ��ʧ��
 */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    usart3_close_flag();
    usart3_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        while (timeout > 0)
        {
            ret = usart3_uart_dat();
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
                    return ATK_MW8266D_EOK;
                }
                else
                {
                    usart3_close_flag();
                }
            }
            timeout--;
            delay_ms(1);
        }
        
        return ATK_MW8266D_ETIMEOUT;
    }
}


/**
 * @brief       ATK-MW8266D ATָ�����
 * @param       ��
 * @retval      0: ATָ����Գɹ�
 *              1: ATָ�����ʧ��
 *      ��AT����OK
 */
uint8_t atk_mw8266d_at_test(void)
{
    uint8_t ret;
    uint8_t i;
    
    for (i=0; i<10; i++)
    {
        ret = atk_mw8266d_send_at_cmd("AT", "OK", 500);
        if (ret == ATK_MW8266D_EOK)
        {
            return ATK_MW8266D_EOK;
        }
    }
    
    return ATK_MW8266D_ERROR;
}


/**
 * @brief       ����ATK-MW8266D����ģʽ
 * @param       mode: 1��Stationģʽ
 *                    2��APģʽ
 *                    3��AP+Stationģʽ
 * @retval      0: ����ģʽ���óɹ�
 *              1: ����ģʽ����ʧ��
 *              3: mode�������󣬹���ģʽ����ʧ��
 *      ��AT+CWMODE=1����OK
 */
uint8_t atk_mw8266d_set_mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=1", "OK", 500);    /* Stationģʽ */
            break;
        }
        case 2:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=2", "OK", 500);    /* APģʽ */
            break;
        }
        case 3:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=3", "OK", 500);    /* AP+Stationģʽ */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D����TCP������
 * @param       server_ip  : TCP������IP��ַ
 *              server_port: TCP�������˿ں�
 * @retval      0: ����TCP�������ɹ�
 *              1: ����TCP������ʧ��
 *      ��AT+CIPSTART="TCP","%s",%s����CONNECT
 */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", server_ip, server_port);
    ret = atk_mw8266d_send_at_cmd(cmd, "CONNECT", 5000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D����ԭ���Ʒ�����
 * @param       id : ԭ�����豸���
 *              pwd: ԭ�����豸����
 * @retval      0: ����ԭ���Ʒ������ɹ�
 *              1: ����ԭ���Ʒ�����ʧ��
 *      ��AT+ATKCLDSTA="39135820043068758276","12345678"����CLOUD CONNECTED
 */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+ATKCLDSTA=\"%s\",\"%s\"", id, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "CLOUD CONNECTED", 10000);
    
    printf("%d" ,ret);
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D�Ͽ�ԭ���Ʒ���������
 * @param       ��
 * @retval      0: �Ͽ�ԭ���Ʒ��������ӳɹ�
 *              1: �Ͽ�ԭ���Ʒ���������ʧ��
 *      ��AT+ATKCLDCLS����CLOUD DISCONNECT
 */
uint8_t atk_mw8266d_disconnect_atkcld(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+ATKCLDCLS", "CLOUD DISCONNECT", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D����WIFI
 * @param       ssid: WIFI����
 *              pwd : WIFI����
 * @retval      0: WIFI���ӳɹ�
 *              1: WIFI����ʧ��
 *      ��AT+CWJAP="vivo X80","YQY1122334455"����WIFI GOT IP
 */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "WIFI GOT IP", 10000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D����͸��
 * @param       ��
 * @retval      0: ����͸���ɹ�
 *              1: ����͸��ʧ��
 *      ��AT+CIPMODE=1����OK
 *      ��AT+CIPSEND����>
 */
uint8_t atk_mw8266d_enter_unvarnished(void)
{
    uint8_t ret;
    
    ret  = atk_mw8266d_send_at_cmd("AT+CIPMODE=1", "OK", 500);
    ret += atk_mw8266d_send_at_cmd("AT+CIPSEND", ">", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D�˳�͸��
 * @param       ��
 * @retval      ��
 *      ��+++
 */
void atk_mw8266d_exit_unvarnished(void)
{
    usart3_printf("+++");
}


/**
 * @brief       ATK-MW8266D��ȡIP��ַ
 * @param       buf: IP��ַ����Ҫ16�ֽ��ڴ�ռ�
 * @retval      0: ��ȡIP��ַ�ɹ�
 *              1: ��ȡIP��ַʧ��
 *      ��AT+CIFSR����OK
 */
uint8_t atk_mw8266d_get_ip(char *buf)
{
    uint8_t ret;
    char *p_start;
    char *p_end;
    
    ret = atk_mw8266d_send_at_cmd("AT+CIFSR", "OK", 500);
    if (ret != ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_ERROR;
    }
    
    p_start = strstr((const char *)usart3_uart_dat(), "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);
    
    return ATK_MW8266D_EOK;
}


/**
 * @brief       ATK-MW8266D���û���ģʽ
 * @param       cfg: 0���رջ���
 *                   1���򿪻���
 * @retval      0: ���û���ģʽ�ɹ�
 *              1: ���û���ģʽʧ��
 *      ��ATE1����OK
 */
uint8_t atk_mw8266d_ate_config(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = atk_mw8266d_send_at_cmd("ATE0", "OK", 500);   /* �رջ��� */
            break;
        }
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("ATE1", "OK", 500);   /* �򿪻��� */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D�ָ���������
 * @param       ��
 * @retval      0: �ָ��������óɹ�
 *              1: �ָ���������ʧ��
 *      ��AT+RESTORE����ready
 */
uint8_t atk_mw8266d_restore(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RESTORE", "ready", 3000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D�����λ
 * @param       ��
 * @retval      0: �����λ�ɹ�
 *              1: �����λʧ��
 *      ��AT+RST����OK
 */
uint8_t atk_mw8266d_sw_reset(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RST", "OK", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


/**
 * @brief       ATK-MW8266D��ʼ��
 * @retval      0: ATK-MW8266D��ʼ���ɹ�������ִ�гɹ�
 *              1: ATK-MW8266D��ʼ��ʧ�ܣ�����ִ��ʧ��
 */
void ATK_MW8266D_Init(void)
{
    uint8_t flag;       //���ر�־
    char ip_buf[16];    //ip��ַ
    
    
wifi_init:
    atk_mw8266d_reset();            /* ATK-MW8266DӲ����λ */
    flag = atk_mw8266d_at_test();   /* ATK-MW8266D ATָ����� */
    if (flag != ATK_MW8266D_EOK)      // �д�
    {
        OLED_ShowString_fun("8266 Init ERROR");
        printf("ATK-MW8266 Init ERROR\r\n");
        goto wifi_init;
    }
    OLED_ShowString_fun("8266 Init OK");
    printf("ATK-MW8266 Init OK\r\n");
    
    
//    flag  = atk_mw8266d_restore();    /* �ָ��������� */
//    flag += atk_mw8266d_at_test();    /* AT���� */
    flag = atk_mw8266d_set_mode(1);     /* Stationģʽ */
    flag += atk_mw8266d_sw_reset();     /* �����λ */
    flag += atk_mw8266d_ate_config(0);  /* �رջ��Թ��� */
    flag += atk_mw8266d_join_ap(WIFI_ID, WIFI_PASSWORD);  /* ����WIFI */
    flag += atk_mw8266d_get_ip(ip_buf); /* ��ȡIP��ַ */
    if (flag != 0)      // �д�
    {
        OLED_ShowString_fun("8266 Wifi ERROR");
        printf("ATK-MW8266 Wifi ERROR\r\n");
        goto wifi_init;
    }
    OLED_ShowString_fun("8266 Wifi OK");
    printf("ATK-MW8266 Wifi OK\r\n");
    
    
    flag = atk_mw8266d_connect_atkcld(WIFI_SERVER_ID, WIFI_SERVER_PASSWORD);    /* ����ԭ���� */
    if (flag != 0)
    {
        OLED_ShowString_fun("8266 Link ERROR");
        printf("ATK-MW8266 Link ERROR\r\n");
        goto wifi_init;
    }
    OLED_ShowString_fun("8266 Link OK");
    printf("ATK-MW8266 Link OK\r\n");
    
    usart3_close_flag();    /* ���־λ */
}
