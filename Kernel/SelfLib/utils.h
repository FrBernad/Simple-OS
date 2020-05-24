#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define IS_LETTER(c) (c >= 'a' && c <= 'z' ? 1 : 0)
#define IS_OPPERAND(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '(' || c == ')' ? 1 : 0)
#define IS_NUMBER(c) (c >= '0' && c <= '9' ? 1 : 0)

uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);
uint8_t BSDToInt(uint8_t num);
uint64_t strToInt(char * str);
float strToFloat(char *string);
uint64_t pow(uint64_t x, uint64_t y);

#endif