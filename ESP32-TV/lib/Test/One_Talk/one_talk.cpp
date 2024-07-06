#include "one_talk.h"

const char *talk_http = "https://v1.hitokoto.cn/";

HitokotoData_t Hitokoto;

/*
{
	"id": 6368,
	"uuid": "90948bf0-03cd-4c09-a8cd-4fc6d9b8d9c1",
	"hitokoto": "远方未必远，未来一定来。",
	"type": "f",
	"from": "网络",
	"from_who": null,
	"creator": "像风",
	"creator_uid": 6731,
	"reviewer": 1,
	"commit_from": "web",
	"created_at": "1594981252",
	"length": 12
}
*/

void get_Hitokoto(void)
{
	HTTPClient http;
	http.begin(talk_http); // 指定 URL

	int httpCode = http.GET(); // Make the request

	if (httpCode == HTTP_CODE_OK)
	{
		String payload = http.getString();

		if (SERIAL_EN)
		{
			Serial.println(httpCode);
			Serial.println(payload);
		}

		StaticJsonDocument<1024> doc; // StaticJsonDocument 在栈区分配 1024 内存
		// DynamicJsonDocument doc(1024); // DynamicJsonDocument 在堆区分配内存

		DeserializationError error = deserializeJson(doc, payload); // 反序列化JSON文档

		if (error)
		{
			if (SERIAL_EN)
			{
				Serial.println("JSON 解析失败!");
			}
			if (LCD_EN)
			{
			}
		}
		else
		{
			if (strlen(doc["hitokoto"]) > sizeof(Hitokoto.hitokoto))
			{
				if (SERIAL_EN)
				{
					Serial.println("解析数据过长...");
				}
				if (LCD_EN)
				{
				}
				http.end();
				return;
			}
			strcpy(Hitokoto.hitokoto, doc["hitokoto"]);
			strcpy(Hitokoto.from, doc["from"]);

			if (SERIAL_EN)
			{
				Serial.println(Hitokoto.hitokoto);
				Serial.printf("出处：");
				Serial.println(Hitokoto.from);
				Serial.println();
			}
			if (LCD_EN)
			{
			}
		}
	}

	else
	{
		String anser = HTTP_Error_MY(httpCode);

		if (SERIAL_EN)
		{
			Serial.println(anser);
		}
		if (LCD_EN)
		{
		}
	}

	http.end();
}

String HTTP_Error_MY(int num)
{
	String str_back;

	switch (num)
	{
	case -1:
		str_back = "HTTP:(服务器拒绝连接)";
		break;
	case -2:
		str_back = "HTTP:(发送头信息错误)";
		break;
	case -3:
		str_back = "HTTP:(发送请求体时失败)";
		break;
	case -4:
		str_back = "HTTP:(连接服务器失败)";
		break;
	case -5:
		str_back = "HTTP:(服务器传输中断)";
		break;
	case -6:
		str_back = "HTTP:(没有可用流处理后续数据)";
		break;
	case -7:
		str_back = "HTTP:(无法连接服务器)";
		break;
	case -8:
		str_back = "HTTP:(运行过程内存不足)";
		break;
	case -9:
		str_back = "HTTP:(数据编解码格式错误)";
		break;
	case -10:
		str_back = "HTTP:(写入流出现错误)";
		break;
	case -11:
		str_back = "HTTP:(读取数据超时)";
		break;
	case 110:
		str_back = "HTTP:(token无效)";
		break;
	case 404:
		str_back = "HTTP:(网页不存在)";
		break;
	case 503:
		str_back = "HTTP:(服务不可用)";
		break;

	default:
		str_back = "HTTP:ERROR!";
		break;
	}

	return str_back;
}
