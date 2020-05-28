#include <appManager.h>
#include <buffer.h>
#include <calculator.h>
#include <keys.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>
#include <expressionAnalyzer.h>

static void initCalculator();
static void calcText();

static t_buffer calcBuffer = {{0}, 0};
static int blink = 1, started = 0;

void runCalculator() {
      if (!started) {
            initCalculator();
            started = 1;
      }
      while (1) {
            if (sys_ticksElapsed() % 12 == 0) {
                  blinkCursor(&blink);
            }
            char c = getchar();
            if (c != 0) {
                  staticputchar(' ');  //remove blink
                  switch (c) {
                        case CHANGE_SCREEN_0:
                              break;
                        case CHANGE_SCREEN_1:
                              changeApplication(shell);
                              break;
                        case EQUAL:
                              putchar(c);
                              evaluate(calcBuffer.buffer);
                              cleanBuffer(&calcBuffer);
                              calcText();
                              break;
                        case CLEAR_SCREEN:
                              sys_clear();
                              cleanBuffer(&calcBuffer);
                              calcText();
                              break;
                        case B_SPACE:
                              if (calcBuffer.index > 0) {
                                    calcBuffer.buffer[--calcBuffer.index] = 0;  //i pongo a-- se caga pq accedo a index=BUFFER_SIZE
                                    deletechar();
                              }
                              break;

                        default:
                              if (calcBuffer.index < BUFFER_SIZE) {
                                    if (IS_DIGIT(c) || IS_OPERAND(c) || c==SPACE) {
                                          calcBuffer.buffer[calcBuffer.index++] = c;
                                          putchar(c);
                                    }
                              }
                  }
            }
      }
}

void evaluate(char* expression) {
      int value, error = 0;
      value = getValue(expression, &error);
      if (!error) {
            printInt(value);
      } else {
            printStringLn("Invalid expression");
      }
      putchar('\n');
}

static void initCalculator(){
      calcText();
}

static void calcText() {
      printString("calculator $ > ");
}
