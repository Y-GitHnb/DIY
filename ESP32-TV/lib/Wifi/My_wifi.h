#ifndef __MY_WIFI_H
#define __MY_WIFI_H

#include <EEPROM.h>
#include <WiFi.h>

#include <WiFiManager.h> // Wifi
#include <TimeLib.h>	 // 时间

#include "config.h"
#include "My_Button.h"
#include "My_TFTLCD.h"
#include "My_getHTTP.h"

struct config_type
{
	char stassid[32]; // 定义配网得到的WIFI名长度(最大32字节)
	char stapsw[64];  // 定义配网得到的WIFI密码长度(最大64字节)
};

extern WiFiManager wm;
extern WiFiUDP Udp;

void Wifi_Init();							 // WIFI 初始化
void open_Wifi();							 // 打开 Wifi
void colse_Wifi();							 // Wifi 休眠
void Wifi_Reset(Button2 &btn);				 // 重置 Wifi
void Write_WifiConfig(config_type wificonf); // EEPROM 写入 ssid，psw
void Read_WifiConfig(config_type wificonf);	 // EEPROM 读取 ssid，psw
void Delete_WifiConfig();					 // EEPROM 删除 ssid，psw
void Webconfig();							 // WEB 配网
void save_WebData();						 // 将从页面中获取的数据保存
void WIFI_reflash_All();					 // 所有需要联网后更新的方法都放在这里

#endif
