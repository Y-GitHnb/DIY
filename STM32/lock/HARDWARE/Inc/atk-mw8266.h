#ifndef __ATK_MW8266_H
#define __ATK_MW8266_H


#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>



/* IO���� */
#define ATK_MW8266D_RST(x)      do{ x ?                                                                                     \
                                    HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                    HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                }while(0)


/* ������� */
#define ATK_MW8266D_EOK         0   /* û�д��� */
#define ATK_MW8266D_ERROR       1   /* ͨ�ô��� */
#define ATK_MW8266D_ETIMEOUT    2   /* ��ʱ���� */
#define ATK_MW8266D_EINVAL      3   /* �������� */


/* �������� */
void atk_mw8266d_reset(void);                                            /* ATK-MW8266DӲ����λ */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ATK-MW8266D����ATָ�� */
                                            
uint8_t atk_mw8266d_at_test(void);                                          /* ATK-MW8266D ATָ����� */
uint8_t atk_mw8266d_set_mode(uint8_t mode);                                 /* ����ATK-MW8266D����ģʽ */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port); /* ATK-MW8266D����TCP������ */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd);                    /* ATK-MW8266D����ԭ���Ʒ����� */
uint8_t atk_mw8266d_disconnect_atkcld(void);                                /* ATK-MW8266D�Ͽ�ԭ���Ʒ��������� */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd);                         /* ATK-MW8266D����WIFI */
uint8_t atk_mw8266d_enter_unvarnished(void);                                /* ATK-MW8266D����͸�� */
void atk_mw8266d_exit_unvarnished(void);                                    /* ATK-MW8266D�˳�͸�� */
uint8_t atk_mw8266d_get_ip(char *buf);                                      /* ATK-MW8266D��ȡIP��ַ */
uint8_t atk_mw8266d_ate_config(uint8_t cfg);                                /* ATK-MW8266D���û���ģʽ */
uint8_t atk_mw8266d_restore(void);                                          /* ATK-MW8266D�ָ��������� */
uint8_t atk_mw8266d_sw_reset(void);                                         /* ATK-MW8266D�����λ */

void ATK_MW8266D_Init(void);        /* ATK-MW8266D��ʼ�� */

#endif
