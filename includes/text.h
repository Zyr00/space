#ifndef __TEXT_H__
#define __TEXT_H__

#include "common.h"

#define GLYPH_WIDTH 16
#define GLYPH_HEIGHT 30

extern TTF_Font *font;

/**
 * Draw text
 *
 * @param x the x positon of the text
 * @param y the y positon of the text
 * @param r the red color value of the text
 * @param g the green color value of the text
 * @param b the blue color value of the text
 * @param fmt the format like in printf
 */
void drawText(int, int, int, int, int, char *, ...);

#endif
