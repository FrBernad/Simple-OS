#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

typedef struct{
    void(*command)();
    char * name;
}t_command;

typedef enum {
      HELP = 0,
      INFOREG = 1,
      PRINTMEM = 2,
      TIME = 3,
      CPUINFO = 4,
      CPUTEMP = 5,
      CHANGEUSERNAME = 6
} t_commandID;

//prints commands man
void help();

//print registers, done in assembly
void inforeg();

//recieves memory direction and prints 32 bytes after
void printmem(uint64_t mem);

//displays system time
void time();

//shows processor model and brand
void cpuInfo();

//shows processor temp
void cpuTemp();

//change username in shell
void changeUsername(char * newUsername);

#endif