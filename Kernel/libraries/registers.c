#include <registers.h>

static char * regNames[] = {"rax", "rcx", "rdx", "rbx", "rsi", "rdi", "rsp", "rbp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", ""};

void getRegisters(t_register * registers){
    uint64_t registersData[REGISTERS];
    getRegistersData(registersData); //return array 

    for (int i = 0; i < REGISTERS; i++)
    {
        registers[i].data=registersData[i];     
        registers[i].name=regNames[i];     
    }
}
