#include "config.h"

// LCD
int LCD_BL_PWM = 1;		// 屏幕亮度0-100
int LCD_Rotation = 1;	// LCD屏幕方向
String scrollText[7];	// 滚动文本
uint8_t text_Index = 0; // 滚动文本循环索引
int prevTime = 0;		// 滚动显示更新标志位

// 动画
const uint8_t *Animate_value; // 指向关键帧的指针
uint32_t Animate_size;		  // 指向关键帧大小的指针
int Amimate_reflash_Time = 0; // 更新时间记录

// Wifi
uint8_t Wifi_en = 1;		  // WIFI模块启动  1：打开    0：关闭
const char *My_AP = "YQY_AP"; // 配网 AP

// 天气信息
Weather_Msg weather_msg = {{""}, {""}, {""}}; // 天气变量

uint16_t Weater_time = WEATHER_UPDATE_TIME; // 天气更新时间 X 分钟（默认10分钟）
String cityCode = "101010400";				// 天气城市代码(顺义)

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

// 串口调试
String Ser_flag = "";

/// @brief 串口调试
void Serial_set()
{
	String Ser_buf = "";

	if (Serial.available() > 0)
	{
		while (Serial.available() > 0)
		{
			Ser_buf += char(Serial.read()); // 读取单个字符值，转换为字符，并按顺序一个个赋值
			delay(2);						// 不能省略，因为读取缓冲区数据需要时间
		}

		if (Ser_flag == "0x01") // 1  亮度设置
		{
			int LCDBL = atoi(Ser_buf.c_str()); // String 转 int

			if (LCDBL >= 0 && LCDBL <= 100)
			{
				EEPROM.write(BL_addr, LCDBL); // 亮度地址写入亮度值
				EEPROM.commit();			  // 保存更改的数据
				delay(5);

				LCD_BL_PWM = EEPROM.read(BL_addr);
				delay(5);

				Serial.printf("(Answer) LCD bright to: %d...\r\n", LCD_BL_PWM);
				analogWrite(TFT_BL, (LCD_BL_PWM * 10));

				Ser_flag = "";
			}
			else
				Serial.println("(Error) LCD bright error(0-100)!");
		}

		else if (Ser_flag == "0x02") // 2 地址设置
		{
			int CityCODE = 0;
			int CityC = atoi(Ser_buf.c_str()); // String 转 int

			if (((CityC >= 101000000) && (CityC <= 102000000)) || (CityC == 0))
			{
				for (int cnum = 0; cnum < 5; cnum++)
				{
					EEPROM.write(CC_addr + cnum, CityC % 100); // 城市地址写入城市代码
					EEPROM.commit();						   // 保存更改的数据
					CityC = CityC / 100;
					delay(5);
				}

				for (int cnum = 5; cnum > 0; cnum--)
				{
					CityCODE = CityCODE * 100;
					CityCODE += EEPROM.read(CC_addr + cnum - 1);
					delay(5);
				}

				cityCode = CityCODE;

				if (cityCode == "0")
				{
					Serial.println("(Answer) Automatic acquisition city...");
					getCityCode(); // 获取城市代码
				}
				else
				{
					Serial.printf("(Answer) The city code is: %d...\r\n", cityCode);
				}
				getCityWeater(); // 更新城市天气
				Ser_flag = "";
			}
			else
				Serial.println("(Error) city code error(input 9 place code or 0 automatic acquisition)!"); // 9位城市代码 或 0自动获取
		}

		else if (Ser_flag == "0x03") // 3 屏幕显示方向
		{
			int RoSet = atoi(Ser_buf.c_str());

			if (RoSet >= 0 && RoSet <= 3)
			{
				EEPROM.write(Ro_addr, RoSet); // 屏幕方向地址写入方向值
				EEPROM.commit();			  // 保存更改的数据

				// 设置屏幕方向后重新刷屏并显示
				tft.setRotation(RoSet);
				tft.fillScreen(BAKCGROUND_COLOR);
				LCD_reflash(); // 屏幕刷新程序
				Show_WS();	   // 温湿度

				Serial.printf("(Answer) LCD direction: %d...\r\n", RoSet);

				Ser_flag = "";
			}
			else
			{
				Serial.println("(Error) LCD direction error(input 0-3)!");
			}
		}

		else if (Ser_flag == "0x04") // 4 天气更新时间
		{
			int wtup = atoi(Ser_buf.c_str());

			if (wtup >= 1 && wtup <= 60)
			{
				Weater_time = wtup;

				Serial.printf("(Answer) Weater time is: %d minute...\r\n", Weater_time);
				Ser_flag = "";
			}
			else
				Serial.println("(Error) Weater time long(1-60)!");
		}

		else
		{
			Ser_flag = Ser_buf;
			delay(2);

			if (Ser_flag == "0x01")
				Serial.println("(Configuration) Input LCD bright(0-100)...");

			else if (Ser_flag == "0x02")
				Serial.println("(Configuration) Input city code(9 place code or 0 automatic acquisition)...");

			else if (Ser_flag == "0x03")
			{
				Serial.println("(Configuration) Input LCD direction(0-3)...");
				Serial.println("0-USB down");
				Serial.println("1-USB right");
				Serial.println("2-USB up");
				Serial.println("3-USB left");
			}

			else if (Ser_flag == "0x04")
			{
				Serial.printf("(Answer) Weater time now: %d minute...\r\n", Weater_time);
				Serial.println("(Configuration) Input Weater time (1-60) minute...");
			}

			else if (Ser_flag == "0x05")
			{
				Serial.println("(Configuration) Reset WiFi...");
				delay(10);

				wm.resetSettings();
				Delete_WifiConfig();
				delay(10);

				Serial.println("(Answer) Reset WiFi Succeed...");
				Ser_flag = "";

				ESP.restart();
			}

			else
			{
				Serial.println("");
				Serial.println("Input the code you want to modify: ");
				Serial.println("0x01: LCD bright");
				Serial.println("0x02: city code");
				Serial.println("0x03: LCD direction");
				Serial.println("0x04: Weater time");
				Serial.println("0x05: reset WiFi");
				Serial.println("");
			}
		}
	}
}
