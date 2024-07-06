#ifndef __BUTTON_H
#define __BUTTON_H

#include <Button2.h> //按钮库

#include "config.h"
#include "My_WIFI.h"

#define BUTTON_PIN_13 13

extern Button2 Button_sw;

void Button_Init(void);		  // 按键初始化
void Esp_Reset(Button2 &btn); // ESP 重启

#endif
