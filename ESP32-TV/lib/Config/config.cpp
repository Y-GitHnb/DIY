#include "config.h"

// LCD
int LCD_BL_PWM = 50;	// 屏幕亮度0-100，默认50
int LCD_Rotation = 0;	// LCD屏幕方向
String scrollText[7];	// 滚动文本
uint8_t text_Index = 0; // 滚动文本循环索引
int prevTime = 0;		// 滚动显示更新标志位

// 动画
const uint8_t *Animate_value; // 指向关键帧的指针
uint32_t Animate_size;		  // 指向关键帧大小的指针
int Amimate_reflash_Time = 0; // 更新时间记录
int Amilove_reflash_Time = 0; // 更新时间记录

// Wifi
uint8_t Wifi_en = 1;		  // WIFI模块启动  1：打开    0：关闭
const char *My_AP = "YQY_AP"; // 配网 AP

// 天气信息
Weather_Msg weather_msg = {{""}, {""}, {""}}; // 天气变量

uint16_t Weater_time = WEATHER_UPDATE_TIME; // 天气更新时间 X 分钟（默认10分钟）
String cityCode = "101090609";				// 天气城市代码

int tempnum = 0;		 // 温度百分比
int huminum = 0;		 // 湿度百分比
int tempcol = TFT_WHITE; // 温度显示颜色
int humicol = TFT_WHITE; // 湿度显示颜色

// 星期
String week()
{
	String wk[7] = {"日", "一", "二", "三", "四", "五", "六"};
	String s = "周" + wk[weekday() - 1];
	return s;
}

// 月日
String monthDay()
{
	String s = String(month());
	s = s + "月" + day() + "日";
	return s;
}

// 时间
int Hour_sign = 60;		// 小时
int Minute_sign = 60;	// 分钟
int Second_sign = 60;	// 秒
time_t prevDisplay = 0; // 显示时间显示记录

// DHT11
bool DHT_flag = 0; // 用不用 DHT11
