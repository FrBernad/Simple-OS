#include <appManager.h>
#include <buffer.h>
#include <systemCalls.h>
#include <calculator.h>
#include <keys.h>
#include <stringLib.h>
#include <utils.h>

static void calcText();

static t_buffer calcBuffer = {{0}, 0};

static int started = 0, availableRemoves = 0, blink = 1;

void runCalculator() {
      if (!started) {
            calcText();
            started = 1;
      }
      while (1) {
            char c = getchar();
            if (c != 0) {
                  switch (c) {
                        case CHANGE_SCREEN_0:
                              break;
                        case CHANGE_SCREEN_1:
                              staticputchar(' ');  //for timer tick
                              changeApplication(shell);
                              break;
                        case EQUAL:
                              putchar(c);
                              evaluate(calcBuffer.buffer);
                              cleanBuffer(&calcBuffer);
                              calcText();
                              staticputchar(' ');  //for timer tick
                              availableRemoves = 0;
                              break;
                        case CLEAR_SCREEN:
                              sys_clear();
                              cleanBuffer(&calcBuffer);
                              calcText();
                              availableRemoves = 0;
                              break;
                        case B_SPACE:
                              if (availableRemoves != 0) {
                                    calcBuffer.buffer[--calcBuffer.index] = 0;  //i pongo a-- se caga pq accedo a index=BUFFER_SIZE
                                    availableRemoves--;
                                    staticputchar(' ');  //for timer tick
                                    deletechar();
                              }
                              break;

                        default:
                              if (calcBuffer.index < BUFFER_SIZE) {
                                    if (IS_NUMBER(c) || IS_OPPERAND(c)) {
                                          calcBuffer.buffer[calcBuffer.index++] = c;
                                          putchar(c);
                                          availableRemoves++;
                                    }
                              }
                  }
            } else {
                  if (sys_ticksElapsed() % 9 == 0) {
                        if (blink) {
                              staticputchar('|');
                              blink = 0;
                        } else {
                              staticputchar(' ');
                              blink = 1;
                        }
                  }
            }
      }
}

void evaluate(char* expression) {
      newLine();
}

static void calcText() {
      printString("calculator $ > ");
}