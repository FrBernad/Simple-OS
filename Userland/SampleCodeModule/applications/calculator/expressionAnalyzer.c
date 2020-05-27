#include <buffer.h>
#include <expressionAnalyzer.h>
#include <staticStack.h>
#include <utils.h>

// static const int precedenceMx[5][6] = {
//     //	 +,-,*,%,(,)
//     {1, 1, 0, 0, 0, 1},  //+
//     {1, 1, 0, 0, 0, 1},  //-
//     {1, 1, 1, 1, 0, 1},  //*
//     {1, 1, 1, 1, 0, 1},  //%
//     {0, 0, 0, 0, 0, 0}   //(
// };

// static void toPostfix(const char *expression, t_buffer *postfix, int * error);
// static double myStrtof(const char *string);

// int evaluate(char *expression, int *error) {
//       int error = 0;
//       char buffer[BUFFER_SIZE] = {0};
//       t_buffer postfix = {buffer, 0};
//       toPostfix(expression, &postfix, &error);

//       double numbers[BUFFER_SIZE] = {0};
//       t_stack numStack = {numbers, 0, BUFFER_SIZE, DOUBLE};

//       char string[14] = {0};
//       char current = 0;
//       int str_index = 0;
//       double val1, val2, answ;

//       for (int i = 0; postfix[i] != 0; i++) {
//             current = postfix[i];
//             if (IS_OPERATOR(current) && (postfix[i + 1] == 0 || postfix[i + 1] == ' ')) {
//                   if (isEmptyNum(&numbers)) {
//                         printf("MAL 1\n");
//                         return -1;
//                   }
//                   val2 = popNum(&numbers);

//                   if (isEmptyNum(&numbers)) {
//                         printf("MAL 2\n");
//                         return -1;
//                   }
//                   val1 = popNum(&numbers);

//                   switch (current) {
//                         case '+':
//                               answ = val1 + val2;
//                               break;
//                         case '-':
//                               answ = val1 - val2;
//                               break;
//                         case '*': {
//                               answ = val1 * val2;
//                               break;
//                         }
//                         case '%':
//                               answ = (double)val1 / val2;
//                               break;
//                   }
//                   pushNum(&numbers, answ);
//             }

//             else if (IS_NUMBER(current) || current == '.' || current == '-') {
//                   string[str_index++] = current;
//             }

//             else {
//                   if (str_index != 0) {
//                         pushNum(&numbers, my_strtof(string));
//                         int j = 0;
//                         while (j < str_index)
//                               string[j++] = 0;
//                         str_index = 0;
//                   }
//             }
//       }

//       if (isEmptyNum(&numbers)) {
//             printf("MAL 3\n");
//             return -1;
//       }
//       printf("Respuesta: %f\n", popNum(&numbers));
//       return 1;
// }

// static void toPostfix(const char *expression, t_buffer *postfix, int * error) {
//       char operators[BUFFER_SIZE] = {0};
//       t_stack postfix = {operators, 0, BUFFER_SIZE, CHAR};

//       // 23+3/

//       int i = 0,state=NUMBER;
// //a(
//       while(expression[i]!='='){
//           switch (state)
//           {
//           case NUMBER:
//               state = NUMBER;
//               if(expression[i]=='('){
//                     state = ERROR;
//               } else if (expression[i] == ' '){
                    
//                     state = SPACE;
//               } else if (expression[i] == ')') {
//                     state = PARENTHESIS_C;
//               } else if (expression[i] == '(') {
//                     state = PARENTHESIS_O;
//               } else if (IS_OPERAND(expression[i])) {
//                     state = PARENTHESIS_O;
//               }
//               }
//               break;
//           }
//       }
//       for (int i = 0; expression[i] != 0 && expression[i] != '='; i++) {
//             char symbol = expression[i];

//             if (IS_NUMBER(symbol) || symbol == '.') {  //si es un numero metelo en el token o un punto
//                   token.buffer[token.index++] = expression[i];
//             }  //mete es token y aumenta su tamaño

//             else if (buffer[i] == '-' && (buffer[i + 1] != 0 && buffer[i + 1] != '=' && buffer[i + 1] != ' ')) {  //si es el menos para cambiar signo metelo
//                   to_convert[tc_index++] = buffer[i];
//             }  //mete es token y aumenta su tamaño

//             else {
//                   if (IS_OPERATOR(buffer[i]) || buffer[i] == ' ') {  //si es un operador o un espacio entra

//                         if (tc_index > 0) {  //si el token no esta vacio --> metelo todo en el string postfija
//                               for (int k = 0; k < tc_index; k++) {
//                                     postfix[pf_index++] = to_convert[k];
//                                     to_convert[k] = 0;
//                               }
//                               postfix[pf_index++] = ' ';
//                               tc_index = 0;
//                         }

//                         if (IS_OPERATOR(buffer[i])) {
//                               putOperator(buffer[i], &operators, &pf_index, postfix);
//                         }
//                   }
//             }
//       }

//       if (tc_index != 0) {  //si el token no esta vacio --> metelo todo en el string postfija
//             for (int k = 0; k < tc_index; k++) {
//                   postfix[pf_index++] = to_convert[k];
//                   to_convert[k] = 0;
//             }

//             postfix[pf_index++] = ' ';
//             tc_index = 0;
//       }

//       while (!isEmptyOp(&operators)) {
//             postfix[pf_index++] = popOp(&operators);
//             postfix[pf_index++] = ' ';
//       }
//       postfix[--pf_index] = 0;
// }

// static void putOperator(char op, t_char_stack *operators, int *pf_index, char *postfix) {
//       if (isEmptyOp(operators)) {
//             pushOp(operators, op);
//             return;
//       }
//       if (op == ')') {
//             while (!isEmptyOp(operators) && peekOp(operators) != '(') {
//                   postfix[(*pf_index)++] = popOp(operators);
//                   postfix[(*pf_index)++] = ' ';
//             }
//             popOp(operators);
//             return;
//       }

//       while (!isEmptyOp(operators) && hasToPop(peekOp(operators), op)) {
//             postfix[(*pf_index)++] = popOp(operators);
//             postfix[(*pf_index)++] = ' ';
//       }
//       pushOp(operators, op);
//       return;
// }

// static int hasToPop(char peek, char current) {
//       int peek_value = peekValue(peek);
//       int current_value = currentValue(current);
//       if (peek_value == -1 || current_value == -1) {
//             printf("MAL 4\n");
//             return -1;
//       }
//       return precedenceMx[peek_value][current_value];
// }

// static int peekValue(char c) {
//       enum peek { PSUM = 0,
//                   PSUB,
//                   PMUL,
//                   PDIV,
//                   POPEN,
//                   PCLOSE };
//       switch (c) {
//             case '+':
//                   return PSUM;
//             case '-':
//                   return PSUB;
//             case '*':
//                   return PMUL;
//             case '%':
//                   return PDIV;
//             case '(':
//                   return POPEN;
//             case ')':
//                   return PCLOSE;
//       }
//       return -1;
// }

// static int currentValue(char c) {
//       enum current { CSUM = 0,
//                      CSUB,
//                      CMUL,
//                      CDIV,
//                      COPEN };
//       switch (c) {
//             case '+':
//                   return CSUM;
//             case '-':
//                   return CSUB;
//             case '*':
//                   return CMUL;
//             case '%':
//                   return CDIV;
//             case '(':
//                   return COPEN;
//       }
//       return -1;
// }

// static double my_strtof(const char *string) {
//       double res = 0.0F;
//       int afterDecimalPoint = 0, i = 0, negative = 1;
//       double div = 1;

//       while (string[i] != 0) {
//             if (string[i] == '-') {
//                   negative *= -1;
//             } else if (IS_NUMBER(string[i])) {
//                   if (!afterDecimalPoint) {
//                         res *= 10;
//                         res += string[i] - '0';
//                   } else {
//                         div *= 10;
//                         res += (double)(string[i] - '0') / div;
//                   }
//             } else if (string[i] == '.') {
//                   afterDecimalPoint = 1;
//             } else {
//                   printf("SE ROMPIO\n");
//                   break;
//             }
//             i++;
//       }
//       return res * negative;
// }
