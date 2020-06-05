#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

//dataTypes
#include <RTCTime.h>
#include <taskManager.h>
#include <colours.h>
#include <cpuInfo.h>
#include <stdint.h>

typedef enum{
    GET_MEM = 0,
    RTC_TIME = 1,
    TEMP = 2,
    WRITE = 3,
    GETCHAR = 4,
    CLEAR = 5,
    LOAD_APP = 6,
    RUN = 7,
    EXIT = 8,
    INFOREG = 9
}syscallID;

uint64_t syscall(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);
void sys_changeApp();

// void sys_getMem(uint64_t memDir, uint8_t* memData);
// uint8_t sys_RTCTime(t_timeInfo tInfo);
// int sys_temp();

// void sys_write(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour);
// void sys_staticwrite(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour);
// char sys_getchar();
// void sys_clear();

// int sys_ticksElapsed();

// void sys_changeApp();
// void sys_loadApp(t_PCB* app);

// void sys_run();
// void sys_exit();
// uint64_t * sys_inforeg();

#endif