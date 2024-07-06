#include "My_WIFI.h"

WiFiManager wm; // 建立 WiFiManager 对象，自动配网使用

// wifi连接 UDP 设置参数
WiFiUDP Udp = WiFiUDP();
uint16_t localPort = 8000; // 侦听的本地端口号

// wifi 名称密码
config_type wificonf = {{"TP-LINK_8ACF"}, {"zh111111"}};

/// @brief Wifi 初始化
void Wifi_Init()
{
	Read_WifiConfig(wificonf); // 读取存储的 wifi 信息

	Serial.print("connect WIFI ");
	Serial.println(wificonf.stassid);

	WiFi.begin(wificonf.stassid, wificonf.stapsw);

	while (WiFi.status() != WL_CONNECTED) // 没连上
	{
		loading(30);

		if (loadNum >= (TFT_WIDTH - 4) - 6)
		{
			TFT_Close(); // 清屏
#if WM_EN
			Web_Show();	 // 配网显示
			Webconfig(); // 配网
#elif !WM_EN
			SmartConfig(); // 微信配网函数
#endif
			break;
		}
	}
	delay(10);

	while (loadNum < (TFT_WIDTH - 4) - 6) // 让动画走完
		loading(1);

	if (WiFi.status() == WL_CONNECTED) // 配网成功
	{
		Serial.print("SSID:");
		Serial.println(WiFi.SSID().c_str());
		Serial.print("PSW:");
		Serial.println(WiFi.psk().c_str());
		strcpy(wificonf.stassid, WiFi.SSID().c_str()); // 名称复制
		strcpy(wificonf.stapsw, WiFi.psk().c_str());   // 密码复制
		Write_WifiConfig(wificonf);					   // 存储 wifi 信息
		Read_WifiConfig(wificonf);					   // 读取存储的 wifi 信息
	}

	Serial.print("IP: ");
	Serial.println(WiFi.localIP());

	Serial.println("Start UDP");
	Udp.begin(localPort); // 初始化 WiFiUDP 库和网络设置，启动 WiFiUDP 套接字，侦听指定的本地端口

	Serial.println("Wait for synchronization..."); // 等待同步
	setSyncProvider(getNtpTime);				   // 同步时间
	setSyncInterval(300);						   // 5 分钟同步一次（5*60）
}

/// @brief 打开 Wifi
void open_Wifi()
{
	Serial.println("Open WIFI...");
	// WiFi.forceSleepWake();
	Wifi_en = 1;
}

/// @brief Wifi 休眠
void colse_Wifi()
{
	Serial.println("Close WIFI...");
	// WiFi.forceSleepBegin();
	Wifi_en = 0;
}

/// @brief 重置 Wifi
/// @param btn 按键
void Wifi_Reset(Button2 &btn)
{
	wm.resetSettings();	 // 清除 ESP 存储的 WiFi 连接信息
	Delete_WifiConfig(); // 删除信息
	delay(10);
	Serial.println("Config WiFi Succeed!");
	ESP.restart(); // esp 重启
}

/// @brief EEPROM 写入 ssid，psw
/// @param wificonf Wifi 结构体
void Write_WifiConfig(config_type wificonf)
{
	uint8_t *p = (uint8_t *)(&wificonf);
	for (uint16_t i = 0; i < sizeof(wificonf); i++)
	{
		EEPROM.write(i + Wifi_addr, *(p + i)); // 在闪存内模拟写入
	}
	delay(10);
	EEPROM.commit(); // 执行写入ROM
	delay(10);

	Serial.println("EEPROM Write WiFi Config...");
}

/// @brief EEPROM 读取 ssid，psw
/// @param wificonf Wifi 结构体
void Read_WifiConfig(config_type wificonf)
{
	uint8_t *p = (uint8_t *)(&wificonf);

	for (uint16_t i = 0; i < sizeof(wificonf); i++)
	{
		*(p + i) = EEPROM.read(i + Wifi_addr);
	}

	Serial.println("EEPROM Read WiFi Config...");
	Serial.printf("SSID:%s\r\n", wificonf.stassid);
	Serial.printf("PSW:%s\r\n", wificonf.stapsw);
	Serial.println("Connecting...");
}

/// @brief EEPROM 删除 ssid，psw
void Delete_WifiConfig()
{
	config_type delete_wifi = {{""}, {""}};
	uint8_t *p = (uint8_t *)(&delete_wifi);

	for (uint16_t i = 0; i < sizeof(delete_wifi); i++)
	{
		EEPROM.write(i + Wifi_addr, *(p + i)); // 在闪存内模拟写入
	}
	delay(10);
	EEPROM.commit(); // 执行写入ROM
	delay(10);

	Serial.println("EEPROM Delete WiFi Config...");
}

/// @brief WEB 配网
void Webconfig()
{
	bool res; // Wifi 连接标志位

	WiFi.mode(WIFI_STA);
	delay(2000);

	wm.resetSettings(); // 清除 ESP 存储的 WiFi 连接信息

	// 创建可添加到 WiFiManager 设置页面的自定义参数
	// 一行
	WiFiManagerParameter p_lineBreak_notext("<p></p>");
	// 城市代码
	WiFiManagerParameter custom_cc("CityCode", "城市代码", "0", 9);
	// 屏幕亮度
	WiFiManagerParameter custom_bl("LCDBL", "屏幕亮度（1-100）", "10", 3);
	// 刷新时间
	WiFiManagerParameter custom_weatertime("WeaterUpdateTime", "天气刷新时间（分钟）", "10", 3);
	// USB 自定义输入字段
	const char *set_rotation = "<br/><label for='set_rotation'>显示方向设置</label><br>\
                              <input type='radio' name='set_rotation' value='0' checked> USB接口朝下<br>\
                              <input type='radio' name='set_rotation' value='1'> USB接口朝右<br>\
                              <input type='radio' name='set_rotation' value='2'> USB接口朝上<br>\
                              <input type='radio' name='set_rotation' value='3'> USB接口朝左<br>";
	WiFiManagerParameter custom_rot(set_rotation);
	// 生日
	WiFiManagerParameter custom_bir("birthday", "生日", "0", 8);
#if DHT_EN
	// DHT11使能
	WiFiManagerParameter custom_DHT11_en("DHT11_en", "Enable DHT11 sensor", "0", 1);
#endif

	// 显示到网页
	wm.addParameter(&p_lineBreak_notext);
	wm.addParameter(&custom_cc);
	wm.addParameter(&p_lineBreak_notext);
	wm.addParameter(&custom_bl);
	wm.addParameter(&p_lineBreak_notext);
	wm.addParameter(&custom_weatertime);
	wm.addParameter(&p_lineBreak_notext);
	wm.addParameter(&custom_rot);
	wm.addParameter(&p_lineBreak_notext);
	wm.addParameter(&custom_bir);
#if DHT_EN
	wm.addParameter(&p_lineBreak_notext);
	wm.addParameter(&custom_DHT11_en);
#endif

	// 设置回调参数保存获取数据
	wm.setSaveParamsCallback(save_WebData);

	// 通过数组或矢量自定义菜单
	std::vector<const char *> menu = {"wifi", "restart"};
	wm.setMenu(menu);

	// 设置黑暗主题
	wm.setClass("invert");

	// Wifi 扫描设置
	wm.setMinimumSignalQuality(20); // 设置扫描显示的最小百分比，null = 8%

	res = wm.autoConnect(My_AP); // 自定义 AP
	// res = wm.autoConnect(); // 自动从芯片生成 AP 名称
	// res = wm.autoConnect("YQY_AP","1122334455"); // 密码保护 AP

	while (!res)
		;
}

/// @brief 从服务器读取参数，用于自定义 html 输入
/// @param name 对应参数名字
/// @return 获取的参数
String getParam(String name)
{
	String value;
	if (wm.server->hasArg(name))
	{
		value = wm.server->arg(name);
	}
	return value;
}

/// @brief 将从页面中获取的数据保存
void save_WebData()
{
	int CCODE = 0, cc; // 城市代码转换量

	// 城市代码
	cc = getParam("CityCode").toInt();
	if (((cc >= 101000000) && (cc <= 102000000)) || (cc == 0))
	{
		for (int cnum = 0; cnum < 5; cnum++)
		{
			EEPROM.write(CC_addr + cnum, cc % 100); // 城市地址写入城市代码
			EEPROM.commit();						// 保存更改的数据
			cc = cc / 100;
			delay(5);
		}
		for (int cnum = 5; cnum > 0; cnum--)
		{
			CCODE = CCODE * 100;
			CCODE += EEPROM.read(CC_addr + cnum - 1);
			delay(5);
		}
		cityCode = CCODE;
	}

	// 屏幕亮度
	LCD_BL_PWM = getParam("LCDBL").toInt();
	if (EEPROM.read(BL_addr) != LCD_BL_PWM)
	{
		analogWrite(TFT_BL, 1023 - (LCD_BL_PWM * 10));
		EEPROM.write(BL_addr, LCD_BL_PWM);
		EEPROM.commit();
		delay(5);
	}

	// 天气刷新 time
	Weater_time = getParam("WeaterUpdateTime").toInt();

	// 屏幕方向
	LCD_Rotation = getParam("set_rotation").toInt();
	if (EEPROM.read(Ro_addr) != LCD_Rotation)
	{
		EEPROM.write(Ro_addr, LCD_Rotation);
		EEPROM.commit(); // 保存更改的数据
		delay(5);
	}
	tft.setRotation(LCD_Rotation);
	tft.fillScreen(BAKCGROUND_COLOR);

	Web_Show();
	loadNum--;
	loading(1);

#if DHT_EN
	// DHT11
	DHT_flag = getParam("DHT11_en").toInt();
	if (EEPROM.read(DHT_addr) != DHT_flag)
	{
		EEPROM.write(DHT_addr, DHT_flag);
		EEPROM.commit(); // 保存更改的数据
		delay(5);
	}
#endif

	Serial.println("[CALLBACK] save_WebData fired"); // save_WebData 触发
	Serial.println("PARAM CityCode = " + cityCode);
	Serial.printf("PARAM LCD Bright = %d\r\n", LCD_BL_PWM);
	Serial.printf("PARAM Weater_Time = %d\r\n", Weater_time);
	Serial.printf("PARAM LCD Direction = %d\r\n", LCD_Rotation);
	Serial.printf("PARAM DHT11_en = %d\r\n", DHT_flag);
}

/// @brief 所有需要联网后更新的方法都放在这里
void WIFI_reflash_All()
{
	if (Wifi_en == 1)
	{
		if (WiFi.status() == WL_CONNECTED)
		{
			Serial.println("WIFI connected");

			getCityWeater(); // 获取城市天气

			getNtpTime(); // 取网络时间

			// 其他需要联网的方法写在后面

			Serial.println("WIFI sleep......");
			Wifi_en = 0;
		}
		else
		{
			Serial.println("WIFI unconnected!!!");
			// goto_missu_page("wifi unconnected", TFT_RED);
		}
	}
}
