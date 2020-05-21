#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdint.h>
#include <lib.h>

#define WIDTH 80
#define HEIGHT 25

#define RESET_VID currentVideo = firstMem;

void clearScreen();
void newLine();
// void putchar(char c);
void printString(char * str);
void printStringWCL(char * str, uint8_t colour, uint64_t count);
void printStringLn(char * str);
void printInt(uint64_t num);
void printIntLn(uint64_t num);
void activateKeyboard();
// uint8_t stringcmp(char * str1,char * str2, char delimiter);
// void deletechar();

#endif