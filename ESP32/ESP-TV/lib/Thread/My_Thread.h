#ifndef __MY_THREAD_H
#define __MY_THREAD_H

#include <Thread.h>					//协程
#include <StaticThreadController.h> //协程控制

#include "config.h"
#include "My_wifi.h"

void Thread_Init();			  // 线程任务初始化
void reflashTime();			  // 更新时间
void reflashBanner();		  // 切换天气 or 空气质量
void refresh_AnimatedImage(); // 动画显示
void refresh_loveImage();	  // 动画显示
void Supervisor_controller(); // 守护线程池

#endif
