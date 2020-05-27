#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <stdint.h>

#define INTEGER 4
#define DOUBLE 8
#define CHAR 1

typedef struct{
    void * stack;
    int size;
    int dim;
    uint64_t dataSize;
}t_stack;

void pop(t_stack * stack, void * elem);
void push(t_stack * stack, void * elem);
int isEmpty(t_stack * stack);
void peek(t_stack * stack, void * elem);

#endif