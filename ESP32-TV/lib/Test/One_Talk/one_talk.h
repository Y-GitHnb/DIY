#ifndef __WEATHER_H
#define __WEATHER_H

#include "config.h"
#include "ArduinoJson.h"
#include "HTTPClient.h"

#include "My_TFTLCD.h"

// 一言
typedef struct
{
	char hitokoto[1024]; // 一言正文 编码方式unicode 使用 utf-8
	char from[60];		 // 一言出处
} HitokotoData_t;

extern HitokotoData_t Hitokoto;

void get_Hitokoto(void);
String HTTP_Error_MY(int num);

#endif
