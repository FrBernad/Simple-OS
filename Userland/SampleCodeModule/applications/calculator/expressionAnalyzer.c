#include <buffer.h>
#include <expressionAnalyzer.h>
#include <staticStack.h>
#include <stringLib.h>
#include <utils.h>

static const int precedenceMx[5][6] = {
   //+, -, *, %, (, )
    {1, 1, 0, 0, 0, 1},  //+
    {1, 1, 0, 0, 0, 1},  //-
    {1, 1, 1, 1, 0, 1},  //*
    {1, 1, 1, 1, 0, 1},  //%
    {0, 0, 0, 0, 0, 0}   //(
};

static void toPostfix(char *expression, t_buffer *postfix, int *error);
static void putOperator(char operator, t_stack *operatorsStack, t_buffer *postfix, int *error);
static int hasToPop(char peek, char current);
static int getPrecedence(char c);
static int operate(int left, int right, char *operator);

int getValue(char *expression, int *error) {
      t_buffer postfix = {{0}, 0};
      toPostfix(expression, &postfix, error);

      if (*error) {
            return -1;
      }
      int numbers[BUFFER_SIZE] = {0}, popNum;
      t_stack numStack = {numbers, 0, BUFFER_SIZE, INTEGER};

      char token[BUFFER_SIZE] = {0};
      strtok(postfix.buffer, token, ' ');
      while (strtok(0, token, ' ')) {
            if (isNum(token)) {
                  popNum = strToInt(token, error);
                  stackPush(&numStack, &popNum);
            } else {
                  if (IS_OPERAND(*token)) {
                        if (numStack.size < 2) {
                              printStringLn("error");
                              *error = 1;
                              break;
                        }
                        int left, right, result;
                        stackPop(&numStack, &right);
                        stackPop(&numStack, &left);
/*printString("Left= ");
                        printInt(left);
                        putchar('\n');
                        printString("Right= ");
                        printInt(right);
                        putchar('\n');*/
                        result = operate(left, right, token);
                      /*  printInt(result);
                        putchar('\n');*/
                        stackPush(&numStack, &result);
                  }
            }
      }
      if(numStack.size != 1){
            *error = 1;
      }

      strtok(0, 0, ' ');

      if (*error) {
            return -1;
      }

      int result;
      stackPop(&numStack, &result);
      return result;
}

static void toPostfix(char *expression, t_buffer *postfix, int *error) {
      char operators[BUFFER_SIZE] = {0};
      t_stack operatorsStack = {operators, 0, BUFFER_SIZE, CHAR};

      char token[BUFFER_SIZE] = {0};
      strtok(expression, token, ' ');
      while (strtok(0, token, ' ')) {
            if (isNum(token)) {
                  for (int i = 0; token[i] != 0; i++) {
                        postfix->buffer[postfix->index++] = token[i];
                        postfix->buffer[postfix->index++] = ' ';
                  }
            } else if (IS_OPERAND(token[0]) && token[1] == 0) {  //if is operand and strlen is 1
                  putOperator(token[0], &operatorsStack, postfix, error);
                  if (*error) {
                        return;
                  }
            } else {
                  *error = 1;
                  return;
            }
      }

      strtok(0, 0, ' ');

      char popOp;
      while (!stackIsEmpty(&operatorsStack)) {
            stackPop(&operatorsStack, &popOp);
            postfix->buffer[postfix->index++] = popOp;
            postfix->buffer[postfix->index++] = ' ';
      }
}

static void putOperator(char operator, t_stack *operatorsStack, t_buffer *postfix, int *error) {
      char peekOp, popOp;
      while (!stackIsEmpty(operatorsStack)) {
            stackPeek(operatorsStack, &peekOp);
            if (hasToPop(peekOp, operator)) {
                  stackPop(operatorsStack, &popOp);
                  postfix->buffer[postfix->index++] = popOp;
                  postfix->buffer[postfix->index++] = ' ';
            } else {
                  break;
            }
      }
      if (operator== ')') {
            if (stackIsEmpty(operatorsStack)) {
                  *error = 1;
                  return;
            }
            stackPop(operatorsStack, &popOp);
      } else {
            stackPush(operatorsStack, &operator);
      }
}

static int hasToPop(char peek ,char current) {
      int aux = precedenceMx[getPrecedence(peek)][getPrecedence(current)];
      putchar('\n');
      putchar('\n');
      printString("Precedence peek ");
      printString(&peek);
      printString(",current= ");
      printString(&current);
      printString("-> ");
      printInt(aux);
      putchar('\n');
      return aux;
}

static int getPrecedence(char c) {
      enum precedence { SUM = 0,
                        SUB,
                        MUL,
                        DIV,
                        OPEN,
                        CLOSE };
      switch (c) {
            case '+':
                  return SUM;
            case '-':
                  return SUB;
            case '*':
                  return MUL;
            case '%':
                  return DIV;
            case '(':
                  return OPEN;
            case ')':
                  return CLOSE;
      }
      return -1;
}

static int operate(int left, int right, char *operator) {
      int result;
      switch (*operator) {
            case '+':
                  result = left + right;
                  break;
            case '-':
                  result = left - right;
                  break;
            case '*':
                  result = left * right;
                  break;
            case '%':
                  result = left / right;
                  break;
            case '^':
                  result = left / right;
                  break;
      }
      return result;
}
