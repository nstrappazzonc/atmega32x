#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void LCDInit(void) {
    // Initialize PORTs for LCD
    DDRD |= (1<<PD2); // LCD Pin Number 04, Pin Name RS, Register.
    DDRD |= (1<<PD3); // LCD Pin Number 06, Pin Name E, Enable.
    DDRD |= (1<<PD4); // LCD Pin Number 11, Pin Name D4, Data Bus.
    DDRD |= (1<<PD5); // LCD Pin Number 12, Pin Name D5, Data Bus.
    DDRD |= (1<<PD6); // LCD Pin Number 13, Pin Name D6, Data Bus.
    DDRD |= (1<<PD7); // LCD Pin Number 14, Pin Name D7, Data Bus.

    // Send Pulse to Latch the data
    LCDLatch();
    // Delay for stable power
    _delay_ms(2);
    // Command to set up the LCD
    LCDCmd(0x33);
    _delay_us(100);
    LCDCmd(0x32);
    _delay_us(100);
    LCDCmd(0x28);    // 2 lines 5x7 matrix dot
    _delay_us(100);
    LCDCmd(0x0C);    // display ON, Cursor OFF
    _delay_us(100);
    // Clear LCD
    LCDCmd(0x01);
    _delay_ms(20);
    // Shift cursor to right
    LCDCmd(0x06);
    _delay_ms(1);
}

void LCDLatch(void) {
    PORTD |= (1<<PD3);  // Send high.
    _delay_us(500);     // Wait.
    PORTD &= ~(1<<PD3); // Send low.
    _delay_us(500);     // Wait.
}

void LCDCmd(uint8_t cmd) {
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0); // Send high nibble
    PORTD &= ~(1<<PD2);                    // Send 0 to select command register
    LCDLatch();                            // Latch the data
    PORTD = (PORTD & 0x0F) | (cmd<<4);     // Send low nibble
    LCDLatch();
}

void LCDClear(void) {
    LCDCmd(0x01);
    _delay_ms(5);
}

void LCDChar(uint8_t data) {
    // Send high nibble.
    PORTD = (PORTD & 0x0F) | (data & 0xF0);
    // Send 1 to select data register.
    PORTD |= (1<<PD2);
    LCDLatch();
    // Send high nibble.
    PORTD = (PORTD & 0x0F) | (data << 4);
    LCDLatch();
}

void LCDCreateCustomChar(uint8_t x, uint8_t y, uint8_t n, unsigned char *cc) {
    if(n<8) {
        LCDCmd(0x40 + (n*8));
        for(int i=0;i<8;i++) {
            LCDChar(cc[i]);
        }
        LCDSetCursor(x,y);
        LCDChar(n);
    }
}

void LCDPrint(char *str) {
    for(int i=0;str[i]!=0;i++) {
        LCDChar(str[i]);
    }
}

void LCDSetCursor(uint8_t x, uint8_t y) {
    uint8_t firstcharadr[] = {0x80, 0xC0, 0x94, 0xD4};
    LCDCmd(firstcharadr[y-1] + x-1);
    _delay_us(1000);
}
