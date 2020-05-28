#include <staticStack.h>
#include <utils.h>

void pop(t_stack* stack, void* elem) {
      if (!(isEmpty(stack))) {
            memcpy(elem, (void*)((uint64_t)stack->stack + ((stack->size-1) * stack->dataSize)), stack->dataSize);
            stack->size--;
      }
}

void push(t_stack* stack, void* elem) {
      if (stack->size < stack->dim) {
            memcpy((void*)((uint64_t)stack->stack + (stack->size * stack->dataSize)), elem, stack->dataSize);
            stack->size++;
      }
}

int isEmpty(t_stack* stack) {
    return stack->size==0;
}

void peek(t_stack* stack, void* elem) {
      if (!(isEmpty(stack))) {
            memcpy(elem, (void*)((uint64_t)stack->stack + ((stack->size-1) * stack->dataSize)), stack->dataSize);
      }
}
