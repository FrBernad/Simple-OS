#include <buffer.h>
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

uint64_t pow(uint64_t x, uint64_t y) {
      if (y == 0)
            return 1;

      for (int i = 1; i < y; i++) {
            x *= x;
      }

      return x;
}

uint8_t BSDToInt(uint8_t num) {
      uint8_t low = num & 0x0F;
      uint8_t high = num & 0xF0;
      high >>= 4;
      return high * 10 + low;
}

void strtok(char *string, char *result, const char delim) {
      static int currentIndex = 0;
      static char ogString[BUFFER_SIZE] = {0};

      if (result == 0) {
            currentIndex=0;
            for (int i = 0; i < BUFFER_SIZE && ogString[i] != 0; i++) {
                  ogString[i] = 0;
            }
            return;
      }

      for (int i = 0; i < BUFFER_SIZE && result[i] != 0; i++) {
            result[i] = 0;
      }

      if (string != 0) {
            for (int i = 0; string[i] != 0 && i < BUFFER_SIZE; i++) {
                  ogString[i] = string[i];
            }
            for (; ogString[currentIndex] != 0 && ogString[currentIndex] == delim && currentIndex < BUFFER_SIZE; currentIndex++);
            for (int i = 0; ogString[currentIndex] != 0 && ogString[currentIndex] != delim && currentIndex < BUFFER_SIZE; currentIndex++, i++) {
                  result[i] = string[currentIndex];
            }
      } else {
            for (;ogString[currentIndex] != 0 && ogString[currentIndex] == delim && currentIndex < BUFFER_SIZE; currentIndex++);
            for (int i = 0; ogString[currentIndex] != 0 && ogString[currentIndex] != delim; currentIndex++, i++) {
                  result[i] = ogString[currentIndex];
            }
      }

      if(currentIndex == BUFFER_SIZE && ogString[currentIndex]==0){
            result[0]=-1;
      }

}

uint64_t strToInt(char *str, int * error) {
      uint64_t num = 0;
      *error = 0;
      for (int i = 0; str[i] != 0; i++) {
            if (IS_NUMBER(str[i])) {
                  num *= 10;
                  num += str[i] - '0';
            } else {
                  *error = 1;
                  return -1;
            }
      }
      return num;
}

uint8_t stringcmp(char *str1, char *str2) {
      uint8_t i;
      if (*str1 == 0 || *str2 == 0) {
            return 0;
      }
      for (i = 0; str1[i] != 0 && str2[i] != 0; i++) {
            if (str1[i] != str2[i])
                  return 0;
      }
      return 1;
}

void cleanBuffer(t_buffer * buffer){
      for (int i = 0; buffer->buffer[i] != 0; i++)
      {
            buffer->buffer[i]=0;
      }
      buffer->index=0;
}

void cleanString(char * str) {
      for (int i = 0; str[i] != 0; i++) {
            str[i] = 0;
      }
}
