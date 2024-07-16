#include "config.h"
#include "My_Button.h"
#include "My_TFTLCD.h"
#include "My_wifi.h"
#include "My_getHTTP.h"
#include "My_Thread.h"

#define BULE 115200

void setup()
{
	Serial.begin(BULE);
	EEPROM.begin(1024);

	TFT_Init(); // TFT 初始化

	Button_Init(); // 按键初始化

	Wifi_Init(); // Wifi 初始化

	TJpgDec_Init();	 // 图片解码
	Show_WS();		 // 温湿度图片
	getCityWeater(); // 获取显示天气

	Thread_Init(); // 线程任务
}

void loop()
{
	Button_sw.loop(); // 按钮轮询
	// page += getEncoderTurn();

	Serial_set(); // 串口响应

	Supervisor_controller(); // 守护线程池
	WIFI_reflash_All();		 // WIFI应用
}
