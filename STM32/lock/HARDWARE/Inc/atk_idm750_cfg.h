#ifndef __ATK_IDM750_CFG_H
#define __ATK_IDM750_CFG_H


#include "main.h"


typedef enum
{
    ATK_IDM750C_LINK1MODE_TCP = 0,  //TCP 模式
    ATK_IDM750C_LINK1MODE_UDP,      //UDP 模式
} atk_idm750c_link1mode_t;  //第一路连接参数


typedef enum
{
    ATK_IDM750C_LINK2MODE_TCP = 0,  //TCP 模式
    ATK_IDM750C_LINK2MODE_UDP,      //UDP 模式
} atk_idm750c_link2mode_t;  //第二路连接参数


typedef enum
{
    ATK_IDM750C_LINK3MODE_TCP = 0,  //TCP 模式
    ATK_IDM750C_LINK3MODE_UDP,      //UDP 模式
} atk_idm750c_link3mode_t;  //第三路连接参数


typedef enum
{
    ATK_IDM750C_LINK4MODE_TCP = 0,  //TCP 模式
    ATK_IDM750C_LINK4MODE_UDP,      //UDP 模式
} atk_idm750c_link4mode_t;  //第四路连接参数


typedef enum
{
    ATK_IDM750C_LINK1EN_ON = 0, //启用连接
    ATK_IDM750C_LINK1EN_OFF,    //不启用连接
} atk_idm750c_link1en_t;    //第一路连接使能状态


typedef enum
{
    ATK_IDM750C_LINK2EN_ON = 0, //启用连接
    ATK_IDM750C_LINK2EN_OFF,    //不启用连接
} atk_idm750c_link2en_t;    //第二路连接使能状态


typedef enum
{
    ATK_IDM750C_LINK3EN_ON = 0, //启用连接
    ATK_IDM750C_LINK3EN_OFF,    //不启用连接
} atk_idm750c_link3en_t;    //第三路连接使能状态


typedef enum
{
    ATK_IDM750C_LINK4EN_ON = 0, //启用连接
    ATK_IDM750C_LINK4EN_OFF,    //不启用连接
} atk_idm750c_link4en_t;    //第四路连接使能状态


typedef enum
{
    ATK_IDM750C_LINK1MD_LONG = 0,   //长连接
    ATK_IDM750C_LINK1MD_SHORT,      //短连接
} atk_idm750c_link1md_t;    //第一路连接模式


typedef enum
{
    ATK_IDM750C_LINK2MD_LONG = 0,   //长连接
    ATK_IDM750C_LINK2MD_SHORT,      //短连接
} atk_idm750c_link2md_t;    //第二路连接模式


typedef enum
{
    ATK_IDM750C_LINK3MD_LONG = 0,   //长连接
    ATK_IDM750C_LINK3MD_SHORT,      //短连接
} atk_idm750c_link3md_t;    //第三路连接模式


typedef enum
{
    ATK_IDM750C_LINK4MD_LONG = 0,   //长连接
    ATK_IDM750C_LINK4MD_SHORT,      //短连接
} atk_idm750c_link4md_t;    //第四路连接模式


typedef enum
{
    ATK_IDM750C_SENDFAST_ON = 0,    //快发模式
    ATK_IDM750C_SENDFAST_OFF,       //慢发模式
} atk_idm750c_sendfast_t;   //网络透传模式数据发送模式


typedef enum
{
    ATK_IDM750C_SET_YUANZIYUN_ON = 0,   //启用
    ATK_IDM750C_SET_YUANZIYUN_OFF,      //不启用
} atk_idm750c_set_yuanziyun_t;  //原子云启用状态


typedef enum
{
    ATK_IDM750C_SET_REGEN_ON = 0,   //启用
    ATK_IDM750C_SET_REGEN_OFF,      //不启用
} atk_idm750c_regen_t;  //注册包启用状态


typedef enum
{
    ATK_IDM750C_HRTEN_ON = 0,   //启用
    ATK_IDM750C_HRTEN_OFF,      //不启用
} atk_idm750c_hrten_t;  //心跳包启用状态


typedef enum
{
    ATK_IDM750C_HTTP_REQUEST_GET = 0,   //GET 方式
    ATK_IDM750C_HTTP_REQUEST_POST,      //POST 方式
} atk_idm750c_http_request_mode_t;  //HTTP相关指令


typedef enum
{
    ATK_IDM750C_MQTT_ZERO_MODE1 = 0,
    ATK_IDM750C_MQTT_ZERO_MODE2,
    ATK_IDM750C_MQTT_ZERO_MODE3,
    ATK_IDM750C_MQTT_ZERO_MODE4,
    ATK_IDM750C_MQTT_ONE_MODE1,
    ATK_IDM750C_MQTT_ONE_MODE2,
    ATK_IDM750C_MQTT_ONE_MODE3,
    ATK_IDM750C_MQTT_ONE_MODE4,
    ATK_IDM750C_MQTT_TWO_MODE1,
    ATK_IDM750C_MQTT_TWO_MODE2,
    ATK_IDM750C_MQTT_TWO_MODE3,
    ATK_IDM750C_MQTT_TWO_MODE4,
} atk_idm750c_mqtt_para_mode_t; //MQTT 参数信息


typedef enum
{
    ATK_IDM750C_ALIYUN_ZERO_MODE1 = 0,
    ATK_IDM750C_ALIYUN_ZERO_MODE2,
    ATK_IDM750C_ALIYUN_ZERO_MODE3,
    ATK_IDM750C_ALIYUN_ZERO_MODE4,
    ATK_IDM750C_ALIYUN_ONE_MODE1,
    ATK_IDM750C_ALIYUN_ONE_MODE2,
    ATK_IDM750C_ALIYUN_ONE_MODE3,
    ATK_IDM750C_ALIYUN_ONE_MODE4,
    ATK_IDM750C_ALIYUN_TWO_MODE1,
    ATK_IDM750C_ALIYUN_TWO_MODE2,
    ATK_IDM750C_ALIYUN_TWO_MODE3,
    ATK_IDM750C_ALIYUN_TWO_MODE4,
} atk_idm750c_aliyun_para_mode_t;   //阿里云参数信息


typedef enum
{
    ATK_IDM750C_ONENET_ZERO_MODE1 = 0,
    ATK_IDM750C_ONENET_ZERO_MODE2,
    ATK_IDM750C_ONENET_ZERO_MODE3,
    ATK_IDM750C_ONENET_ZERO_MODE4,
    ATK_IDM750C_ONENET_ZERO_MODE5,
    ATK_IDM750C_ONENET_ZERO_MODE6,
    ATK_IDM750C_ONENET_ZERO_MODE7,
    ATK_IDM750C_ONENET_ZERO_MODE8,
    ATK_IDM750C_ONENET_ZERO_MODE9,
    ATK_IDM750C_ONENET_ZERO_MODE10,
    ATK_IDM750C_ONENET_ZERO_MODE11,
    ATK_IDM750C_ONENET_ZERO_MODE12,
    ATK_IDM750C_ONENET_ONE_MODE1,
    ATK_IDM750C_ONENET_ONE_MODE2,
    ATK_IDM750C_ONENET_ONE_MODE3,
    ATK_IDM750C_ONENET_ONE_MODE4,
    ATK_IDM750C_ONENET_ONE_MODE5,
    ATK_IDM750C_ONENET_ONE_MODE6,
    ATK_IDM750C_ONENET_ONE_MODE7,
    ATK_IDM750C_ONENET_ONE_MODE8,
    ATK_IDM750C_ONENET_ONE_MODE9,
    ATK_IDM750C_ONENET_ONE_MODE10,
    ATK_IDM750C_ONENET_ONE_MODE11,
    ATK_IDM750C_ONENET_ONE_MODE12,
    ATK_IDM750C_ONENET_TWO_MODE1,
    ATK_IDM750C_ONENET_TWO_MODE2,
    ATK_IDM750C_ONENET_TWO_MODE3,
    ATK_IDM750C_ONENET_TWO_MODE4,
    ATK_IDM750C_ONENET_TWO_MODE5,
    ATK_IDM750C_ONENET_TWO_MODE6,
    ATK_IDM750C_ONENET_TWO_MODE7,
    ATK_IDM750C_ONENET_TWO_MODE8,
    ATK_IDM750C_ONENET_TWO_MODE9,
    ATK_IDM750C_ONENET_TWO_MODE10,
    ATK_IDM750C_ONENET_TWO_MODE11,
    ATK_IDM750C_ONENET_TWO_MODE12,
} atk_idm750c_onenet_para_mode_t;   //ONENET参数信息


typedef enum
{
    ATK_IDM750C_BAIDUYUN_ZERO_MODE1 = 0,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE2,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE3,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE4,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE5,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE6,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE7,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE8,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE9,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE10,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE11,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE12,
    ATK_IDM750C_BAIDUYUN_ONE_MODE1,
    ATK_IDM750C_BAIDUYUN_ONE_MODE2,
    ATK_IDM750C_BAIDUYUN_ONE_MODE3,
    ATK_IDM750C_BAIDUYUN_ONE_MODE4,
    ATK_IDM750C_BAIDUYUN_ONE_MODE5,
    ATK_IDM750C_BAIDUYUN_ONE_MODE6,
    ATK_IDM750C_BAIDUYUN_ONE_MODE7,
    ATK_IDM750C_BAIDUYUN_ONE_MODE8,
    ATK_IDM750C_BAIDUYUN_ONE_MODE9,
    ATK_IDM750C_BAIDUYUN_ONE_MODE10,
    ATK_IDM750C_BAIDUYUN_ONE_MODE11,
    ATK_IDM750C_BAIDUYUN_ONE_MODE12,
} atk_idm750c_baiduyun_para_mode_t;     //百度云参数信息


typedef enum
{
    ATK_IDM750C_WORKMODE_NET = 0,   //网络透传模式
    ATK_IDM750C_WORKMODE_HTTP,      //HTTP 透传模式
    ATK_IDM750C_WORKMODE_MQTT,      //MQTT 透传模式
    ATK_IDM750C_WORKMODE_ALIYUN,    //阿里云透传模式
    ATK_IDM750C_WORKMODE_ONENET,    //OneNET 透传模式
    ATK_IDM750C_WORKMODE_BAUDUYUN,  //百度云透传模式
    ATK_IDM750C_WORKMODE_RNDIS,     //无线上网工作模式
} atk_idm750c_workmode_t;   //工作模式


typedef enum
{
    DTU_WORKMODE_NET = 0,   //网络透传模式
    DTU_WORKMODE_HTTP,      //http透传模式
    DTU_WORKMODE_MQTT,      //mqtt透传模式
    DTU_WORKMODE_ALIYUN,    //阿里云透传模式
    DTU_WORKMODE_ONENET,    //OneNET透传模式
    DTU_WORKMODE_BAIDUYUN,  //百度云透传模式
} _dtu_work_mode_eu;


typedef struct
{
    uint32_t timeout; /*指令等待超时时间，单位：100ms*/
    char *read_cmd;   /*查询参数指令      请参考DTU AT用户手册说明进行填写*/
    char *write_cmd;  /*配置参数指令      请参考DTU AT用户手册说明进行填写*/
} _dtu_atcmd_st;


typedef struct
{
    const char *urc_info;                         /*DTU自动上报的URC信息*/
    void (*func)(const char *data, uint32_t len); /*回调处理函数*/
} _dtu_urc_st;


typedef enum
{
    ATK_IDM750C_ECHO_ON = 0,
    ATK_IDM750C_ECHO_OFF,
} atk_idm750c_echo_t;


typedef enum
{
    ATK_IDM750C_UARTMODE_FIRST = 0,
    ATK_IDM750C_UARTMODE_SECOND,
    ATK_IDM750C_UARTMODE_THIRD,
    ATK_IDM750C_UARTMODE_FOURTH,
    ATK_IDM750C_UARTMODE_FIFTH,
    ATK_IDM750C_UARTMODE_SIXTH,
    ATK_IDM750C_UARTMODE_SEVENTH,
    ATK_IDM750C_UARTMODE_EIGHTH,
    ATK_IDM750C_UARTMODE_NINTH,
    ATK_IDM750C_UARTMODE_TENTH,
    ATK_IDM750C_UARTMODE_ELEVENTH,
    ATK_IDM750C_UARTMODE_TWELFTH,
    ATK_IDM750C_UARTMODE_THIRTEENTH,
} atk_idm750c_uartmode_t;   //串口参数


typedef enum
{
    ATK_IDM750C_UART_ON = 0,
    ATK_IDM750C_UART_OFF,
} atk_idm750c_urat_t;   //串口透传配置


typedef enum
{
    ATK_IDM750C_NET_ON = 0,
    ATK_IDM750C_NET_OFF,
} atk_idm750c_net_t;    //网络透传指令


#endif
