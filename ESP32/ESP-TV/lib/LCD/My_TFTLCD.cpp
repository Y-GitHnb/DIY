#include "My_TFTLCD.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);

WeatherNum wrat; // 天气图标

byte loadNum = 6; // 进度条进度

// ----------------------------------------------------------------------------------------------------------------------
/**
 * 初始化部分
 */

/// @brief TFT屏幕输出函数
/// @param x	x
/// @param y	y
/// @param w	w
/// @param h	h
/// @param bitmap	绘制数组
/// @return		01
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
	if (y >= tft.height())
		return 0;

	tft.pushImage(x, y, w, h, bitmap);

	// Return 1 to decode next block
	return 1;
}

/// @brief TFT 初始化
void TFT_Init()
{
	// 从 EEPROM 读取背光亮度
	if (EEPROM.read(BL_addr) > 0 && EEPROM.read(BL_addr) < 100)
		LCD_BL_PWM = EEPROM.read(BL_addr);
	pinMode(TFT_BL, OUTPUT);
	analogWrite(TFT_BL, (LCD_BL_PWM * 10));

	// 从 EEPROM 读取屏幕方向
	if (EEPROM.read(Ro_addr) >= 0 && EEPROM.read(Ro_addr) <= 3)
		LCD_Rotation = EEPROM.read(Ro_addr);

	tft.begin();								   // 初始化TFT
	tft.invertDisplay(1);						   // 反转所有显示颜色：1反转，0正常
	tft.setRotation(LCD_Rotation);				   // 设置屏幕显示的旋转角度，参数为：0, 1, 2, 3  分别代表 0°、90°、180°、270°
	tft.fillScreen(BAKCGROUND_COLOR);			   // 颜色填充
	tft.setTextColor(PEN_COLOR, BAKCGROUND_COLOR); // 设置笔色

	Serial.println("(Init) TFTLCD_Init...");
	Serial.printf("(Configuration) LCD Brigh: %d\r\n", LCD_BL_PWM);
	Serial.printf("(Configuration) LCD Direction: %d\r\n", LCD_Rotation);
}

/// @brief 图片解码库初始化
void TJpgDec_Init()
{
	TJpgDec.setJpgScale(1); // 设置缩小比例因子（1 2 4 8）
	TJpgDec.setSwapBytes(true);
	TJpgDec.setCallback(tft_output); // 回调函数

	Serial.println("(Init) TJpgDec Init...");
}

/// @brief 清屏
void TFT_Close()
{
	tft.fillScreen(TFT_BLACK);
}

// ----------------------------------------------------------------------------------------------------------------------
/**
 * Wifi 部分
 */

/// @brief  绘制 WIFI 进度条
/// @param delayTime 当前进度延时时间
void loading(byte delayTime, char stassid[])
{
	const char *wifi_name = stassid;

	clk.setColorDepth(8);											  // 设置颜色像素位数（1 4 8 16）
	clk.createSprite(TFT_WIDTH - 40, 100);							  // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);								  // 填充
	clk.loadFont(My_Font);											  // 加载显示的字体（自制的字库）
	clk.setTextDatum(CC_DATUM);										  // 设置文本位置参考基准, CC_DATUM 设置为上下左右居中
	clk.drawRoundRect(0, 0, TFT_WIDTH - 40, 16, 8, TFT_WHITE);		  // 空心圆角矩形
	clk.fillRoundRect(3, 3, loadNum, 10, 5, PEN_COLOR);				  // 实心圆角矩形
	clk.setTextColor(TFT_GREEN, BAKCGROUND_COLOR);					  // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString("连接 WiFi 中.....", (TFT_WIDTH - 40) / 2, 40, 2); // 指定文字显示在画布的指定位置
	clk.setTextColor(TFT_RED, BAKCGROUND_COLOR);
	clk.drawRightString(wifi_name, 180, 60, 2);
	clk.pushSprite(20, 120); // 将画图推送至屏幕的指定位置
	clk.deleteSprite();		 // 删除画布
	clk.unloadFont();		 // 卸载字体，释放资源（RAM）

	loadNum += 1;
	delay(delayTime);
}

/// @brief WEB 配网显示函数
void Web_Show()
{
	clk.setColorDepth(8);										   // 设置颜色像素位数（1 4 8 16）
	clk.createSprite(TFT_WIDTH - 40, 90);						   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);							   // 填充
	clk.loadFont(My_Font);										   // 加载显示的字体（自制的字库）
	clk.setTextDatum(CC_DATUM);									   // 设置文本数据
	clk.setTextColor(TFT_RED, BAKCGROUND_COLOR);				   // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString("WiFi 连接失败!", (TFT_WIDTH - 40) / 2, 10, 2); // 指定文字显示在画布的指定位置
	clk.drawString("请自行连接:", (TFT_WIDTH - 40) / 2, 40, 2);
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR);
	clk.drawString("SSID:", 45, 70, 2);
	clk.setTextColor(PEN_COLOR, BAKCGROUND_COLOR);
	clk.drawString(My_AP, 125, 70, 2);
	clk.pushSprite(20, 50); // 窗口位置
	clk.deleteSprite();		// 删除画布
	clk.unloadFont();		// 卸载字体，释放资源（RAM）
}

// ----------------------------------------------------------------------------------------------------------------------
/**
 * 天气 部分
 */

/// @brief 显示温湿度图片
void Show_WS()
{
	TJpgDec.drawJpg(15, 183, temperature_20X20, sizeof(temperature_20X20)); // 温度图标
	TJpgDec.drawJpg(15, 213, humidity_20X20, sizeof(humidity_20X20));		// 湿度图标
}

/// @brief 显示天气滚动文本
void scrollBanner()
{
	if (scrollText[text_Index])
	{
		clk.setColorDepth(8);							// 设置颜色像素位数（1 4 8 16）
		clk.loadFont(My_Font);							// 加载显示的字体（自制的字库）
		clk.createSprite(150, 30);						// 创建窗口
		clk.fillSprite(BAKCGROUND_COLOR);				// 填充
		clk.setTextWrap(false, false);					// 文本是否行尾换行
		clk.setTextDatum(CC_DATUM);						// 设置文本数据
		clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR);	// 设置字体显示区域的颜色，含背景颜色和字体颜色
		clk.drawString(scrollText[text_Index], 74, 16); // 指定文字显示在画布的指定位置
		clk.pushSprite(10, 45);							// 窗口位置
		clk.deleteSprite();								// 删除画布
		clk.unloadFont();								// 卸载字体，释放资源

		if (text_Index >= 5)
			text_Index = 0; // 回第一个
		else
			text_Index += 1; // 准备切换到下一个
	}
	prevTime = 1;
}

// 温度图标显示函数
void Show_Win()
{
	clk.setColorDepth(8);
	clk.createSprite(52, 6);						 // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);				 // 填充率
	clk.drawRoundRect(0, 0, 52, 6, 3, TFT_WHITE);	 // 空心圆角矩形  起始位x,y,长度，宽度，圆弧半径，颜色
	clk.fillRoundRect(1, 1, tempnum, 4, 2, tempcol); // 实心圆角矩形
	clk.pushSprite(45, 192);						 // 窗口位置
	clk.deleteSprite();
}

// 湿度图标显示函数
void Show_Shi()
{
	huminum = huminum / 2;

	clk.setColorDepth(8);
	clk.createSprite(52, 6);						 // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);				 // 填充率
	clk.drawRoundRect(0, 0, 52, 6, 3, TFT_WHITE);	 // 空心圆角矩形  起始位x,y,长度，宽度，圆弧半径，颜色
	clk.fillRoundRect(1, 1, huminum, 4, 2, humicol); // 实心圆角矩形
	clk.pushSprite(45, 222);						 // 窗口位置
	clk.deleteSprite();
}

/// @brief 天气信息写到屏幕上
/// @param cityDZ
/// @param dataSK
/// @param dataFC
void weater_Show(String *cityDZ, String *dataSK, String *dataFC)
{
	// -------------------------------------------------------------------------------------------------------------------
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, *dataSK);
	JsonObject sk = doc.as<JsonObject>();

	clk.setColorDepth(8);  // 设置颜色像素位数（1 4 8 16）
	clk.loadFont(My_Font); // 加载显示的字体（自制的字库）

	// 温度
	clk.createSprite(58, 24);							   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);					   // 填充
	clk.setTextDatum(CC_DATUM);							   // 设置文本数据
	clk.setTextColor(PEN_COLOR, BAKCGROUND_COLOR);		   // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(sk["temp"].as<String>() + "℃", 28, 13); // 指定文字显示在画布的指定位置
	clk.pushSprite(100, 184);							   // 窗口位置
	clk.deleteSprite();									   // 删除画布

	// 更新颜色
	tempnum = sk["temp"].as<int>() + 10;
	if (tempnum < 10)
		tempcol = 0x00FF;
	else if (tempnum < 28)
		tempcol = 0x0AFF;
	else if (tempnum < 34)
		tempcol = 0x0F0F;
	else if (tempnum < 41)
		tempcol = 0xFF0F;
	else if (tempnum < 49)
		tempcol = 0xF00F;
	else
	{
		tempcol = 0xF00F;
		tempnum = 50;
	}
	Show_Win();

	// 湿度
	clk.createSprite(58, 24);					   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);			   // 填充
	clk.setTextDatum(CC_DATUM);					   // 设置文本数据
	clk.setTextColor(PEN_COLOR, BAKCGROUND_COLOR); // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(sk["SD"].as<String>(), 28, 13); // 指定文字显示在画布的指定位置
	clk.pushSprite(100, 214);					   // 窗口位置
	clk.deleteSprite();							   // 删除画布

	// 更新颜色
	huminum = atoi((sk["SD"].as<String>()).substring(0, 2).c_str());
	if (huminum > 90)
		humicol = 0x00FF;
	else if (huminum > 70)
		humicol = 0x0AFF;
	else if (huminum > 40)
		humicol = 0x0F0F;
	else if (huminum > 20)
		humicol = 0xFF0F;
	else
		humicol = 0xF00F;
	Show_Shi();

	// 城市名称
	clk.createSprite(94, 30);							 // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);					 // 填充
	clk.setTextDatum(CC_DATUM);							 // 设置文本数据
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR);		 // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(sk["cityname"].as<String>(), 44, 16); // 指定文字显示在画布的指定位置
	clk.pushSprite(15, 15);								 // 窗口位置
	clk.deleteSprite();									 // 删除画布

	// PM2.5空气指数
	int pm25V = sk["aqi"];										 // 数值
	String aqiTxt = "优";										 // 质量显示
	uint16_t pm25BAKCGROUND_COLOR = tft.color565(156, 202, 127); // 颜色显示	// 优

	if (pm25V > 200)
	{
		pm25BAKCGROUND_COLOR = tft.color565(136, 11, 32); // 重度
		aqiTxt = "重度";
	}
	else if (pm25V > 150)
	{
		pm25BAKCGROUND_COLOR = tft.color565(186, 55, 121); // 中度
		aqiTxt = "中度";
	}
	else if (pm25V > 100)
	{
		pm25BAKCGROUND_COLOR = tft.color565(242, 159, 57); // 轻
		aqiTxt = "轻度";
	}
	else if (pm25V > 50)
	{
		pm25BAKCGROUND_COLOR = tft.color565(247, 219, 100); // 良
		aqiTxt = "良";
	}

	clk.createSprite(56, 24);								  // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);						  // 填充
	clk.fillRoundRect(0, 0, 50, 24, 4, pm25BAKCGROUND_COLOR); // 实心圆角矩形
	clk.setTextDatum(CC_DATUM);								  // 设置文本数据
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR);			  // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(aqiTxt, 25, 13);							  // 指定文字显示在画布的指定位置
	clk.pushSprite(104, 18);								  // 窗口位置
	clk.deleteSprite();										  // 删除画布

	// 滚动字幕
	scrollText[0] = "实时天气 " + sk["weather"].as<String>();
	scrollText[1] = "空气质量 " + aqiTxt;
	scrollText[2] = "风向 " + sk["WD"].as<String>() + sk["WS"].as<String>();

	// 天气图标
	wrat.printfweather(170, 15, atoi((sk["weathercode"].as<String>()).substring(1, 3).c_str()));

	// -------------------------------------------------------------------------------------------------------------------

	// 左上角滚动字幕
	deserializeJson(doc, *cityDZ);
	JsonObject dz = doc.as<JsonObject>();

	scrollText[3] = "今日" + dz["weather"].as<String>();

	// -------------------------------------------------------------------------------------------------------------------

	deserializeJson(doc, *dataFC);
	JsonObject fc = doc.as<JsonObject>();

	scrollText[4] = "最低温度" + fc["fd"].as<String>() + "℃";
	scrollText[5] = "最高温度" + fc["fc"].as<String>() + "℃";

	clk.unloadFont(); // 卸载字体，释放资源（RAM）
}

// ----------------------------------------------------------------------------------------------------------------------
/**
 * 时间 部分
 */

/// @brief 用快速线方法绘制数字
/// @param _x x位置
/// @param _y y位置
/// @param _num
/// @param _size 字号
/// @param _color 颜色
void drawLineFont(uint32_t _x, uint32_t _y, uint32_t _num, uint32_t _size, uint32_t _color)
{
	uint32_t fontSize;
	const LineAtom *fontOne;

	// 小号(9*14)
	if (_size == 1)
	{
		fontOne = smallLineFont[_num];
		fontSize = smallLineFont_size[_num];
		tft.fillRect(_x, _y, 9, 14, BAKCGROUND_COLOR); // 绘制前清理字体绘制区域
	}
	// 中号(18*30)
	else if (_size == 2)
	{
		fontOne = middleLineFont[_num];
		fontSize = middleLineFont_size[_num];
		tft.fillRect(_x, _y, 18, 30, BAKCGROUND_COLOR); // 绘制前清理字体绘制区域
	}
	// 大号(36*90)
	else if (_size == 3)
	{
		fontOne = largeLineFont[_num];
		fontSize = largeLineFont_size[_num];
		tft.fillRect(_x, _y, 36, 90, BAKCGROUND_COLOR); // 绘制前清理字体绘制区域
	}
	else
		return;

	for (uint32_t i = 0; i < fontSize; i++)
	{
		tft.drawFastHLine(fontOne[i].xValue + _x, fontOne[i].yValue + _y, fontOne[i].lValue, _color);
	}
}

/// @brief 日期刷新(快速划线)
/// @param reflash_en	输入参数, 输入1强制刷新
void digitalClockDisplay(int reflash_en)
{
	// 时钟刷新
	int now_hour = hour();	   // 获取小时
	int now_minute = minute(); // 获取分钟
	int now_second = second(); // 获取秒针

	// 小时刷新
	if ((now_hour != Hour_sign) || (reflash_en == 1))
	{
		drawLineFont(20, timeY, now_hour / 10, 3, TFT_WHITE);
		drawLineFont(60, timeY, now_hour % 10, 3, TFT_WHITE);
		Hour_sign = now_hour;
	}

	// 分钟刷新
	if ((now_minute != Minute_sign) || (reflash_en == 1))
	{
		drawLineFont(101, timeY, now_minute / 10, 3, TFT_GREENYELLOW);
		drawLineFont(141, timeY, now_minute % 10, 3, TFT_GREENYELLOW);
		Minute_sign = now_minute;
	}

	// 秒针刷新
	if ((now_second != Second_sign) || (reflash_en == 1)) // 分钟刷新
	{
		drawLineFont(182, timeY + 30, now_second / 10, 2, TFT_WHITE);
		drawLineFont(202, timeY + 30, now_second % 10, 2, TFT_WHITE);
		Second_sign = now_second;
	}

	if (reflash_en == 1)
		reflash_en = 0;

	clk.setColorDepth(8);  // 设置颜色像素位数（1 4 8 16）
	clk.loadFont(My_Font); // 加载显示的字体（自制的字库）

	// 星期
	clk.createSprite(58, 30);					   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);			   // 填充
	clk.setTextDatum(CC_DATUM);					   // 设置文本数据
	clk.setTextColor(PEN_COLOR, BAKCGROUND_COLOR); // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(week(), 29, 16);				   // 指定文字显示在画布的指定位置
	clk.pushSprite(102, 150);					   // 窗口位置
	clk.deleteSprite();							   // 删除画布

	// 月日
	clk.createSprite(95, 30);					   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);			   // 填充
	clk.setTextDatum(CC_DATUM);					   // 设置文本数据
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR); // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(monthDay(), 49, 16);			   // 指定文字显示在画布的指定位置
	clk.pushSprite(5, 150);						   // 窗口位置
	clk.deleteSprite();							   // 删除画布

	clk.unloadFont(); // 卸载字体，释放资源（RAM）
}

// ----------------------------------------------------------------------------------------------------------------------
/**
 * DHT11 部分
 */

/// @brief 外接DHT11传感器，显示数据
void DHT11_Show()
{
	String s = "内温";
	float t = dht.readTemperature(); // 读温度
	float h = dht.readHumidity();	 // 读湿度

	clk.setColorDepth(8);  // 设置颜色像素位数（1 4 8 16）
	clk.loadFont(My_Font); // 加载显示的字体（自制的字库）

	// 内温
	clk.createSprite(58, 30);					   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);			   // 填充
	clk.setTextDatum(CC_DATUM);					   // 设置文本数据
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR); // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawString(s, 29, 16);					   // 指定文字显示在画布的指定位置
	clk.pushSprite(172, 150);					   // 窗口位置
	clk.deleteSprite();							   // 删除画布

	// 温度
	clk.createSprite(60, 24);					   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);			   // 填充
	clk.setTextDatum(CC_DATUM);					   // 设置文本数据
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR); // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawFloat(t, 1, 20, 13);				   // 指定文字显示在画布的指定位置
	clk.drawString("℃", 50, 13);
	//  clk.drawString(sk["temp"].as<String>()+"℃",28,13);
	clk.pushSprite(170, 184); // 窗口位置
	clk.deleteSprite();		  // 删除画布

	// 湿度
	clk.createSprite(60, 24);					   // 创建窗口
	clk.fillSprite(BAKCGROUND_COLOR);			   // 填充
	clk.setTextDatum(CC_DATUM);					   // 设置文本数据
	clk.setTextColor(TFT_WHITE, BAKCGROUND_COLOR); // 设置字体显示区域的颜色，含背景颜色和字体颜色
	clk.drawFloat(h, 1, 20, 13);				   // 指定文字显示在画布的指定位置
	clk.drawString("%", 50, 13);
	// clk.drawString(sk["SD"].as<String>(),28,13);
	// clk.drawString("100%",28,13);
	clk.pushSprite(170, 214); // 窗口位置
	clk.deleteSprite();		  // 删除画布
}

/**
 * 屏幕刷新
 */

/// @brief 强制屏幕刷新
void LCD_reflash()
{
	reflashTime();
	reflashBanner();
	open_Wifi();
}

/// @brief 显示指定字符串
void show_str(const char *string)
{
	clk.setColorDepth(16);							  // 设置颜色像素位数（1 4 8 16）
	clk.createSprite(TFT_WIDTH - 40, 60);			  // 创建指定大小的画布（需小于屏幕的最大尺寸）
	clk.fillSprite(BAKCGROUND_COLOR);				  // 设置画布的填充颜色
	clk.loadFont(My_Font);							  // 加载显示的字体（自制的字库）
	clk.setTextDatum(CC_DATUM);						  // 设置文本位置参考基准, CC_DATUM 设置为上下左右居中
	clk.setTextColor(TFT_RED, BAKCGROUND_COLOR);	  // 设置字体显示区域的颜色，含背景颜色和字体颜色（背景颜色与画布填充颜色一致，不然很丑）
	clk.drawString(string, (TFT_WIDTH - 40) / 2, 30); // 指定文字显示在画布的指定位置
	clk.pushSprite(20, 90);							  // 将画图推送至屏幕的指定位置
	clk.deleteSprite();								  // 删除画布
	clk.unloadFont();								  // 卸载字体，释放资源（RAM）
}

// 用快速线方法绘制数字
void drawLineFontForDay(uint32_t _x, uint32_t _y, uint32_t _num, uint32_t _size, uint32_t _color)
{
	uint32_t fontSize;
	const LineAtom *fontOne;
	fontOne = middleLineFont[_num];
	fontSize = middleLineFont_size[_num];

	// 绘制前清理字体绘制区域  周围填充4像素
	tft.fillRoundRect(_x - 4, _y - 4, 26, 38, 4, TFT_WHITE);

	for (uint32_t i = 0; i < fontSize; i++)
	{
		tft.drawFastHLine(fontOne[i].xValue + _x, fontOne[i].yValue + _y, fontOne[i].lValue, _color);
	}
}
