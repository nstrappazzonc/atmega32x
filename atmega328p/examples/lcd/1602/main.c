#include <util/delay.h>
#include "lcd.h"

int main(void) {
    unsigned char cc01[8] = {0b11111,
                             0b11111,
                             0b11111,
                             0b11111,
                             0b11111,
                             0b11111,
                             0b11111,
                             0b11111};
    unsigned char cc02[8] = {0b00000,
                             0b01010,
                             0b11111,
                             0b11111,
                             0b11111,
                             0b01110,
                             0b00100,
                             0b00000};

    LCDInit();

    while (1) {
        LCDClear();
        LCDSetCursor(1,1);
        LCDPrint("ABCD");
        _delay_ms(1000);
        LCDClear();
        LCDSetCursor(1,2);
        LCDPrint("1234");
        _delay_ms(1000);
        LCDClear();
        LCDCreateCustomChar(1,1,1,cc01);
        LCDCreateCustomChar(2,1,2,cc02);
        _delay_ms(1000);
    }
    return 0;
}
