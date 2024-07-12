#include "My_Button.h"

// 定义按钮引脚
Button2 Button_sw = Button2();

/// @brief 按键初始化
void Button_Init(void)
{
	Button_sw.begin(BUTTON_PIN_13, INPUT_PULLUP);
	Button_sw.setDebounceTime(10);			   // 设置消抖时间
	Button_sw.setDoubleClickTime(500);		   // 设置双击时间
	Button_sw.setLongClickTime(1000);		   // 设置长按时间
	Button_sw.setClickHandler(Esp_Reset);	   // 单击事件，重启
	Button_sw.setLongClickHandler(Wifi_Reset); // 长按事件，Wifi 复位

	// Button_sw.setDoubleClickHandler();	  // 双击时间

	Serial.println("(Init) Button_Init...");
}

/// @brief ESP 重启
/// @param btn 按键
void Esp_Reset(Button2 &btn)
{
	Serial.println("(Configuration) ESP_EN...");
	ESP.restart();
}
