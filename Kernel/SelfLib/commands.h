#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct{
    void(*command)();
    uint8_t * name;
}command;

#define HELP 0
#define INFOREG 1
#define PRINTMEM 2
#define TIME 3
#define CPUID 4
#define TEMP 5


#endif