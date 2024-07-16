#ifndef __OLED_H__
#define __OLED_H__


#include "i2c.h"
#include "oled_ZK.h"


#define OLED_W   127
#define OLED_H   7


/* OLED控制用函数 */
void OLED_Set_Pos(uint8_t x, uint8_t y);    //OLED设置显示位置
void OLED_Display_On(void);                 //OLED开启显示
void OLED_Display_Off(void);                //OLED关闭显示
void OLED_Clear(void);                      //OLED清屏函数
void OLED_On(void);                         //OLED显示全开


/* OLED功能函数 */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);               //在指定位置显示一个ASCII字符
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);   //在指定位置显示一个整数
void OLED_ShowString(uint8_t x,uint8_t y, char *chr,uint8_t size);              //在指定位置显示一个字符串
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);                          //在指定位置显示一个汉字
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]); //在指定位置显示一幅图片
void OLED_ShowString_fun(char *p);                                              //打印字符串


/* OLED初始化 */
void OLED_Init(void);


#endif
