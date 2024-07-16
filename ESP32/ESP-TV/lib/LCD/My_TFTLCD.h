#ifndef __MY_BUTTON
#define __MY_BUTTON

#include <EEPROM.h>

#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "Lib/Animate.h"	 // 动画
#include "Lib/weatherNum.h"	 // 天气图标
#include "Lib/temperature.h" // 温度图标
#include "Lib/humidity.h"	 // 湿度图标

#include "Lib/font_ye_20.h"	   // 字库
#include "Lib/timeClockFont.h" // 时间时钟字库

#include "config.h"
#include "My_wifi.h"
#include "My_Thread.h"
#include "dht11.h"

// const uint8_t Font_ye_20[20] PROGMEM = {};

#define My_Font Font_ye_20 // 使用字库

// 屏幕结构
extern TFT_eSPI tft;

extern byte loadNum; // 进度条进度

void TFT_Init();												  // TFT 初始化
void TJpgDec_Init();											  // 图片解码库初始化
void TFT_Close();												  // 清屏
void Show_WS();													  // 显示图片
void loading(byte delayTime, char stassid[]);					  // 绘制 WIFI 进度条
void Web_Show();												  // WEB 配网显示函数
void weater_Show(String *cityDZ, String *dataSK, String *dataFC); // 天气信息写到屏幕上
void digitalClockDisplay(int reflash_en = 0);					  // 日期刷新
void scrollBanner();											  // 显示天气信息
void DHT11_Show();												  // 显示 DHT11 数据
void LCD_reflash();												  // 强制屏幕刷新
void show_str(const char *string);								  // 显示指定字体

#endif
