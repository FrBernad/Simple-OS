#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdint.h>

void printString(char* str);
void printStringLn(char* str);
void printInt(uint64_t num);
void printHex(uint64_t num);
void putchar(char c);
void staticputchar(char c);
char getchar();
void deletechar();
void newLine();
int strlen(char* str);

#endif