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

//todo: print registers, done in assembly
void inforeg();

//todo: recieves memory direction and prints 32 bytes after
void printmem(uint64_t mem);

//todo: desplays system time
void time();

//todo: shows processor model and brand
void cpuInfo();

//todo: shows processor temp
void temp();

#endif