#ifndef __BUTTON_H
#define __BUTTON_H

#include <Button2.h> //按钮库

#include "config.h"
#include "My_WIFI.h"

#define BUTTON_PIN 36
#define BUTTON_A 12
#define BUTTON_B 14
#define BUTTON_S 27

extern Button2 Button_sw;

void Button_Init(void);		  // 按键初始化
void Esp_Reset(Button2 &btn); // ESP 重启
int getEncoderTurn();		  // 旋转编码器

#endif
