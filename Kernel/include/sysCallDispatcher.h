#ifndef SYS_CALL_DISPATCHER
#define SYS_CALL_DISPATCHER

#include <stdint.h>

typedef struct
{
    uint64_t rax, rdi, rsi, rdx, r10, r8, r9;
} registers;

// void systemCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax, uint64_t r8, uint64_t r9, uint64_t r10);
uint64_t sysCallDispatcher(registers * r);

#endif 