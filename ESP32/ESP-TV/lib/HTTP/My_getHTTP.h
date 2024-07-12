#ifndef __GET_HTTP_H
#define __GET_HTTP_H

#include <EEPROM.h>

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <PubSubClient.h>

#include "config.h"
#include "My_wifi.h"
#include "My_TFTLCD.h"

extern WiFiClient wificlient;	// wifi 连接 UDP 设置参数
extern PubSubClient mqttClient; // mqtt参数
extern const char *mqtt_server;

void get_City();	  // 获取城市代码
void getCityWeater(); // 获取城市天气
void getCityCode();	  // 发送HTTP请求并且将服务器响应通过串口输出
time_t getNtpTime();  // 通过 NTP 协议获取网络时间

#endif
