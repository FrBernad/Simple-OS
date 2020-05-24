#ifndef SYSTEM_CALL_HANDLER_H
#define SYSTEM_CALL_HANDLER_H

#include <stdint.h>

typedef struct
{
    uint64_t rdi, rsi, rdx, rax, r8, r9, r10;
} registers;

// void systemCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax, uint64_t r8, uint64_t r9, uint64_t r10);
void systemCall(registers * r);

#endif 