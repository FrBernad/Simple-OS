#ifndef KEYS_H
#define KEYS_H

#define KEYS 59

typedef enum {
      PRESSED = 1,
      RELEASED = 2,
      ERROR = -1
} t_keyState;

typedef enum {
      L_SHFT_SC = 0x2A,
      R_SHFT_SC = 0x36,
      B_SPACE_SC = 0x0E,
      SPACE_SC = 0x39,
      CAPS_LCK_SC = 0x3A,
      ENTER_SC = 0x1C,
      L_CONTROL_SC = 0x1D,
} t_specialKeySC;

typedef enum {
      CHANGE_SCREEN_0 = 0x05,
      CHANGE_SCREEN_1 = 0x06,
      CLEAR_SCREEN = 0x16,
      SNAP_SHOT = 0x7,
} t_specialKeyCode;

#endif