#ifndef __OLED_ZK_H__
#define __OLED_ZK_H__


#include "main.h"


/*
    汉字字模
    阴码、列行式、16、64、逆向、16进制、C51
*/

extern const uint8_t F6x8[][6];
extern const uint8_t F8X16[];
extern char Hzk[][32];



/*
    图片字模
    选择图片，用画图软件打开，修改分辨率64*64，保存为单色模式
*/

extern uint8_t BMP1[];


#endif
