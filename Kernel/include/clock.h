#ifndef CLOCK_H
#define CLOCK_H

#define SECONDS 0x00
#define MINUTES 0x02
#define HOURS 0x04

#include <stdint.h>

uint8_t getDecimalTimeInfo(uint8_t info);
uint8_t getBSDTimeInfo(uint8_t info);

#endif