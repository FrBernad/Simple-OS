#include <keyboardDriver.h>
#include <keyboardInfo.h>
#include <keys.h>
#include <screens.h>
#include <utils.h>
#include <buffer.h>

static uint8_t action(uint8_t scanCode);
// static void cleanBuffer();
// static void changeBuffer(int screen);

static const char pressCodes[KEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
    {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('},
    {'0', ')'}, {'-', '_'}, {'=', '+'}, {0, 0}, {0, 0}, {'q', 'Q'}, 
    {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, 
    {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, 
    {']', '}'}, {0, 0}, {0, 0}, {'a', 'A'}, {'s', 'S'}, 
    {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'},
    {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, 
    {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, 
    {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

static uint8_t scanCode, currentAction, specialChars = 0, capsLock = 0, l_ctrl = 0;

static t_buffer buffers[MAX_SCREENS] = {{{0}, 0}, {{0}, 0}};
static t_buffer * currentBuffer = &buffers[SCREEN_2 - 1];

void keyboard_handler() {
      if (hasKey()) {
            scanCode = getKey();
            currentAction = action(scanCode);
            if (currentAction == PRESSED) {
                  switch (scanCode) {
                        case L_SHFT_SC:
                        case R_SHFT_SC:
                              specialChars = 1;
                              break;

                        case ENTER_SC:
                              currentBuffer->buffer[currentBuffer->index++] = ENTER;
                              break;

                        case CAPS_LCK_SC:
                              capsLock = capsLock == 1 ? 0 : 1;
                              break;

                        case SPACE_SC:
                              currentBuffer->buffer[currentBuffer->index++] = SPACE;
                              break;

                        case L_CONTROL_SC:
                              l_ctrl = 1;
                              break;

                        case B_SPACE_SC:
                              currentBuffer->buffer[currentBuffer->index++] = B_SPACE;
                              break;

                        case EQUAL_SC:
                        default:
                              if (pressCodes[scanCode][0]) {
                                    if (l_ctrl) {
                                          if (pressCodes[scanCode][0] == '0' + SCREEN_1) {
                                                currentBuffer->buffer[currentBuffer->index++] = CHANGE_SCREEN_1;
                                          } else if (pressCodes[scanCode][0] == '0' + SCREEN_2) {
                                                currentBuffer->buffer[currentBuffer->index++] = CHANGE_SCREEN_2;
                                          } else if (pressCodes[scanCode][0] == 'l') {
                                                currentBuffer->buffer[currentBuffer->index++] = CLEAR_SCREEN;
                                          }
                                          l_ctrl = 0;
                                    } else {
                                          char character;
                                          if (!IS_LETTER(pressCodes[scanCode][0])) {
                                                character = pressCodes[scanCode][specialChars];
                                                currentBuffer->buffer[currentBuffer->index++] = character;
                                          } else {
                                                character = pressCodes[scanCode][ABS(capsLock - (specialChars))];
                                                currentBuffer->buffer[currentBuffer->index++] = character;
                                          }
                                    }
                              }
                  }
            } else if (currentAction == RELEASED) {
                  switch (scanCode) {
                        case L_SHFT_SC | 0x80:  //for realease code
                        case R_SHFT_SC | 0x80:
                              specialChars = 0;
                              break;

                        case L_CONTROL_SC | 0x80:
                              l_ctrl = 0;
                              break;
                  }
            }
      }
}

char getChar(){
      char c = currentBuffer->buffer[0];
     for (int i = 0; i < BUFFER_SIZE - 1; i++)
     {
           currentBuffer->buffer[i] = currentBuffer->buffer[i+1];
     }
     currentBuffer->buffer[BUFFER_SIZE-1]=0;
      return c;
}

// void keyboard_handler() {
//       if (hasKey()) {
//             scanCode = getKey();
//             currentAction = action(scanCode);
//             if (currentAction == PRESSED) {
//                   switch (scanCode) {
//                         case L_SHFT:
//                         case R_SHFT:
//                               specialChars = 1;
//                               break;

//                         case ENTER:
//                              /* if (currentScreen == SCREEN_2) {
//                                     newLine();
//                                     checkCommand();
//                                     printString("User $ ");
//                                     cleanBuffer();
//                               }*/
//                               break;

//                         case CAPS_LCK:
//                               if (currentScreen == SCREEN_2) {
//                                     scrollDownScreen();
//                                     capsLock = capsLock == 1 ? 0 : 1;
//                               }
//                               break;

//                         case SPACE:
//                               currentBuffer->buffer[currentBuffer->index++] = ' ';
//                               putChar(' ');
//                               break;

//                         case L_CONTROL:
//                               l_ctrl = 1;
//                               break;

//                         case B_SPACE:
//                               currentBuffer->buffer[currentBuffer->index] = 0;
//                               if (currentBuffer->index > 0) {
//                                     currentBuffer->index--;
//                               }
//                               deletechar();
//                               break;

//                         case EQUAL:
//                               if (currentScreen == SCREEN_1) {
//                                     evaluate(currentBuffer->buffer);
//                                     cleanBuffer();
//                                     newLine();
//                                     printString("Calculator $ ");
//                               }
//                         default:
//                               if (pressCodes[scanCode][0]) {
//                                     if (l_ctrl) {
//                                           if (pressCodes[scanCode][0] == '0' + SCREEN_1) {
//                                                changeFocus(SCREEN_1);
//                                                printString("Calculator $ ");
//                                           } 
//                                           else if (pressCodes[scanCode][0] == '0' + SCREEN_2) {
//                                                 changeFocus(SCREEN_2);
//                                                 printString("User $ ");
//                                           } 
//                                           else if (pressCodes[scanCode][0] == 'l') {
//                                                 clearScreen();
//                                                 cleanBuffer();
//                                                 if (currentScreen == SCREEN_1)
//                                                       printString("Calculator $ ");
//                                                 else if(currentScreen == SCREEN_2)
//                                                       printString("User $ ");
//                                           }
//                                           l_ctrl = 0;
//                                     } 
//                                     else {
//                                           if (currentBuffer->index == BUFFER_SIZE) {
//                                                 cleanBuffer();
//                                           }

//                                           char character;

//                                           if (!IS_LETTER(pressCodes[scanCode][0])) {
//                                                 character = pressCodes[scanCode][specialChars];

//                                                 if (currentScreen == SCREEN_1) {
//                                                       if (IS_OPPERAND(character) || IS_NUMBER(character)) {
//                                                             currentBuffer->buffer[currentBuffer->index++] = character;
//                                                             putChar(character);
//                                                       }
//                                                 }

//                                                 else if (currentScreen == SCREEN_2) {
//                                                       currentBuffer->buffer[currentBuffer->index++] = character;
//                                                       putChar(character);
//                                                 }
//                                           } else {
//                                                 if (currentScreen == SCREEN_2) {
//                                                       character = pressCodes[scanCode][ABS(capsLock - (specialChars))];
//                                                       currentBuffer->buffer[currentBuffer->index++] = character;
//                                                       putChar(character);
//                                                 }
//                                           }
//                                     }
//                               }
//                   }
//             } 
//             else if (currentAction == RELEASED) {
//                   switch (scanCode) {
//                         case L_SHFT | 0x80:  //for realease code
//                         case R_SHFT | 0x80:
//                               specialChars = 0;
//                               break;

//                         case L_CONTROL | 0x80:
//                               l_ctrl = 0;
//                               break;
//                   }
//             }
//       }
// }

// static void changeBufffer(int screen) {
//       currentBuffer = &buffers[screen - 1];
// }

static uint8_t action(uint8_t scanCode) {
      if (scanCode >= 0x01 && scanCode <= 0x3A)
            return PRESSED;
      else if (scanCode >= 0x81 && scanCode <= 0xBA)
            return RELEASED;

      return ERRROR;
}

// static void cleanBuffer() {
//       for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
//             currentBuffer->buffer[i] = 0;
//       }
//       currentBuffer->index = 0;
// }
