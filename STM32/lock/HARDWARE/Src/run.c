#include "run.h"


/**
 * @brief       按键0功能，功能测试
 * @param       is_atkcld: 0，未连接原子云
 *                         1，已连接原子云
 * @retval      无
 */
static void demo_key0_fun(uint8_t is_atkcld)
{
    uint8_t ret;
    
    if (is_atkcld == 0)
    {
        /* 进行AT指令测试 */
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
        /* 发送信息至原子云服务器 */
        atk_mw8266d_uart_printf("This ATK-MW8266D ALIENTEK Cloud Test.\r\n");
    }
}


/**
 * @brief       按键1功能，切换原子云连接状态
 * @param       is_atkcld: 0，未连接原子云
 *                         1，已连接原子云
 * @retval      无
 */
static void demo_key1_fun(uint8_t *is_atkcld)
{
    uint8_t ret;
    
    if (*is_atkcld == 0)
    {
        /* 连接原子云 */
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
        /* 断开原子云连接 */
        atk_mw8266d_disconnect_atkcld();
        *is_atkcld = 0;
        printf("Disconnect to ALIENTEK cloud!\r\n");
    }
}


/**
 * @brief       连接原子云后，将接收自原子云的数据发送到串口调试助手
 * @param       is_atkcld: 0，未连接原子云
 *                         1，已连接原子云
 * @retval      无
 */
static void demo_upload_data(uint8_t is_atkcld)
{
    uint8_t *buf;
    
    if (is_atkcld == 1)
    {
        /* 接收来自ATK-MW8266D UART的一帧数据 */
        buf = atk_mw8266d_uart_rx_get_frame();
        if (buf != NULL)
        {
            printf("%s", buf);
            /* 重开开始接收来自ATK-MW8266D UART的数据 */
            atk_mw8266d_uart_rx_restart();
        }
    }
}


/**
 * @brief       例程演示入口函数
 * @param       无
 * @retval      无
 */
void demo_run(void)
{
    uint8_t flag;       //返回标志
    
//    flag  = atk_mw8266d_restore();                        /* 恢复出厂设置 */
//    flag += atk_mw8266d_at_test();                        /* AT测试 */
    flag = atk_mw8266d_set_mode(1);                         /* Station模式 */
    flag += atk_mw8266d_sw_reset();                         /* 软件复位 */
    flag += atk_mw8266d_ate_config(0);                      /* 关闭回显功能 */
    flag += atk_mw8266d_join_ap(MY_WIFI, MY_WIFI_PASSWORD); /* 连接WIFI */
    flag += atk_mw8266d_get_ip(ip_buf);                     /* 获取IP地址 */
   
    
    atk_mw8266d_close();    /* 清标志位 */
    
    while (1)
    {
            /* 功能测试 */
            demo_key0_fun(is_atkcld);
            
            /* 切换原子云连接状态 */
            demo_key1_fun(&is_atkcld);
        
        /* 发送接收自原子云的数据到串口调试助手 */
        demo_upload_data(is_atkcld);
        
        delay_ms(10);
    }
}
