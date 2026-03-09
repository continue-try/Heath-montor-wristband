#ifndef FONT_H_
#define FONT_H_

#include "stdint.h"
typedef struct{
	uint8_t FontData[32];	
	char Index[4];
}ChineseCell_t;//UTF8

extern const uint8_t OLED_F6x8[][6];
extern const uint8_t OLED_F8x16[][16];
extern const ChineseCell_t OLED_CF16x16[];
extern const uint8_t Image_desk[1024];
#endif