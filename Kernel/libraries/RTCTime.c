#include <RTCTime.h>
#include <lib.h>
#include <utils.h>

uint8_t getDecimalTimeInfo(uint8_t info){
    return BSDToInt(getBSDTimeInfo(info));
}
