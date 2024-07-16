#ifndef __ATK_IDM750_H
#define __ATK_IDM750_H


#include "main.h"
#include "usart.h"
#include "atk_idm750_cfg.h"


#define ATK_IDM750C_TIME            1000
#define ATK_IDM750C_SET_TIME        10000
#define ATK_IDM750C_DTU_URC_SIZE    5
#define DTU_RX_CMD_BUF_SIZE         (512)
#define DTU_SMS_SEND_BUF_MAX        (1024)


/* 函数错误代码 */
#define ATK_IDM750C_EOK                     0   /* DTU返回OK */
#define ATK_IDM750C_ERROR                   1   /* 错误 */
#define ATK_IDM750C_ETIMEOUT                2   /* 超时错误 */
#define ATK_IDM750C_EINVAL                  3   /* 参数错误 */
#define ATK_IDM750C_AT_TIMEOUT              4   /* 发送AT指令校验超时 */



void ATK_IMD750_Init(void);     //初始化
void atk_idm750c_dtu_get_urc_info(uint8_t ch);
int dtu_config_init(_dtu_work_mode_eu work_mode);
uint8_t atk_idm750c_send_cmd_to_dtu(char *cmd, char *ack, uint32_t timeout);    //发送AT指令
uint8_t atk_idm750c_at_test(void);    //AT指令测试
uint8_t atk_idm750c_dtu_enter_configmode(void);    //DTU进入配置状态
uint8_t atk_idm750c_restore(void);
uint8_t atk_idm750c_query_versionnumber(void);
uint8_t atk_idm750c_query_imeinumber(void);
uint8_t atk_idm750c_query_iccidnumber(void);
uint8_t atk_idm750c_query_imsinumber(void);
uint8_t atk_idm750c_query_productid(void);
uint8_t atk_idm750c_enter_transfermode(void);    //进入透传状态
uint8_t atk_idm750c_query_workmode(atk_idm750c_workmode_t mode);    //工作模式设置
uint8_t atk_idm750c_commandecho(atk_idm750c_echo_t echo);
uint8_t atk_idm750c_config_working_mode(uint8_t mode,char  *cmd);
uint8_t atk_idm750c_uart(atk_idm750c_urat_t uart);    //串口透传配置
uint8_t atk_idm750c_uart_parameter(atk_idm750c_uartmode_t mode);
uint8_t atk_idm750c_uart_pack_parameter(void);
uint8_t atk_idm750c_net(atk_idm750c_net_t net);
uint8_t atk_idm750c_cmdkey(void);
uint8_t atk_idm750c_user(void);
uint8_t atk_idm750c_rstime(void);
uint8_t atk_idm750c_link_rstime(void);
uint8_t atk_idm750c_send_english_message(void);
uint8_t atk_idm750c_link1(atk_idm750c_link1mode_t link1, char *link1_domainname, char *link1_port);    //第一路连接参数
uint8_t atk_idm750c_link2(atk_idm750c_link2mode_t link2, char *link2_domainname, char *link2_port);
uint8_t atk_idm750c_link3(atk_idm750c_link3mode_t link3, char *link3_domainname, char *link3_port);
uint8_t atk_idm750c_link4(atk_idm750c_link4mode_t link4, char *link4_domainname, char *link4_port);
uint8_t atk_idm750c_link1en(atk_idm750c_link1en_t link1en);    //第一路连接使能状态
uint8_t atk_idm750c_link2en(atk_idm750c_link2en_t link2en);    //第二路连接使能状态
uint8_t atk_idm750c_link3en(atk_idm750c_link3en_t link3en);    //第三路连接使能状态
uint8_t atk_idm750c_link4en(atk_idm750c_link4en_t link4en);    //第四路连接使能状态
uint8_t atk_idm750c_link1md(atk_idm750c_link1md_t link1md);    //第一路连接模式
uint8_t atk_idm750c_link2md(atk_idm750c_link2md_t link2md);
uint8_t atk_idm750c_link3md(atk_idm750c_link3md_t link3md);
uint8_t atk_idm750c_link4md(atk_idm750c_link4md_t link4md);
uint8_t atk_idm750c_query_link1sta(void);
uint8_t atk_idm750c_query_link2sta(void);
uint8_t atk_idm750c_query_link3sta(void);
uint8_t atk_idm750c_query_link4sta(void);
uint8_t atk_idm750c_link1_timeout(void);    //第一路超时重连时间
uint8_t atk_idm750c_link2_timeout(void);
uint8_t atk_idm750c_link3_timeout(void);
uint8_t atk_idm750c_link4_timeout(void);
uint8_t atk_idm750c_link1_duration(void);
uint8_t atk_idm750c_link2_duration(void);
uint8_t atk_idm750c_link3_duration(void);
uint8_t atk_idm750c_link4_duration(void);
uint8_t atk_idm750c_set_apn(void);
uint8_t atk_idm750c_send_data(void);
uint8_t atk_idm750c_send_fast(atk_idm750c_sendfast_t sendfast);
uint8_t atk_idm750c_set_yuanziyun(atk_idm750c_set_yuanziyun_t yuanziyun);    //原子云相关指令
uint8_t atk_idm750c_device_num(char *devicenum);    //原子云设备编号
uint8_t atk_idm750c_device_password(char *devicepassword);    //原子云设备密码
uint8_t atk_idm750c_registration_package(atk_idm750c_regen_t regen);    //注册包启用状态
uint8_t atk_idm750c_registration_package_data(void);    //注册包数据
uint8_t atk_idm750c_registration_package_send_method(void);    //注册包发送模式
uint8_t atk_idm750c_registration_package_data_type(void);    //注册包数据类型
uint8_t atk_idm750c_heartbeat_package(atk_idm750c_hrten_t heart);    //心跳包启用状态
uint8_t atk_idm750c_heartbeat_package_data(void);    //心跳包数据
uint8_t atk_idm750c_heartbeat_package_interval(void);    //心跳包时间间隔
uint8_t atk_idm750c_http_request_mode(atk_idm750c_http_request_mode_t mode);
uint8_t atk_idm750c_http_url_address(char *http_address);
uint8_t atk_idm750c_http_request_timeout(void);
uint8_t atk_idm750c_http_request_header_information(void);
uint8_t atk_idm750c_mqtt_clientid(char *clientid);
uint8_t atk_idm750c_mqtt_username(char *username);
uint8_t atk_idm750c_mqtt_password(char *password);
uint8_t atk_idm750c_server_address(char *ip,char *port);
uint8_t atk_idm750c_mqtt_sub_title(char *title);
uint8_t atk_idm750c_mqtt_pub_title(char *title);
uint8_t atk_idm750c_mqtt_para_information(atk_idm750c_mqtt_para_mode_t mode);
uint8_t atk_idm750c_dtu_enter_transfermode(void);
uint8_t atk_idm750c_aliyun_productkey(char *key);
uint8_t atk_idm750c_aliyun_devicesecret(char *secret);
uint8_t atk_idm750c_aliyun_devicename(char *name);
uint8_t atk_idm750c_aliyun_region(char *reg);
uint8_t atk_idm750c_aliyun_subscribe_title(char *ati);
uint8_t atk_idm750c_aliyun_release_title(char *ati);
uint8_t atk_idm750c_aliyun_para_information(atk_idm750c_aliyun_para_mode_t mode);
uint8_t atk_idm750c_onenet_device_id(char *id);
uint8_t atk_idm750c_onenet_product_id(char *id);
uint8_t atk_idm750c_onenet_authentication_information(char *ai);
uint8_t atk_idm750c_onenet_server_information(char *ip,char *port);
uint8_t atk_idm750c_onenet_para_information(atk_idm750c_onenet_para_mode_t mode);
uint8_t atk_idm750c_baiduyun_endpoint(char *data);
uint8_t atk_idm750c_baiduyun_name(char *name);
uint8_t atk_idm750c_baiduyun_key(char *key);
uint8_t atk_idm750c_baiduyun_sub_title(char *title);
uint8_t atk_idm750c_baiduyun_pub_title(char *title);
uint8_t atk_idm750c_baiduyun_para_information(atk_idm750c_baiduyun_para_mode_t mode);


#endif
