#include <avr/io.h>
#include <util/delay.h>

// Define Register Select pin
#define RS (1<<PD2)
// Define Enable signal pin
#define EN (1<<PD3)

void LCDInit(void);
void LCDLatch(void);
void LCDCmd(uint8_t cmd);
void LCDClear(void);
void LCDChar(uint8_t data);
void LCDPrint(char *str);
void LCDSetCursor(uint8_t x, uint8_t y);
void LCDClear(void);

int main(void) {
    LCDInit();

    while (1) {
        LCDSetCursor(1,1);
        LCDPrint("ABCD");
        _delay_ms(1000);
        LCDClear();
        LCDSetCursor(2,1);
        LCDPrint("1234");
        _delay_ms(1000);
    };

    return 0;
}

void LCDInit(void) {
    // Initialize PORTs for LCD
    DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);
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
    PORTD |= EN;     // Send high
    _delay_us(500); // Wait
    PORTD &= ~EN;    // Send low
    _delay_us(500); // Wait
}

void LCDCmd(uint8_t cmd) {
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0);  // send high nibble
    PORTD &= ~RS; //send 0 to select command register
    LCDLatch();          //latch the data
    PORTD = (PORTD & 0x0F) | (cmd<<4);    //send low nibble
    LCDLatch();
}

void LCDClear(void) {
    LCDCmd(0x01);
    _delay_ms(5);
}

void LCDChar(uint8_t data) {
    // Send high nibble
    PORTD = (PORTD & 0x0F) | (data & 0xF0);
    // Send 1 to select data register
    PORTD |= RS;
    LCDLatch();
    // Send high nibble
    PORTD = (PORTD & 0x0F) | (data << 4);
    LCDLatch();
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
