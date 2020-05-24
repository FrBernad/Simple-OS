#ifndef SCREENS_H
#define SCREENS_H

#include <stdint.h>

#define MAX_SCREENS 2
#define SCREEN_1 1
#define SCREEN_2 2

typedef struct
{
    int defaultBGColour;
    int defaultFontColour;
    uint32_t currentX;
    uint32_t currentY;
    uint32_t offset;
    uint32_t width;
    uint32_t height;
    uint32_t firstLine;
    uint32_t firstLineWidth;
} t_screen;

#endif
