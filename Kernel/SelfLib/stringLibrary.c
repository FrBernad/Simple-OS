#include <font.h>
#include <videoDriver.h>
#include <stdint.h>
#include <stringLibrary.h>

static uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);

static char defaultBGColour[RGB] = {0, 0, 0};
static char defaultFontColour[RGB] = {255, 255, 255};

void putChar(char c){
    printCharOnScreen(c,defaultBGColour,defaultFontColour);
}

void deletechar()
{
    removeCharFromScreen(defaultBGColour);
}

void printString(char * str) {
    for (uint8_t i = 0; str[i] != 0; i++)
    {
        putChar(str[i]);
    }
}

void printStringLn(char *str)
{
    for (uint8_t i = 0; str[i] != 0; i++)
    {
        putChar(str[i]);
    }
    newLine();
}

void printInt(uint64_t num)
{
    char buffer[10];
    uintToBase(num, buffer, 10);
    printString(buffer);
}

void clear(){
    clearScreen(defaultBGColour);
}

void printIntLn(uint64_t num)
{
    char buffer[10];
    uintToBase(num, buffer, 10);
    printString(buffer);
    newLine();
    }

    void newLine()
    {
        changeLineOnScreen();
    }

    uint8_t stringcmp(char *str1, char *str2, char delimiter)
    {
        uint8_t i;
        for (i = 0; str1[i] != 0 && str2[i] != 0 && str1[i] != delimiter && str2[i] != delimiter; i++)
        {
            if (str1[i] != str2[i])
                return 0;
        }

        return str1[i] == 0 || str2[i] == 0 || str1[i] == delimiter || str2[i] == delimiter ? 0 : 1;
    }

    static uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base)
    {
        char *p = buffer;
        char *p1, *p2;
        uint32_t digits = 0;

        //Calculate characters for each digit
        do
        {
            uint32_t remainder = value % base;
            *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
            digits++;
        } while (value /= base);

        // Terminate string in buffer.
        *p = 0;

        //Reverse string in buffer.
        p1 = buffer;
        p2 = p - 1;
        while (p1 < p2)
        {
            char tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;
            p1++;
            p2--;
        }

        return digits;
    }
