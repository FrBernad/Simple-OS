#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdint.h>

void putchar(char c);
void printString(char* str);
void printStringLn(char* str);
void printInt(uint64_t num);
void printIntLn(uint64_t num);
void printHex(uint64_t num);
void printHexLn(uint64_t num);
void clear();
void clearLine();
void newLine();
void deletechar();
uint8_t stringcmp(char* str1, char* str2);

#endif