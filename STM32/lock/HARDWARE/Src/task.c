#include "task.h"


static uint8_t* buf;
static char oled_buf[64];
static uint8_t run_flag = 0;
static uint8_t flag = 1;



//防断云
void YuanZiYun(void)
{
    if(detection_flag == 1)
    {
        if(atk_mw8266d_at_test() != ATK_MW8266D_EOK)
        {
            ATK_MW8266D_Init();
        }
        
        detection_flag = 0;
    }
}



// 开锁逻辑
void open_lock(void)
{
    if(run_flag == 1)
    {
        // 开锁
        OLED_ShowString_fun("Open The Lock");
        while(READ_MOT)
        {
            RELAY_OPEN(1);
            delay_ms(2000);
            RELAY_OPEN(0);
            delay_ms(2000);
        }
        
        
        // 计时
        open_flag = 1;
        while(1)
        {
            if(open_flag == 0)
                break;
            delay_ms(100);
        }
        
        
        // 有车进来
        if(car_flag)
        {
            // 检测车开走
            OLED_ShowString_fun("Stop Car");
            while(!READ_HW)
            {
                delay_ms(1000);
                YuanZiYun();
            }
            
            // 计时
            close_flag = 1;
            while(1)
            {
                if(close_flag == 0)
                    break;
                delay_ms(100);
            }
            
            //关锁
            OLED_ShowString_fun("Car Leave");
            while(!READ_MOT)
            {
                RELAY_CLOSE(1);
                delay_ms(2000);
                RELAY_CLOSE(0);
                delay_ms(2000);
            }
            
            // 发信号到云
            while(flag)
            {
                printf_usart3("Car Leave");
                
                // 云接收到返回数据
                buf = usart3_uart_dat();
                
                if (buf != NULL)
                {
                    sprintf(oled_buf, "%s", buf);
                    OLED_ShowString_fun(oled_buf);
                    
                    if(!strcmp((char*)buf, "ok"))
                    {
                        printf_usart3("ok");
                        flag = 0;
                    }
                    
                    usart3_close_flag();    /* 重开开始接收来自ATK-MW8266D UART的数据 */
                }
                
                delay_ms(1000);
                
                YuanZiYun();
            }
            
            // 清标志
            flag = 1;
            car_flag = 0;
            run_flag = 0;
        }
        
        
        //没车进来
        else
        {
            //关锁
            OLED_ShowString_fun("NO Car");
            while(!READ_MOT)
            {
                RELAY_CLOSE(1);
                delay_ms(2000);
                RELAY_CLOSE(0);
                delay_ms(2000);
            }
            
            // 发信号到云
            while(flag)
            {
                printf_usart3("N0 Car");
                
                // 云接收到返回数据
                buf = usart3_uart_dat();
                
                if (buf != NULL)
                {
                    sprintf(oled_buf, "%s", buf);
                    OLED_ShowString_fun(oled_buf);
                    
                    if(!strcmp((char*)buf, "ok"))
                    {
                        printf_usart3("ok");
                        flag = 0;
                    }
                    
                    usart3_close_flag();    /* 重开开始接收来自ATK-MW8266D UART的数据 */
                }
                
                delay_ms(1000);
                
                YuanZiYun();
            }
            
            // 清标志
            flag = 1;
            run_flag = 0;
        }
    }
    
    
    else
    {
//        OLED_ShowString_fun("enter stop...");
//        Pwr_Stop();     /* 进入停止模式 */
//        
//        /* 从停止模式唤醒, 需要重新设置系统时钟, 72Mhz */
//        SystemClock_Config();
        
        YuanZiYun();
    }
    
    
    delay_ms(10);
}


// ESP8266通信逻辑
void ESP8266_TASK(void)
{
    ATK_MW8266D_Init();       //ATK-MW8266D初始化
    
    while(1)
    {
        buf = usart3_uart_dat();   /* 接收来自ATK-MW8266D UART的一帧数据 */
        
        if (buf != NULL)
        {
            sprintf(oled_buf, "%s", buf);
            OLED_ShowString_fun(oled_buf);
            
            if(!strcmp((char*)buf, "open"))
            {
                run_flag = 1;
            }
            
            if(!strcmp((char*)buf, "close"))
            {
                run_flag = 0;
            }
            
            usart3_close_flag();    /* 重开开始接收来自ATK-MW8266D UART的数据 */
        }
        
        open_lock();
    }
}


// IMD750通信逻辑
void IMD750_TASK(void)
{
    delay_ms(10000);
    
    ATK_IMD750_Init();
    
    while(1)
    {
        buf = usart3_uart_dat();    //接收数据
        
        if (buf != NULL)
        {
            sprintf(oled_buf, "%s", buf);
            OLED_ShowString_fun(oled_buf);
            
            if(!strcmp((char*)buf, "open"))
            {
                run_flag = 1;
            }
            
            if(!strcmp((char*)buf, "close"))
            {
                run_flag = 0;
            }
            
            usart3_close_flag();    //重开接收
        }
        
        open_lock();
    }
}
