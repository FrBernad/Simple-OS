#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

//dataTypes
#include <applications.h>
#include <registers.h>
#include <RTCTime.h>
#include <cpuInfo.h>
#include <stdint.h>
#include <colours.h>

#define SYSCALLS 16

void sys_inforeg(t_register * registers);
uint8_t sys_getMem(uint64_t mem);
uint8_t sys_RTCTime(t_timeInfo tInfo);
void sys_cpuInfo(t_cpuInfo * cpuInfo);
uint8_t sys_temp();

void sys_write(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour);
void sys_staticwrite(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour);
char sys_getchar();
void sys_deletechar();
void sys_clear();

int sys_ticksElapsed();

void sys_changeResources(const t_application* app);

#endif