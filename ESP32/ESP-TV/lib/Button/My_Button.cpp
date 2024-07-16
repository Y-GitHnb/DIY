#include "My_Button.h"

// 定义按钮引脚
Button2 Button_sw = Button2();

/// @brief 按键初始化
void Button_Init(void)
{
	Button_sw.begin(BUTTON_PIN, INPUT_PULLUP);
	Button_sw.setDebounceTime(10);			   // 设置消抖时间
	Button_sw.setDoubleClickTime(500);		   // 设置双击时间
	Button_sw.setLongClickTime(1000);		   // 设置长按时间
	Button_sw.setClickHandler(Esp_Reset);	   // 单击事件，重启
	Button_sw.setLongClickHandler(Wifi_Reset); // 长按事件，Wifi 复位
	// Button_sw.setDoubleClickHandler();	  // 双击时间

	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_S, INPUT_PULLDOWN);

	Serial.println("(Init) Button_Init...");
}

/// @brief ESP 重启
/// @param btn 按键
void Esp_Reset(Button2 &btn)
{
	Serial.println("(Configuration) ESP_EN...");
	ESP.restart();
}

int getEncoderTurn()
{
	static int oldA = LOW;
	static int oldB = LOW;
	int result = 0;

	int newA = digitalRead(BUTTON_A);
	int newB = digitalRead(BUTTON_B);
	int key = digitalRead(BUTTON_S);

	if (newA != oldA || newB != oldB)
	{
		// something has changed
		if (oldA == LOW && newA == HIGH)
			result = -(oldB * 2 - 1);
	}

	if (!key)
	{
		page = 0;
	}

	oldA = newA;
	oldB = newB;

	return result;
}
