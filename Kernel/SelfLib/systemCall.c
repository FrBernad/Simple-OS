#include <systemCall.h>
#include <stringLib.h>

#define STDOUT 1
#define STDERR 2
#define MAX_FUNCS 64

// static void sys_write(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax, uint64_t r8, uint64_t r9, uint64_t r10);
static void sys_write(registers * r);

// static void (*syscalls[MAX_FUNCS])() = {0, &sys_write, 0};
static void (*syscalls[MAX_FUNCS])(registers * r) = {0, &sys_write, 0};

// void systemCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax, uint64_t r8, uint64_t r9, uint64_t r10)
// {
//     if (rax > 0 && rax <= MAX_FUNCS)
//         syscalls[rax](rdi,rsi,rdx,rax,r8,r9,r10);
// }

void systemCall(registers * r)
{
    if (r->rax > 0 && r->rax <= MAX_FUNCS)
        syscalls[r->rax](r);
}

//%rax	System call	%rdi	        %rsi	        %rdx
//1	    sys_write	unsigned int fd	const char *buf	size_t count

// static void sys_write(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax, uint64_t r8, uint64_t r9, uint64_t r10)
// {
//     if(rdi == STDERR)
//         printStringWCL((char*) rsi,0x04,(uint64_t) rdx);
//     else    
//         printStringWCL((char*) rsi,0,(uint64_t) rdx);
// }

static void sys_write(registers * r)
{
    if (r->rdi == STDERR)
        printStringWCL((char *)r->rsi, 0x04, (uint64_t)r->rdx);
    else
        printStringWCL((char *)r->rsi, 0, (uint64_t)r->rdx);
}
