#include <systemCall.h>

#define STDOUT 1
#define STDERR 2
#define MAX_FUNCS 64

// static void sys_write(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax, uint64_t r8, uint64_t r9, uint64_t r10);

// static void (*syscalls[MAX_FUNCS])() = {0, &sys_write, 0};
static void (*syscalls[MAX_FUNCS])(registers * r) = {0};


void systemCall(registers * r)
{
    if (r->rax > 0 && r->rax <= MAX_FUNCS)
        syscalls[r->rax](r);
}

