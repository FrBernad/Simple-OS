#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <screens.h>

typedef struct {
      void(*app)();
      t_screenID screenID;
} t_application;

extern t_application shell;
extern t_application calculator;

#endif