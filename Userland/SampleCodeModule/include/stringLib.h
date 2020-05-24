#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdint.h>

void putchar(char c);
char getchar();
void printString(char* str, uint8_t newLine);
void printNum(uint64_t num, uint8_t base);
void clear();
void clearLine();
void newLine();
void deletechar();
uint8_t stringcmp(char* str1, char* str2);

#endif