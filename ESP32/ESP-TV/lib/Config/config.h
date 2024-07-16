#ifndef __CONFIG_H
#define __CONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

#include <TFT_eSPI.h>
#include <TimeLib.h>

#include "My_getHTTP.h"
#include "My_wifi.h"

#define Version "YQY & ZL"

// EEPROM 参数存储地址位
#define BL_addr 1	 // 亮度 EEPROM 地址
#define Ro_addr 2	 // 旋转方向 EEPROM 地址
#define DHT_addr 3	 // 3 DHT使能标志位
#define CC_addr 10	 // 城市 EEPROM 地址
#define Wifi_addr 30 // wifi EEPROM 地址

// 使能标志位
#define WM_EN 1			// WEB 配网使能
extern uint8_t Wifi_en; // WIFI模块启动	1：打开	0：关闭
#define DHT_EN 0		// 有没有 DHT11
extern bool DHT_flag;	// 用不用 DHT11

// WIFI
extern const char *My_AP; // 热点 AP

// mqtt 配置
#define MQTT_IP "test.ranye-iot.net" // mqtt服务器地址  test.ranye-iot.net

// LCD
#define PEN_COLOR TFT_PINK		   // 笔色
#define BAKCGROUND_COLOR TFT_BLACK // 底色
#define timeY 82				   // 绘制数字高度
extern int LCD_BL_PWM;			   // LCD 背光
extern int LCD_Rotation;		   // LCD 屏幕方向
extern int prevTime;			   // 滚动显示更新标志位
extern String scrollText[7];	   // 滚动文本
extern uint8_t text_Index;		   // 滚动文本循环索引

// 动画
#define Animate_Choice 1			 // 动图选择：1,太空人图片 2,胡桃
extern const uint8_t *Animate_value; // 指向关键帧的指针
extern uint32_t Animate_size;		 // 指向关键帧大小的指针
extern const uint8_t *Anilove_value; // 指向关键帧的指针
extern uint32_t Anilove_size;		 // 指向关键帧大小的指针
extern int Amimate_reflash_Time;	 // 更新时间记录
extern int Amilove_reflash_Time;	 // 更新时间记录

// 天气
struct Weather_Msg
{
	String cityDZ;
	String dataSK;
	String dataFC;
};
extern Weather_Msg weather_msg; // 天气变量

#define WEATHER_UPDATE_TIME 10 // 默认天气更新时间
extern uint16_t Weater_time;   // 天气更新时间 X 分钟（默认10分钟）
extern String cityCode;		   // 天气城市代码

extern int tempnum; // 温度百分比
extern int huminum; // 湿度百分比
extern int tempcol; // 温度显示颜色
extern int humicol; // 湿度显示颜色

// 星期
extern String week();

// 月日
extern String monthDay();

// 时间
#define TMS 1000		// 一千毫秒
extern int Hour_sign;	// 小时
extern int Minute_sign; // 分钟
extern int Second_sign; // 秒

// ##################### 纪念日页面配置 #####################################
// 页面
#define CLOCK_PAGE 0
#define LOVE_PAGE 1
#define MISSU_PAGE 2
extern byte page;
extern byte pre_page; // 切换前一个页面,后面单击退出时能够回到之前的页面
extern byte role;

#define DEFAULT_WORDS "{\"word\":\"因有着你，跟你一起，亲爱的你\"}" // 只能修改汉字内容
#define WORD_UPDATE_TIME 3											// 情话切换时间单位 - 分钟
#define ANIMATE_CHANGE_FREQUENTCE 20								// 动画切换频次，20此切换一张

#define BUTTOM_WORD "@M&G since 2021.06.25" // 纪念日页面底部文字

#define YEAR 2021 // 纪念日 年
#define MONTH 6	  // 纪念日  月
#define DAY 25	  // 纪念日  日

// ##################### 想你页面配置 #####################################
// mqtt 配置
#define MQTT_IP "test.ranye-iot.net" // mqtt服务器地址  test.ranye-iot.net

#define RECEIVER 0
#define SENDER 1

// 1是我的小电视，0是女朋友的小电视
#if 0
#define OUT_TOPIC "my" // 本机要推送消息的主题
#define IN_TOPIC "you" // 本机订阅消息的主题
#else
#define OUT_TOPIC "yqy" // 本机要推送消息的主题
#define IN_TOPIC "zl"	// 本机订阅消息的主题
#endif

#define IN_MSG "imu"		  // 收到消息
#define IN_MSG_CHECK "check"  // 收到消息确认
#define OUT_MSG "imu"		  // 推送消息
#define OUT_MSG_CHECK "check" // 推送消息确认

void Serial_set();

#endif
