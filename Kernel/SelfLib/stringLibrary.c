#include <font.h>
#include <videoDriver.h>
#include <stdint.h>
#include <stringLibrary.h>

static char defaultBGColour[RGB] = {0, 0, 0};
static char defaultFontColour[RGB] = {255, 255, 255};

void putcharr(char c){
    printCharOnScreen(c,defaultBGColour,defaultFontColour);
}

uint8_t stringcmpp(char *str1, char *str2, char delimiter)
{
    uint8_t i;
    for (i = 0; str1[i] != 0 && str2[i] != 0 && str1[i] != delimiter && str2[i] != delimiter; i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }

    return str1[i] == 0 || str2[i] == 0 || str1[i] == delimiter || str2[i] == delimiter ? 0 : 1;
}

void deletechar()
{
    removeCharFromScreen(defaultBGColour);
}

void printString(char * str) {
    for (uint8_t i = 0; str[i] != 0; i++)
    {
        putcharr(str[i]);
    }
}