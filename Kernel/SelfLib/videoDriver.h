#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

#define RGB 3

void writePixel(uint32_t x, uint32_t y, char colour[RGB]);
void printChar(char c, char bgColour[RGB], char fontColour[RGB]);

#endif
