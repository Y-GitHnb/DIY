#ifndef _SD3_Font_
#define _SD3_Font_

#include <Arduino.h>
#include <pgmspace.h>

#define SD_FONT_YELLOW 0xD404 // 黄色字体颜色
#define SD_FONT_WHITE 0xFFFF  // 黄色字体颜色

struct LineAtom
{
	unsigned xValue : 8; // X坐标
	unsigned yValue : 8; // Y坐标
	unsigned lValue : 8; // 长度
	LineAtom(int x, int y, int l) : xValue(x), yValue(y), lValue(l){};
};

extern const LineAtom _largeLineFont_0[];
extern const LineAtom _largeLineFont_1[];
extern const LineAtom _largeLineFont_2[];
extern const LineAtom _largeLineFont_3[];
extern const LineAtom _largeLineFont_4[];
extern const LineAtom _largeLineFont_5[];
extern const LineAtom _largeLineFont_6[];
extern const LineAtom _largeLineFont_7[];
extern const LineAtom _largeLineFont_8[];
extern const LineAtom _largeLineFont_9[];

extern const LineAtom _middleLineFont_0[];
extern const LineAtom _middleLineFont_1[];
extern const LineAtom _middleLineFont_2[];
extern const LineAtom _middleLineFont_3[];
extern const LineAtom _middleLineFont_4[];
extern const LineAtom _middleLineFont_5[];
extern const LineAtom _middleLineFont_6[];
extern const LineAtom _middleLineFont_7[];
extern const LineAtom _middleLineFont_8[];
extern const LineAtom _middleLineFont_9[];

extern const LineAtom _smallLineFont_0[];
extern const LineAtom _smallLineFont_1[];
extern const LineAtom _smallLineFont_2[];
extern const LineAtom _smallLineFont_3[];
extern const LineAtom _smallLineFont_4[];
extern const LineAtom _smallLineFont_5[];
extern const LineAtom _smallLineFont_6[];
extern const LineAtom _smallLineFont_7[];
extern const LineAtom _smallLineFont_8[];
extern const LineAtom _smallLineFont_9[];

extern const LineAtom *largeLineFont[10];
extern const uint32_t largeLineFont_size[10];
extern const LineAtom *middleLineFont[10];
extern const uint32_t middleLineFont_size[10];
extern const LineAtom *smallLineFont[10];
extern const uint32_t smallLineFont_size[10];

#endif
