#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#define COMMANDS 10
#define MAX_ARGS 4
typedef struct{
    void(*command)(int,char **);
    char * name;
}t_command;

//prints commands man
void help(int argc,char ** args);

//print registers, done in assembly
void inforeg(int argc,char ** args);

//recieves memory direction and prints 32 bytes after
void printmem(int argc,char ** args);

//displays system time
void time(int argc,char ** args);

//shows processor model and brand
void cpuInfo(int argc,char ** args);

//shows processor temp
void cpuTemp(int argc,char ** args);

//change username in shell
void changeUsername(int argc,char ** args);

//check zero exception
void checkZeroException(int argc,char ** args);

//check invalid op exception
void checkInvalidOpcodeException(int argc, char **args);

//shows arguments
void showArgs(int argc, char **args);

#endif