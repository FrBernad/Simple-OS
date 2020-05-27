#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdint.h>
#include <colours.h>

void printString(char* str);
void printStringLn(char* str);
void printStringWC(char* str, t_colour bgColour, t_colour fontColour);
void printInt(uint64_t num);
void printHex(uint64_t num);
void putchar(char c);
void staticputchar(char c);
void deletechar();
int strlen(char* str);

#endif