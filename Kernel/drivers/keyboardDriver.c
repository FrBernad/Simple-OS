#include <keyboardDriver.h>
#include <keyboardInfo.h>
#include <keys.h>
#include <screens.h>
#include <utils.h>
#include <interrupts.h>
#include <staticQueue.h>
#include <stdint.h>
#include <buffer.h>
#include <sizeof.h>

static uint8_t action(uint8_t scanCode);

static char pressCodes[KEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
    {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('},
    {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {0, 0}, {'q', 'Q'}, 
    {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, 
    {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, 
    {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, {'s', 'S'}, 
    {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'},
    {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, 
    {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, 
    {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static uint8_t scanCode, currentAction, specialChars = 0, capsLock = 0, l_ctrl = 0;
static char buffer1[MAX_SIZE]={0},buffer2[MAX_SIZE]={0};
static t_queue buffers[MAX_SCREENS] = {{buffer1, 0, -1, 0, MAX_SIZE, CHAR}, { buffer2, 0, -1, 0, MAX_SIZE, CHAR }};
static t_queue * currentBuffer;

char cs0=CHANGE_SCREEN_0,cs1=CHANGE_SCREEN_1,clearS=CLEAR_SCREEN;

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

                        case CAPS_LCK_SC:
                              capsLock = capsLock == 1 ? 0 : 1;
                              break;

                        case L_CONTROL_SC:
                              l_ctrl = 1;
                              break;

                        default:
                              if (pressCodes[scanCode][0]!=0) {
                                    if (l_ctrl) {
                                          if (pressCodes[scanCode][0] == '0' + SCREEN_0) {
                                                queueInsert(currentBuffer, &cs0);
                                                //currentBuffer->buffer[currentBuffer->index] = CHANGE_SCREEN_0;
                                          } else if (pressCodes[scanCode][0] == '0' + SCREEN_1) {
                                                queueInsert(currentBuffer, &cs1);
                                                // currentBuffer->buffer[currentBuffer->index] = CHANGE_SCREEN_1;
                                          } else if (pressCodes[scanCode][0] == 'l') {
                                                queueInsert(currentBuffer, &clearS);
                                                //  currentBuffer->buffer[currentBuffer->index] = CLEAR_SCREEN;
                                          }
                                    } else {
                                          // char character;
                                          if (!IS_LETTER(pressCodes[scanCode][0])) {
                                               // character = pressCodes[scanCode][specialChars];
                                               // currentBuffer->buffer[currentBuffer->index] = character;
                                               queueInsert(currentBuffer, &pressCodes[scanCode][specialChars]);
                                          } else {
                                               // character = pressCodes[scanCode][ABS(capsLock - (specialChars))];
                                                //currentBuffer->buffer[currentBuffer->index] = character;
                                               queueInsert(currentBuffer, &pressCodes[scanCode][ABS(capsLock - (specialChars))]);
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

//a b c d e f 
char getchar(){
     char c=0;
   //  while(queueIsEmpty(currentBuffer)){
     //      _hlt();
    // }
     queueRemoveData(currentBuffer, &c);
     
     return c;
}

void changeBuffer(t_screenID screen){
      // printString("changed buffer to screen: ");
      // printInt((int)screen);
      // putchar('\n');
      currentBuffer = &buffers[screen];
}

static uint8_t action(uint8_t scanCode) {
      if (scanCode >= 0x01 && scanCode <= 0x3A)
            return PRESSED;
      else if (scanCode >= 0x81 && scanCode <= 0xBA)
            return RELEASED;

      return ERROR;
}

