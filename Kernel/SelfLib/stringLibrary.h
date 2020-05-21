#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H

void putChar(char c);
uint8_t stringcmp(char *str1, char *str2, char delimiter);
void deletechar();
void printString(char * str);
void newLine();
void printStringLn(char *str);
void printInt(uint64_t num);
void printIntLn(uint64_t num);
void clear();

#endif