#include "i2c.h"

void I2CInit(void) {
    // Set bit rate to 100kHz.
    TWBR  = ((F_CPU / F_SCL) - 16) / 2;
    // Set to use 32.768kHz clock.
    TWSR  = (1<<TWPS0) | (1<<TWPS1);
    // Enable I2C
    TWCR |= (1<<TWEN);
}

void I2CWait(void) {
    while(!(TWCR & (1<<TWINT)));
}

void I2CStart(void) {
    TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
    I2CWait();
}

void I2CStop(void) {
    TWCR |= ((1<<TWINT) | (1<<TWEN) | (1<<TWSTO));
}

void I2CWrite(uint8_t data) {
    TWDR = data;
    TWCR = ((1<<TWINT) | (1<<TWEN));
    I2CWait();
}

uint8_t I2CReadACK(void) {
    TWCR = ((1<<TWINT) | (1<<TWEN) | (1<<TWEA));
    I2CWait();
    return TWDR;
}

uint8_t I2CReadNoACK(void) {
    TWCR = ((1<<TWINT) | (1<<TWEN));
    I2CWait();
    return TWDR;
}
