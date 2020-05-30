#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <applications.h>
#include <screens.h>

void keyboardHandler();
char getchar();
void changeBuffer(t_screenID screen);
void runProcess();

#endif