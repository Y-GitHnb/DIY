#ifndef __MY_TIME_H
#define __MY_TIME_H

#include "config.h"
#include "time.h"
#include "ArduinoJson.h"
#include "HTTPClient.h"
#include "string"

#include "My_TFTLCD.h"
#include "one_talk.h"

void Time_Init();
void printLocalTime();

void http_weather();

#endif
