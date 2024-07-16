#include "atk-mw8266.h"


/**
 * @brief       ATK-MW8266D硬件复位
 * @param       无
 * @retval      无
 */
void atk_mw8266d_reset(void)
{
    HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_Port, ATK_MW8266D_RST_Pin, GPIO_PIN_RESET);
    delay_ms(100);
    HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_Port, ATK_MW8266D_RST_Pin, GPIO_PIN_SET);
    delay_ms(500);
}


/**
 * @brief       ATK-MW8266D发送AT指令
 * @param       cmd    : 待发送的AT指令
 *              ack    : 等待的响应
 *              timeout: 等待超时时间
 * @retval      0: 函数执行成功
 *              2: 等待期望应答超时，函数执行失败
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
 * @brief       ATK-MW8266D AT指令测试
 * @param       无
 * @retval      0: AT指令测试成功
 *              1: AT指令测试失败
 *      发AT，回OK
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
 * @brief       设置ATK-MW8266D工作模式
 * @param       mode: 1，Station模式
 *                    2，AP模式
 *                    3，AP+Station模式
 * @retval      0: 工作模式设置成功
 *              1: 工作模式设置失败
 *              3: mode参数错误，工作模式设置失败
 *      发AT+CWMODE=1，回OK
 */
uint8_t atk_mw8266d_set_mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=1", "OK", 500);    /* Station模式 */
            break;
        }
        case 2:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=2", "OK", 500);    /* AP模式 */
            break;
        }
        case 3:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=3", "OK", 500);    /* AP+Station模式 */
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
 * @brief       ATK-MW8266D连接TCP服务器
 * @param       server_ip  : TCP服务器IP地址
 *              server_port: TCP服务器端口号
 * @retval      0: 连接TCP服务器成功
 *              1: 连接TCP服务器失败
 *      发AT+CIPSTART="TCP","%s",%s，回CONNECT
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
 * @brief       ATK-MW8266D连接原子云服务器
 * @param       id : 原子云设备编号
 *              pwd: 原子云设备密码
 * @retval      0: 连接原子云服务器成功
 *              1: 连接原子云服务器失败
 *      发AT+ATKCLDSTA="39135820043068758276","12345678"，回CLOUD CONNECTED
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
 * @brief       ATK-MW8266D断开原子云服务器连接
 * @param       无
 * @retval      0: 断开原子云服务器连接成功
 *              1: 断开原子云服务器连接失败
 *      发AT+ATKCLDCLS，回CLOUD DISCONNECT
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
 * @brief       ATK-MW8266D连接WIFI
 * @param       ssid: WIFI名称
 *              pwd : WIFI密码
 * @retval      0: WIFI连接成功
 *              1: WIFI连接失败
 *      发AT+CWJAP="vivo X80","YQY1122334455"，回WIFI GOT IP
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
 * @brief       ATK-MW8266D进入透传
 * @param       无
 * @retval      0: 进入透传成功
 *              1: 进入透传失败
 *      发AT+CIPMODE=1，回OK
 *      发AT+CIPSEND，回>
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
 * @brief       ATK-MW8266D退出透传
 * @param       无
 * @retval      无
 *      发+++
 */
void atk_mw8266d_exit_unvarnished(void)
{
    usart3_printf("+++");
}


/**
 * @brief       ATK-MW8266D获取IP地址
 * @param       buf: IP地址，需要16字节内存空间
 * @retval      0: 获取IP地址成功
 *              1: 获取IP地址失败
 *      发AT+CIFSR，回OK
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
 * @brief       ATK-MW8266D设置回显模式
 * @param       cfg: 0，关闭回显
 *                   1，打开回显
 * @retval      0: 设置回显模式成功
 *              1: 设置回显模式失败
 *      发ATE1，回OK
 */
uint8_t atk_mw8266d_ate_config(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = atk_mw8266d_send_at_cmd("ATE0", "OK", 500);   /* 关闭回显 */
            break;
        }
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("ATE1", "OK", 500);   /* 打开回显 */
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
 * @brief       ATK-MW8266D恢复出厂设置
 * @param       无
 * @retval      0: 恢复出场设置成功
 *              1: 恢复出场设置失败
 *      发AT+RESTORE，回ready
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
 * @brief       ATK-MW8266D软件复位
 * @param       无
 * @retval      0: 软件复位成功
 *              1: 软件复位失败
 *      发AT+RST，回OK
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
 * @brief       ATK-MW8266D初始化
 * @retval      0: ATK-MW8266D初始化成功，函数执行成功
 *              1: ATK-MW8266D初始化失败，函数执行失败
 */
void ATK_MW8266D_Init(void)
{
    uint8_t flag;       //返回标志
    char ip_buf[16];    //ip地址
    
    
wifi_init:
    atk_mw8266d_reset();            /* ATK-MW8266D硬件复位 */
    flag = atk_mw8266d_at_test();   /* ATK-MW8266D AT指令测试 */
    if (flag != ATK_MW8266D_EOK)      // 有错
    {
        OLED_ShowString_fun("8266 Init ERROR");
        printf("ATK-MW8266 Init ERROR\r\n");
        goto wifi_init;
    }
    OLED_ShowString_fun("8266 Init OK");
    printf("ATK-MW8266 Init OK\r\n");
    
    
//    flag  = atk_mw8266d_restore();    /* 恢复出厂设置 */
//    flag += atk_mw8266d_at_test();    /* AT测试 */
    flag = atk_mw8266d_set_mode(1);     /* Station模式 */
    flag += atk_mw8266d_sw_reset();     /* 软件复位 */
    flag += atk_mw8266d_ate_config(0);  /* 关闭回显功能 */
    flag += atk_mw8266d_join_ap(WIFI_ID, WIFI_PASSWORD);  /* 连接WIFI */
    flag += atk_mw8266d_get_ip(ip_buf); /* 获取IP地址 */
    if (flag != 0)      // 有错
    {
        OLED_ShowString_fun("8266 Wifi ERROR");
        printf("ATK-MW8266 Wifi ERROR\r\n");
        goto wifi_init;
    }
    OLED_ShowString_fun("8266 Wifi OK");
    printf("ATK-MW8266 Wifi OK\r\n");
    
    
    flag = atk_mw8266d_connect_atkcld(WIFI_SERVER_ID, WIFI_SERVER_PASSWORD);    /* 连接原子云 */
    if (flag != 0)
    {
        OLED_ShowString_fun("8266 Link ERROR");
        printf("ATK-MW8266 Link ERROR\r\n");
        goto wifi_init;
    }
    OLED_ShowString_fun("8266 Link OK");
    printf("ATK-MW8266 Link OK\r\n");
    
    usart3_close_flag();    /* 清标志位 */
}
