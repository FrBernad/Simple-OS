#include <utils.h>

//sacada de nvconsole
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base) {
      char *p = buffer;
      char *p1, *p2;
      uint32_t digits = 0;

      //Calculate characters for each digit
      do {
            uint32_t remainder = value % base;
            *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
            digits++;
      } while (value /= base);

      // Terminate string in buffer.
      *p = 0;

      //Reverse string in buffer.
      p1 = buffer;
      p2 = p - 1;
      while (p1 < p2) {
            char tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;
            p1++;
            p2--;
      }

      return digits;
}

uint64_t pow(uint64_t x, uint64_t y){
      if(y==0)
            return 1;

      for (int i = 1; i < y; i++)
      {
            x*=x;
      }

      return x;
}

uint64_t strToInt(char * str){
      uint64_t num = 0;
      for (int i = 0; str[i] != 0 ; i++)
      {
            if (IS_NUMBER(str[i])){
                  num *=10;
                  num += str[i] - '0';
            }
            else{
                  return -1;
            }
      }
      return num;
}

// float strToFloat(char *string) {
//       float res = 0.0F;
//       int afterDecimalPoint = 0, i = 0, negative = 0;
//       float div = 1;

//       if (string[i] == '-') {
//             negative = 1;
//             i++;
//       }

//       while (string[i] != '\0') {
//             if (IS_NUMBER(string[i])) {
//                   if (!afterDecimalPoint) {
//                         res = 10;
//                         res += string[i] - '0';
//                   } else {
//                         div = 10;
//                         res += (float)(string[i] - '0') / div;
//                   }
//             } else if (string[i] == '.') {
//                   afterDecimalPoint = 1;
//             } else {
//                   break;
//             }
//             i++;
//       }

//       if (negative)
//             return res * -1;
//       return res;
// }

uint8_t BSDToInt(uint8_t num) {
      uint8_t low = num & 0x0F;
      uint8_t high = num & 0xF0;
      high >>= 4;
      return high * 10 + low;
}