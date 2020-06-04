#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

//dataTypes
#include <RTCTime.h>
#include <stdint.h>
#include <colours.h>

#define SYSCALLS 10

void sys_getMem(uint64_t memDir, uint8_t* memData);
uint8_t sys_RTCTime(t_timeInfo tInfo);
int sys_temp();

void sys_write(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour);
void sys_staticwrite(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour);
char sys_getchar();
void sys_clear();

#endif