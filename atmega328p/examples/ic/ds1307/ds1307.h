#include <avr/io.h>
#include "i2c.h"

void RTCSet(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void RTCGet(uint8_t* second, uint8_t* minute, uint8_t* hour, uint8_t* day, uint8_t* date, uint8_t* month, uint8_t* year);
uint8_t lastDigit(uint8_t n);
uint8_t firstDigit(uint8_t n);