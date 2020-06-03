#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <screens.h>
#include <stdint.h>

typedef struct {
      void (*app)();
      void (*reset)();
      t_screenID screenID;
      uint64_t* stack;
} t_application;

#endif
