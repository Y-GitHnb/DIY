#include "My_Thread.h"

// 时钟线程
// 创建时间更新函数线程
Thread reflash_Time = Thread();
// 创建副标题切换线程
Thread reflash_Banner = Thread();
// 创建恢复WIFI链接
Thread reflash_OpenWifi = Thread();
// 创建动画绘制线程
Thread reflash_Animate = Thread();
// 联网后所有需要更新的数据
Thread reflash_Wifi = Thread();
// 创建协程池
StaticThreadController<4> controller(&reflash_Time, &reflash_Banner, &reflash_OpenWifi, &reflash_Animate);

// love线程
// 创建四毛线程
Thread reflash_Love_Animate = Thread();
// 创建
Thread reflash_Love_OpenWifi = Thread();
StaticThreadController<2> controller_love(&reflash_Love_Animate, &reflash_Love_OpenWifi);

// imu线程
Thread reflash_Mqtt = Thread();

/// @brief 线程任务初始化
void Thread_Init()
{
	// 时钟线程
	reflash_Time.onRun(reflashTime); // 更新时间
	reflash_Time.setInterval(300);	 // 设置所需间隔 100毫秒

	reflash_Banner.onRun(reflashBanner); // 切换天气 or 空气质量
	reflash_Banner.setInterval(2 * TMS); // 设置所需间隔 2秒

	reflash_OpenWifi.onRun(open_Wifi);					  // 联网
	reflash_OpenWifi.setInterval(Weater_time * 60 * TMS); // 设置所需间隔 10分钟

	reflash_Animate.onRun(refresh_AnimatedImage); // 动画显示
	reflash_Animate.setInterval(TMS / 10);		  // 设置帧率

	controller.run(); // 检查每个线程是否应该运行，如果是运行它
					  // controller.setInterval(375); // 设置线程的间隔

	// // love线程
	// reflash_Love_Animate.setInterval(TMS / 10);
	// reflash_Love_Animate.onRun(refresh_loveImage);

	// reflash_Love_OpenWifi.setInterval(WORD_UPDATE_TIME * 60 * TMS); // 5分钟刷新情话
	// reflash_Love_OpenWifi.onRun(openWifi);
	// controller_love.run();

	// // 想你页面 mqtt线程
	// reflash_Mqtt.setInterval(2 * TMS); // 设置1秒钟连一次
	// reflash_Mqtt.onRun(mqtt_reconnect);
}

/// @brief  更新时间
void reflashTime()
{
	prevDisplay = now();
	digitalClockDisplay();
	prevTime = 0;
}

/// @brief  切换天气 or 空气质量
void reflashBanner()
{
#if DHT_EN
	if (DHT_flag != 0)
		IndoorTem();
#endif
	scrollBanner();
}

/// @brief 动画显示
void refresh_AnimatedImage()
{
#if Animate_Choice
	if (DHT_flag == 0)
	{
		if (millis() - Amimate_reflash_Time > 100) // x ms切换一次
		{
			Amimate_reflash_Time = millis();
			imgAnim(&Animate_value, &Animate_size);
			TJpgDec.drawJpg(0, 80, Animate_value, Animate_size);
		}
	}
#endif
}

/// @brief 守护线程池
void Supervisor_controller()
{
	if (controller.shouldRun()) // 是否在运行
	{
		controller.run();
	}
}
