#include "my_time.h"

// NTP服务器
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;

void Time_Init()
{
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	printLocalTime();
}

void printLocalTime()
{
	struct tm timeinfo;

	while (1) // 获取时间循环
	{
		if (!getLocalTime(&timeinfo))
		{
			Serial.println("Failed to obtain time");
		}
		else
		{
			Serial.println(&timeinfo, "%F %A"); //%A, %B %d %Y %H:%M:%S
			Serial.println(&timeinfo, "%T");
			return;
		}
	}
}

// https://api.seniverse.com/v3/weather/now.json?key=your_api_key&location=beijing&language=zh-Hans&unit=c
String url = "https://api.seniverse.com/v3/weather/now.json"; // 知心天气请求网址
String key = "S1Y6dCLNaDjlgcFho";							  // 知心天气私钥
String city = "beijing";									  // 查询城市

// 天气的刷新时间我这里显示的是7到10分钟，所以每七到十分钟就要重新给网页发送GET请求，不然数据不会刷新，建议用定时器
void http_weather()
{
	HTTPClient http;
	http.setTimeout(5000);								   // 设置超出响应时间
	http.begin(url + "?key=" + key + "&location=" + city); // 发送GET请求

	int httpCode = http.GET();
	if (httpCode == HTTP_CODE_OK)
	{
		// 获取响应正文
		String response = http.getString();
		Serial.println("响应数据");
		Serial.println(response);

		DynamicJsonDocument doc(1024);										// 创建DynamicJsonDocument对象
		deserializeJson(doc, response);										// 解析JSON数据
		String Name = doc["results"][0]["location"]["name"].as<String>();	// 位置
		String Wea = doc["results"][0]["now"]["text"].as<String>();			// 天气
		String Temp = doc["results"][0]["now"]["temperature"].as<String>(); // 温度
		String Time = doc["results"][0]["last_update"].as<String>();		// 时间

		Serial.printf("位置：%s\n", Name);
		Serial.printf("温度：%s\n", Temp);
		Serial.printf("天气：%s\n", Wea);
		Serial.printf("时间：%s\n", Time);
	}

	else
	{
		String anser = HTTP_Error_MY(httpCode);
		Serial.println(anser);
	}
	http.end();
}
