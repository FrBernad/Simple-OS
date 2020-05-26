#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <screens.h>

typedef enum {
      CALCULATOR = 0,
      SHELL = 1
} t_applicationID;

typedef struct{
      t_applicationID appID;
      t_screenID screenID;
}t_application;

extern t_application shell;
extern t_application calculator;

#endif