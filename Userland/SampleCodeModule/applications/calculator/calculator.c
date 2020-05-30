#include <appManager.h>
#include <buffer.h>
#include <calculator.h>
#include <keys.h>
#include <stringLib.h>
#include <lib.h>
#include <systemCalls.h>
#include <utils.h>
#include <expressionAnalyzer.h>

static void initCalculator();
static void calcText();
static void processChar(char c);

static t_buffer calcBuffer = {{0}, 0};
static int blink = 1, started = 0;

//TODO: MODULARIZAR EL WHILE

void runCalculator() {
      if (!started) {
            initCalculator();
      }
      char c;
      while (1) {
            c = 0;
            while (c == 0) {
                  halt();
                  c = getchar();
                  if (sys_ticksElapsed() % 12 == 0) {
                        blinkCursor(&blink);
                  }
            }
            processChar(c);
      }
}

static void processChar(char c){
      if (c != 0) {
            staticputchar(' ');  //remove blink
            switch (c) {
                  case CHANGE_SCREEN_0:
                        break;
                  case CHANGE_SCREEN_1:
                        sys_changeApp();
                        break;
                  case CLEAR_SCREEN:
                        sys_clear();
                        cleanBuffer(&calcBuffer);
                        calcText();
                        break;
                  case '=':
                        putchar(c);
                        evaluate(calcBuffer.buffer);
                        cleanBuffer(&calcBuffer);
                        calcText();
                        break;
                  case '\b':
                        if (calcBuffer.index > 0) {
                              calcBuffer.buffer[--calcBuffer.index] = 0;  //i pongo a-- se caga pq accedo a index=BUFFER_SIZE
                              deletechar();
                        }
                        break;

                  default:
                        if (calcBuffer.index < BUFFER_SIZE) {
                              if (IS_DIGIT(c) || IS_OPERAND(c) || c == ' ' || c == '.') {
                                    calcBuffer.buffer[calcBuffer.index++] = c;
                                    putchar(c);
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
      started = 1;
}

static void calcText() {
      printString("calculator $ > ");
}
