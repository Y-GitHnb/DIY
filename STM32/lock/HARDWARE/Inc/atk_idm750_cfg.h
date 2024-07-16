#ifndef __ATK_IDM750_CFG_H
#define __ATK_IDM750_CFG_H


#include "main.h"


typedef enum
{
    ATK_IDM750C_LINK1MODE_TCP = 0,  //TCP ģʽ
    ATK_IDM750C_LINK1MODE_UDP,      //UDP ģʽ
} atk_idm750c_link1mode_t;  //��һ·���Ӳ���


typedef enum
{
    ATK_IDM750C_LINK2MODE_TCP = 0,  //TCP ģʽ
    ATK_IDM750C_LINK2MODE_UDP,      //UDP ģʽ
} atk_idm750c_link2mode_t;  //�ڶ�·���Ӳ���


typedef enum
{
    ATK_IDM750C_LINK3MODE_TCP = 0,  //TCP ģʽ
    ATK_IDM750C_LINK3MODE_UDP,      //UDP ģʽ
} atk_idm750c_link3mode_t;  //����·���Ӳ���


typedef enum
{
    ATK_IDM750C_LINK4MODE_TCP = 0,  //TCP ģʽ
    ATK_IDM750C_LINK4MODE_UDP,      //UDP ģʽ
} atk_idm750c_link4mode_t;  //����·���Ӳ���


typedef enum
{
    ATK_IDM750C_LINK1EN_ON = 0, //��������
    ATK_IDM750C_LINK1EN_OFF,    //����������
} atk_idm750c_link1en_t;    //��һ·����ʹ��״̬


typedef enum
{
    ATK_IDM750C_LINK2EN_ON = 0, //��������
    ATK_IDM750C_LINK2EN_OFF,    //����������
} atk_idm750c_link2en_t;    //�ڶ�·����ʹ��״̬


typedef enum
{
    ATK_IDM750C_LINK3EN_ON = 0, //��������
    ATK_IDM750C_LINK3EN_OFF,    //����������
} atk_idm750c_link3en_t;    //����·����ʹ��״̬


typedef enum
{
    ATK_IDM750C_LINK4EN_ON = 0, //��������
    ATK_IDM750C_LINK4EN_OFF,    //����������
} atk_idm750c_link4en_t;    //����·����ʹ��״̬


typedef enum
{
    ATK_IDM750C_LINK1MD_LONG = 0,   //������
    ATK_IDM750C_LINK1MD_SHORT,      //������
} atk_idm750c_link1md_t;    //��һ·����ģʽ


typedef enum
{
    ATK_IDM750C_LINK2MD_LONG = 0,   //������
    ATK_IDM750C_LINK2MD_SHORT,      //������
} atk_idm750c_link2md_t;    //�ڶ�·����ģʽ


typedef enum
{
    ATK_IDM750C_LINK3MD_LONG = 0,   //������
    ATK_IDM750C_LINK3MD_SHORT,      //������
} atk_idm750c_link3md_t;    //����·����ģʽ


typedef enum
{
    ATK_IDM750C_LINK4MD_LONG = 0,   //������
    ATK_IDM750C_LINK4MD_SHORT,      //������
} atk_idm750c_link4md_t;    //����·����ģʽ


typedef enum
{
    ATK_IDM750C_SENDFAST_ON = 0,    //�췢ģʽ
    ATK_IDM750C_SENDFAST_OFF,       //����ģʽ
} atk_idm750c_sendfast_t;   //����͸��ģʽ���ݷ���ģʽ


typedef enum
{
    ATK_IDM750C_SET_YUANZIYUN_ON = 0,   //����
    ATK_IDM750C_SET_YUANZIYUN_OFF,      //������
} atk_idm750c_set_yuanziyun_t;  //ԭ��������״̬


typedef enum
{
    ATK_IDM750C_SET_REGEN_ON = 0,   //����
    ATK_IDM750C_SET_REGEN_OFF,      //������
} atk_idm750c_regen_t;  //ע�������״̬


typedef enum
{
    ATK_IDM750C_HRTEN_ON = 0,   //����
    ATK_IDM750C_HRTEN_OFF,      //������
} atk_idm750c_hrten_t;  //����������״̬


typedef enum
{
    ATK_IDM750C_HTTP_REQUEST_GET = 0,   //GET ��ʽ
    ATK_IDM750C_HTTP_REQUEST_POST,      //POST ��ʽ
} atk_idm750c_http_request_mode_t;  //HTTP���ָ��


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
} atk_idm750c_mqtt_para_mode_t; //MQTT ������Ϣ


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
} atk_idm750c_aliyun_para_mode_t;   //�����Ʋ�����Ϣ


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
} atk_idm750c_onenet_para_mode_t;   //ONENET������Ϣ


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
} atk_idm750c_baiduyun_para_mode_t;     //�ٶ��Ʋ�����Ϣ


typedef enum
{
    ATK_IDM750C_WORKMODE_NET = 0,   //����͸��ģʽ
    ATK_IDM750C_WORKMODE_HTTP,      //HTTP ͸��ģʽ
    ATK_IDM750C_WORKMODE_MQTT,      //MQTT ͸��ģʽ
    ATK_IDM750C_WORKMODE_ALIYUN,    //������͸��ģʽ
    ATK_IDM750C_WORKMODE_ONENET,    //OneNET ͸��ģʽ
    ATK_IDM750C_WORKMODE_BAUDUYUN,  //�ٶ���͸��ģʽ
    ATK_IDM750C_WORKMODE_RNDIS,     //������������ģʽ
} atk_idm750c_workmode_t;   //����ģʽ


typedef enum
{
    DTU_WORKMODE_NET = 0,   //����͸��ģʽ
    DTU_WORKMODE_HTTP,      //http͸��ģʽ
    DTU_WORKMODE_MQTT,      //mqtt͸��ģʽ
    DTU_WORKMODE_ALIYUN,    //������͸��ģʽ
    DTU_WORKMODE_ONENET,    //OneNET͸��ģʽ
    DTU_WORKMODE_BAIDUYUN,  //�ٶ���͸��ģʽ
} _dtu_work_mode_eu;


typedef struct
{
    uint32_t timeout; /*ָ��ȴ���ʱʱ�䣬��λ��100ms*/
    char *read_cmd;   /*��ѯ����ָ��      ��ο�DTU AT�û��ֲ�˵��������д*/
    char *write_cmd;  /*���ò���ָ��      ��ο�DTU AT�û��ֲ�˵��������д*/
} _dtu_atcmd_st;


typedef struct
{
    const char *urc_info;                         /*DTU�Զ��ϱ���URC��Ϣ*/
    void (*func)(const char *data, uint32_t len); /*�ص�������*/
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
} atk_idm750c_uartmode_t;   //���ڲ���


typedef enum
{
    ATK_IDM750C_UART_ON = 0,
    ATK_IDM750C_UART_OFF,
} atk_idm750c_urat_t;   //����͸������


typedef enum
{
    ATK_IDM750C_NET_ON = 0,
    ATK_IDM750C_NET_OFF,
} atk_idm750c_net_t;    //����͸��ָ��


#endif
