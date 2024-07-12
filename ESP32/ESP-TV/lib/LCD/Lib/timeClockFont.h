#ifndef _SD3_Font_
#define _SD3_Font_

#include <Arduino.h>
#include <pgmspace.h>

struct LineAtom
{
	unsigned xValue : 8; // X坐标
	unsigned yValue : 8; // Y坐标
	unsigned lValue : 8; // 长度
	LineAtom(int x, int y, int l) : xValue(x), yValue(y), lValue(l){};
};

extern const LineAtom *largeLineFont[10];
extern const uint32_t largeLineFont_size[10];
extern const LineAtom *middleLineFont[10];
extern const uint32_t middleLineFont_size[10];
extern const LineAtom *smallLineFont[10];
extern const uint32_t smallLineFont_size[10];

#endif
