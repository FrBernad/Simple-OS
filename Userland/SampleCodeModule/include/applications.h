#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <screens.h>

typedef struct {
      void(*app)();
      t_screenID screenID;
} t_application;

#endif