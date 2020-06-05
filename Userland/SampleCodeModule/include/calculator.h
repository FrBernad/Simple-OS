#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <buffer.h>

typedef struct{
      t_buffer buffer;
      char name[BUFFER_SIZE];
} t_calcData;

void runCalculator();
void evaluate(char *expression);

#endif