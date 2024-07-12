#include "My_Thread.h"

// 时钟线程
// 创建恢复WIFI链接
Thread reflash_OpenWifi = Thread();
// 创建时间更新函数线程
Thread reflash_Time = Thread();
// 创建副标题切换线程
Thread reflash_Banner = Thread();
// 创建动画绘制线程
Thread reflash_Animate = Thread();
// 联网后所有需要更新的数据
Thread reflash_Wifi = Thread();
// 创建协程池
StaticThreadController<4> controller(&reflash_OpenWifi, &reflash_Time, &reflash_Banner, &reflash_Animate);

/// @brief 线程任务初始化
void Thread_Init()
{
	// 时钟线程
	reflash_OpenWifi.onRun(open_Wifi);					  // 联网
	reflash_OpenWifi.setInterval(Weater_time * 60 * TMS); // 设置所需间隔 10分钟

	reflash_Time.onRun(reflashTime); // 更新时间
	reflash_Time.setInterval(300);	 // 设置所需间隔 100毫秒

	reflash_Banner.onRun(reflashBanner); // 切换天气 or 空气质量
	reflash_Banner.setInterval(2 * TMS); // 设置所需间隔 2秒

	reflash_Animate.onRun(refresh_AnimatedImage); // 动画显示
	reflash_Animate.setInterval(TMS / 10);		  // 设置帧率

	controller.run(); // 检查每个线程是否应该运行，如果是运行它
}

/// @brief  更新时间
void reflashTime()
{
	digitalClockDisplay();
	prevTime = 0;
}

/// @brief 天气滚动文本
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
			TJpgDec.drawJpg(160, 160, Animate_value, Animate_size);
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
		controller.setInterval(300); // 设置线程的间隔
	}
}
