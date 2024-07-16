#include "task.h"


static uint8_t* buf;
static char oled_buf[64];
static uint8_t run_flag = 0;
static uint8_t flag = 1;



//������
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



// �����߼�
void open_lock(void)
{
    if(run_flag == 1)
    {
        // ����
        OLED_ShowString_fun("Open The Lock");
        while(READ_MOT)
        {
            RELAY_OPEN(1);
            delay_ms(2000);
            RELAY_OPEN(0);
            delay_ms(2000);
        }
        
        
        // ��ʱ
        open_flag = 1;
        while(1)
        {
            if(open_flag == 0)
                break;
            delay_ms(100);
        }
        
        
        // �г�����
        if(car_flag)
        {
            // ��⳵����
            OLED_ShowString_fun("Stop Car");
            while(!READ_HW)
            {
                delay_ms(1000);
                YuanZiYun();
            }
            
            // ��ʱ
            close_flag = 1;
            while(1)
            {
                if(close_flag == 0)
                    break;
                delay_ms(100);
            }
            
            //����
            OLED_ShowString_fun("Car Leave");
            while(!READ_MOT)
            {
                RELAY_CLOSE(1);
                delay_ms(2000);
                RELAY_CLOSE(0);
                delay_ms(2000);
            }
            
            // ���źŵ���
            while(flag)
            {
                printf_usart3("Car Leave");
                
                // �ƽ��յ���������
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
                    
                    usart3_close_flag();    /* �ؿ���ʼ��������ATK-MW8266D UART������ */
                }
                
                delay_ms(1000);
                
                YuanZiYun();
            }
            
            // ���־
            flag = 1;
            car_flag = 0;
            run_flag = 0;
        }
        
        
        //û������
        else
        {
            //����
            OLED_ShowString_fun("NO Car");
            while(!READ_MOT)
            {
                RELAY_CLOSE(1);
                delay_ms(2000);
                RELAY_CLOSE(0);
                delay_ms(2000);
            }
            
            // ���źŵ���
            while(flag)
            {
                printf_usart3("N0 Car");
                
                // �ƽ��յ���������
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
                    
                    usart3_close_flag();    /* �ؿ���ʼ��������ATK-MW8266D UART������ */
                }
                
                delay_ms(1000);
                
                YuanZiYun();
            }
            
            // ���־
            flag = 1;
            run_flag = 0;
        }
    }
    
    
    else
    {
//        OLED_ShowString_fun("enter stop...");
//        Pwr_Stop();     /* ����ֹͣģʽ */
//        
//        /* ��ֹͣģʽ����, ��Ҫ��������ϵͳʱ��, 72Mhz */
//        SystemClock_Config();
        
        YuanZiYun();
    }
    
    
    delay_ms(10);
}


// ESP8266ͨ���߼�
void ESP8266_TASK(void)
{
    ATK_MW8266D_Init();       //ATK-MW8266D��ʼ��
    
    while(1)
    {
        buf = usart3_uart_dat();   /* ��������ATK-MW8266D UART��һ֡���� */
        
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
            
            usart3_close_flag();    /* �ؿ���ʼ��������ATK-MW8266D UART������ */
        }
        
        open_lock();
    }
}


// IMD750ͨ���߼�
void IMD750_TASK(void)
{
    delay_ms(10000);
    
    ATK_IMD750_Init();
    
    while(1)
    {
        buf = usart3_uart_dat();    //��������
        
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
            
            usart3_close_flag();    //�ؿ�����
        }
        
        open_lock();
    }
}
