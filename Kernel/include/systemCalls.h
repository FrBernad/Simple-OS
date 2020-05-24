#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

#include <stdint.h>

#define SYSCALLS 14

void sys_printString(char *str, uint8_t newLine);
void sys_printNum(uint64_t num, uint8_t base);
void sys_putchar(char c);
char sys_getchar();
void sys_deletechar();
uint8_t sys_stringcmp(char *str1, char *str2);
void sys_clearLine();
void sys_clear();
void sys_newLine();

void sys_help();
void sys_inforeg();
void sys_printmem(uint64_t mem);
void sys_time();
void sys_cpuInfo();
void sys_temp();

#endif