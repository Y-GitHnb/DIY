#ifndef __MY_BUTTON
#define __MY_BUTTON

#include <EEPROM.h>

#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "config.h"
// #include "Lib/font_hei_16.h"
// #include "Lib/font_hei_20.h"
#include "Lib/font_ye_16.h"
// #include "Lib/font_ye_20.h"
#include "Lib/timeClockFont.h" // 时间时钟字库
#include "Lib/Animate.h"	   // 动画
#include "Lib/weatherNum.h"	   // 天气图标
#include "Lib/temperature.h"   // 温度图标
#include "Lib/humidity.h"	   // 湿度图标

#include "My_wifi.h"

// const uint8_t Font_ye_16[20] PROGMEM = {};

#define My_Font Font_ye_16 // 使用字库

// 屏幕结构
extern TFT_eSPI tft;
// extern TFT_eSprite clk;

extern byte loadNum;

void TFT_Init();																			 // TFT 初始化
void TJpgDec_Init();																		 // 图片解码库初始化
void TFT_Close();																			 // 清屏
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap);			 // TFT屏幕输出函数
void drawLineFont(uint32_t _x, uint32_t _y, uint32_t _num, uint32_t _size, uint32_t _color); // 用快速线方法绘制数字
void loading(byte delayTime);																 // 绘制 WIFI 进度条
void Web_Show();																			 // WEB 配网显示函数
void weater_Show(String *cityDZ, String *dataSK, String *dataFC);							 // 天气信息写到屏幕上
void digitalClockDisplay(int reflash_en = 0);												 // 日期刷新
void scrollBanner();																		 // 显示天气信息
void DHT11_Show();																			 // 显示 DHT11 数据

#endif
