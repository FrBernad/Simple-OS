#include <keyboardDriver.h>
#include <keyboardInfo.h>
#include <keys.h>
#include <screens.h>
#include <utils.h>
#include <stdint.h>
#include <buffer.h>

static uint8_t action(uint8_t scanCode);

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
static t_buffer * currentBuffer = &buffers[SCREEN_1 - 1];

void keyboardHandler() {
      if (hasKey()) {
            scanCode = getKey();
            currentAction = action(scanCode);
            if (currentAction == PRESSED) {
                  if(currentBuffer)
                  switch (scanCode) {
                        case L_SHFT_SC:
                        case R_SHFT_SC:
                              specialChars = 1;
                              break;

                        case ENTER_SC:
                              currentBuffer->buffer[currentBuffer->index] = ENTER;
                              break;

                        case CAPS_LCK_SC:
                              capsLock = capsLock == 1 ? 0 : 1;
                              break;

                        case SPACE_SC:
                              currentBuffer->buffer[currentBuffer->index] = SPACE;
                              break;

                        case L_CONTROL_SC:
                              l_ctrl = 1;
                              break;

                        case B_SPACE_SC:
                              currentBuffer->buffer[currentBuffer->index] = B_SPACE;
                              break;

                        default:
                              if (pressCodes[scanCode][0]!=0) {
                                    if (l_ctrl) {
                                          if (pressCodes[scanCode][0] == '0' + SCREEN_0) {
                                                currentBuffer->buffer[currentBuffer->index] = CHANGE_SCREEN_0;
                                          } else if (pressCodes[scanCode][0] == '0' + SCREEN_1) {
                                                currentBuffer->buffer[currentBuffer->index] = CHANGE_SCREEN_1;
                                          } else if (pressCodes[scanCode][0] == 'l') {
                                                currentBuffer->buffer[currentBuffer->index] = CLEAR_SCREEN;
                                          }
                                    } else {
                                          char character;
                                          if (!IS_LETTER(pressCodes[scanCode][0])) {
                                                character = pressCodes[scanCode][specialChars];
                                                currentBuffer->buffer[currentBuffer->index] = character;
                                          } else {
                                                character = pressCodes[scanCode][ABS(capsLock - (specialChars))];
                                                currentBuffer->buffer[currentBuffer->index] = character;
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

char getchar(){
     char c = currentBuffer->buffer[0];
     currentBuffer->buffer[0]=0;
     return c;
}

void changeBuffer(t_applicationID app){
      currentBuffer = &buffers[app];
}

static uint8_t action(uint8_t scanCode) {
      if (scanCode >= 0x01 && scanCode <= 0x3A)
            return PRESSED;
      else if (scanCode >= 0x81 && scanCode <= 0xBA)
            return RELEASED;

      return ERROR;
}

