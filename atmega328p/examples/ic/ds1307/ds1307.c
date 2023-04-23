#include "ds1307.h"

void RTCSet(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
    I2CStart();
    I2CWrite(0b11010000);
    I2CWrite(0b00000000);
    I2CWrite((firstDigit(second) << 4) | lastDigit(second));
    I2CWrite((firstDigit(minute) << 4) | lastDigit(minute));
    I2CWrite((firstDigit(hour) << 4) | lastDigit(hour));
    I2CWrite(day);
    I2CWrite((firstDigit(date) << 4) | lastDigit(date));
    I2CWrite(month);
    I2CWrite((firstDigit(year) << 4) | lastDigit(year));
    I2CStop();
}

void RTCGet(uint8_t* second, uint8_t* minute, uint8_t* hour, uint8_t* day, uint8_t* date, uint8_t* month, uint8_t* year) {
    I2CStart();
    I2CWrite(0b11010000);
    I2CWrite(0b00000000);
    I2CStop();
    I2CStart();
    I2CWrite(0b11010001);
    *second = I2CReadACK();
    *minute = I2CReadACK();
    *hour   = I2CReadACK();
    *day    = I2CReadACK();
    *date   = I2CReadACK();
    *month  = I2CReadACK();
    *year   = I2CReadNoACK();
    I2CStop();
}

uint8_t lastDigit(uint8_t n) {
	return n % 10;
}

uint8_t firstDigit(uint8_t n) {
	while(n >= 10) {
		n = n / 10;
	}
	return n;
}
