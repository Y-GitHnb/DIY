#include "My_getHTTP.h"

// wifi 连接 UDP 设置参数
WiFiClient wificlient = WiFiClient();

// mqtt参数
PubSubClient mqttClient = PubSubClient(wificlient);
const char *mqtt_server = MQTT_IP;

// NTP 服务器参数
static const char ntpServerName[] = "ntp6.aliyun.com";
const int timeZone = 8; // 东八区

#define NTP_PACKET_SIZE 48			// NTP 时间在消息的前 48 字节中
byte packetBuffer[NTP_PACKET_SIZE]; // 保存传入和传出数据包的缓冲区

/// @brief HTTP 错误请求
/// @param num HTTP 返回代码
/// @return 错误类型
String HTTP_Error(int num)
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

// ------------------------------------------------------------------------------------------------------------------------
/**
 * 初始化
 */

/// @brief 获取城市代码
void get_City()
{
	int CityCODE = 0;
	for (int cnum = 5; cnum > 0; cnum--)
	{
		CityCODE = CityCODE * 100;
		CityCODE += EEPROM.read(CC_addr + cnum - 1);
		delay(5);
	}
	if (CityCODE >= 101000000 && CityCODE <= 102000000)
		cityCode = CityCODE;
	else
		getCityCode(); // 获取城市代码
}

// ------------------------------------------------------------------------------------------------------------------------
/**
 * 获取天气
 */

/// @brief 获取城市代码
void getCityCode()
{
	String URL = "http://wgeo.weather.com.cn/ip/?_=" + String(now());

	// 创建 HTTPClient 对象
	HTTPClient httpClient;
	// 配置请求地址
	httpClient.begin(wificlient, URL);
	// 设置代理
	httpClient.setUserAgent("Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1");
	// 请求方式
	httpClient.addHeader("Referer", "http://www.weather.com.cn/");

	// 启动连接并发送 HTTP 请求
	int httpCode = httpClient.GET();
	Serial.print("(Request) Send GET request: ");
	Serial.println(URL);

	// 如果服务器响应OK则从服务器获取响应体信息并通过串口输出
	if (httpCode == HTTP_CODE_OK)
	{
		String str = httpClient.getString();

		int aa = str.indexOf("id=");
		if (aa > -1)
		{
			cityCode = str.substring(aa + 4, aa + 4 + 9);
			Serial.println("(Answer) Acquire Success...");
			Serial.println(cityCode);

			getCityWeater();
		}
		else
		{
			Serial.println("(Answer) Fail to get!");
		}
	}
	else
	{
		String error = HTTP_Error(httpCode);
		Serial.println("(Answer) Fetch Error: " + error);
	}

	// 关闭服务器连接
	httpClient.end();
}

/// @brief 获取城市天气
void getCityWeater()
{
	String URL = "http://d1.weather.com.cn/weather_index/" + cityCode + ".html?_=" + String(now()); // 原来
	// String URL = "http://d1.weather.com.cn/dingzhi/" + cityCode + ".html?_="+String(now());	// 新

	// 创建 HTTPClient 对象
	HTTPClient httpClient;
	// 配置请求地址
	httpClient.begin(wificlient, URL); // httpClient.begin(URL);
	// 设置代理
	httpClient.setUserAgent("Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1");
	// 请求方式
	httpClient.addHeader("Referer", "http://www.weather.com.cn/");

	// 启动连接并发送 HTTP 请求
	int httpCode = httpClient.GET();
	Serial.println("(Request) Getting weather data...");
	Serial.println(URL);

	// 如果服务器响应OK则从服务器获取响应体信息并通过串口输出
	if (httpCode == HTTP_CODE_OK)
	{
		String str = httpClient.getString();

		int indexStart = str.indexOf("weatherinfo\":");
		int indexEnd = str.indexOf("};var alarmDZ");

		weather_msg.cityDZ = str.substring(indexStart + 13, indexEnd);

		indexStart = str.indexOf("dataSK =");
		indexEnd = str.indexOf(";var dataZS");
		weather_msg.dataSK = str.substring(indexStart + 8, indexEnd);

		indexStart = str.indexOf("\"f\":[");
		indexEnd = str.indexOf(",{\"fa");
		weather_msg.dataFC = str.substring(indexStart + 5, indexEnd);

		weater_Show(&(weather_msg.cityDZ), &(weather_msg.dataSK), &(weather_msg.dataFC));
		Serial.println("(Answer) Acquire Success...");

		httpClient.end(); // 关闭服务器连接
	}
	else
	{
		String error = HTTP_Error(httpCode);
		Serial.println("(Answer) Fetch Error: " + error);
	}
}

// ------------------------------------------------------------------------------------------------------------------------
/**
 * 获取时间
 */

/// @brief 向NTP服务器发送请求
/// @param address 服务器 ip 地址
void sendNTPpacket(IPAddress &address)
{
	memset(packetBuffer, 0, NTP_PACKET_SIZE); // 清空缓冲区

	// 初始化NTP请求所需的值
	packetBuffer[0] = 0b11100011; // 版本，模式
	packetBuffer[1] = 0;		  // 时钟类型
	packetBuffer[2] = 6;		  // 轮询间隔
	packetBuffer[3] = 0xEC;		  // 对端时钟精度

	// 根延迟和根分散为8字节零

	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// 发送请求时间戳的数据包
	Udp.beginPacket(address, 123);			  // 构建数据包，准备发送到指定 ip 和端口的远程主机(NTP 请求发送到端口 123)
	Udp.write(packetBuffer, NTP_PACKET_SIZE); // 将缓冲区中指定数目的字节数，写入UDP数据包
	Udp.endPacket();						  // 写入UDP数据后，完成数据找包并发送
}

/// @brief  通过 NTP 协议获取网络时间
/// @return 返回计算时间
time_t getNtpTime()
{
	IPAddress ntpServerIP; // NTP 服务器 ip 地址

	while (true)
	{
		// 丢弃所有先前收到的数据包,从池中获取一个随机服务器
		while (Udp.parsePacket() > 0) // 开始处理下一个可用的传入数据包
			;

		WiFi.hostByName(ntpServerName, ntpServerIP); // 将给定的主机名解析为IP地址

		sendNTPpacket(ntpServerIP); // 向NTP服务器发送请求

		uint32_t beginWait = millis();
		while (millis() - beginWait < 1500)
		{
			int size = Udp.parsePacket();

			if (size >= NTP_PACKET_SIZE)
			{
				Serial.println("(Answer) Receive NTP Response..."); // 接收NTP响应
				Udp.read(packetBuffer, NTP_PACKET_SIZE);			// 将数据包读入缓冲区

				// 将从位置40开始的四个字节转换为长整数
				unsigned long secsSince1900;
				secsSince1900 = (unsigned long)packetBuffer[40] << 24;
				secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
				secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
				secsSince1900 |= (unsigned long)packetBuffer[43];

				return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
			}
		}

		Serial.println("(Answer) No NTP Response :-("); // 无响应
	}
}
