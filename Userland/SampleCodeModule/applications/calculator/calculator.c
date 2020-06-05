#include <taskManager.h>
#include <calculator.h>
#include <expressionAnalyzer.h>
#include <keys.h>
#include <lib.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

static void initCalculator(t_calcData * calcData);
static void calcText();
static void processChar(char c, t_calcData* calcDatas);

void runCalculator() {
      t_calcData calcData;
      initCalculator(&calcData);
      char c;
      while (1) {
            c = getchar();
            processChar(c, &calcData);
      }
      syscall(EXIT, 0, 0, 0, 0, 0, 0);
}

static void processChar(char c, t_calcData* calcData) {
      if (c != 0) {
            switch (c) {
                  case CHANGE_SCREEN_0:
                        break;
                  case CHANGE_SCREEN_1:
                        sys_changeApp();
                        break;
                  case CLEAR_SCREEN:
                        syscall(CLEAR,0,0,0,0,0,0);
                        cleanBuffer(&calcData->buffer);
                        calcText(calcData);
                        break;
                  case '=':
                        evaluate(calcData->buffer.buffer);
                        cleanBuffer(&calcData->buffer);
                        calcText(calcData);
                        break;
                  case '\b':
                        if (calcData->buffer.index > 0) {
                              calcData->buffer.buffer[--calcData->buffer.index] = 0;  //pongo -- para evitar acceder a index=BUFFER_SIZE
                              deletechar();
                        }
                        break;

                  default:
                        if (calcData->buffer.index < BUFFER_SIZE) {
                              if (IS_DIGIT(c) || IS_OPERAND(c) || c == ' ' || c == '.') {
                                    calcData->buffer.buffer[calcData->buffer.index++] = c;
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
      printString(" = ");
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

static void initCalculator(t_calcData* calcData) {
      cleanBuffer(&calcData->buffer);
      strcpy("CALCULATOR", calcData->name);
      calcText(calcData);
}

static void calcText(t_calcData* calcData) {
      printString(calcData->name);
      printString(" $ > ");
}
