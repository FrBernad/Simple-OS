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
static void operate(double left, double right, char *operator, double * result);


//TODO:ARROBA

void getValue(char *expression, int *error, char * result) {
      t_buffer postfix = {{0}, 0};

      toPostfix(expression, &postfix, error);
      if (*error) {
            return;
      }
      double numbers[BUFFER_SIZE] = {0}, popNum;
      t_stack numStack = {numbers, 0, BUFFER_SIZE, DOUBLE};

      char token[BUFFER_SIZE] = {0};
      strtok(0, 0, ' ');
      strtok(postfix.buffer, token, ' ');
      while (strtok(0, token, ' ')) {
            if (isNum(token)) {
                  strToDouble(token, error,&popNum);
                  stackPush(&numStack, &popNum);
            } else {
                  if (IS_OPERAND(*token)) {
                        if (numStack.size < 2) {
                              *error = 1;
                              break;
                        }
                        double left, right, res;
                        stackPop(&numStack, &right);

                        stackPop(&numStack, &left);
                        operate(left, right, token,&res);
                        stackPush(&numStack, &res);
                  }
            }
      }
      if(numStack.size != 1){
            *error = 1;
      }

      strtok(0, 0, ' ');

      if (*error) {
            return;
      }

     double total;
     stackPop(&numStack, &total);
     doubleToString(result,total,4);
}

static void toPostfix(char *expression, t_buffer *postfix, int *error) {
      char operators[BUFFER_SIZE] = {0};
      t_stack operatorsStack = {operators, 0, BUFFER_SIZE, CHAR};

      char token[BUFFER_SIZE] = {0};
      strtok(0, 0, ' ');
      strtok(expression, token, ' ');
      while (strtok(0, token, ' ')) {
            if (isNum(token)) {
                  for (int i = 0; token[i] != 0; i++) {
                        postfix->buffer[postfix->index++] = token[i];
                  }
                  postfix->buffer[postfix->index++] = ' ';
            } else if (IS_OPERAND(token[0]) && token[1] == 0) {  //if is operand and strlen is 1
                  putOperator(token[0], &operatorsStack, postfix, error);
                  if (*error) {
                        return;
                  }
            } else {
                  *error = 1;
                  return;
            }
            for (int i = 0; i < BUFFER_SIZE; i++) {
                  token[i] = 0;
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

static void operate(double left, double right, char *operator, double * result){
      switch (*operator) {
            case '+':
                  *result = left + right;
                  break;
            case '-':
                  *result = left - right;
                  break;
            case '*':
                  *result = left * right;
                  break;
            case '%':
                  *result = left / right;
                  break;
      }
}