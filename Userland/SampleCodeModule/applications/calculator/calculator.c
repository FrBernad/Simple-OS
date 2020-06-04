#include <taskManager.h>
#include <buffer.h>
#include <calculator.h>
#include <expressionAnalyzer.h>
#include <keys.h>
#include <lib.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

static void initCalculator();
static void calcText();
static void processChar(char c);

static t_buffer calcBuffer = {{0}, 0};

void runCalculator() {
      initCalculator();
      char c;
      while (1) {
            c = getchar();
            processChar(c);
      }
}

static void processChar(char c) {
      if (c != 0) {
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
                              calcBuffer.buffer[--calcBuffer.index] = 0;  //pongo -- para evitar acceder a index=BUFFER_SIZE
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
      int error = 0;
      char result[BUFFER_SIZE] = {0};
      getValue(expression, &error, result);
      if (!error) {
            printStringLn(result);
      } else {
            putchar('\n');
            printStringWC("Error: ", BLACK, RED);
            if (error == INVALID_EXP) {
                  printStringWC("invalid expression\n", BLACK, RED);
            } else if (error == DIV_BY_ZERO) {
                  printStringWC("division by zero is undefined\n", BLACK, RED);
            }
      }
      putchar('\n');
}

static void initCalculator() {
      cleanBuffer(&calcBuffer);
      sys_clear();
      calcText();
}

static void calcText() {
      printString("calculator $ > ");
}
