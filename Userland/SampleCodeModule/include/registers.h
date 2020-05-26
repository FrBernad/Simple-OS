#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#define REGISTERS 16

typedef struct{
      uint64_t data;
      char * name;
}t_register;

#endif
