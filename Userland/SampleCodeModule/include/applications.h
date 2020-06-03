#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <screens.h>
#include <stdint.h>

typedef struct {
      void (*entryPoint)();
      t_screenID screenID;
} t_application;

#endif