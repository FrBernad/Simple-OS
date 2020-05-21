#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

typedef struct{
    void(*command)();
    char * name;
}t_command;

#define HELP 0
#define INFOREG 1
#define PRINTMEM 2
#define TIME 3
#define CPUID 4
#define TEMP 5

void help();
void inforeg();
void printmem(uint8_t * mem);
void time();
void cpuid();
void temp();

#endif