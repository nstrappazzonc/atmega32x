#include <avr/io.h>
#define F_SCL 100000L

void I2CInit(void);
void I2CWait(void);
void I2CStart(void);
void I2CStop(void);
void I2CWrite(uint8_t data);
uint8_t I2CReadACK(void);
uint8_t I2CReadNoACK(void);
