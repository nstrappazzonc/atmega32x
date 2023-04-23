#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "lcd.h"
#include "ds1307.h"

int main(void) {
    LCDInit();
    LCDClear();
    I2CInit();

    uint8_t second, minute, hour, day, date, month, year;
    char buffer[20];
    char* days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    RTCSet(35, 45, 17, 6, 24, 4, 23);

    while(1) {
        RTCGet(&second, &minute, &hour, &day, &date, &month, &year);
        LCDSetCursor(1,1);
        sprintf(buffer, "%02x/%02x/%02x %3s", year, month, date, days[day-1]);
        LCDPrint(buffer);
        LCDSetCursor(1,2);
        sprintf(buffer, "%02x:%02x:%02x", (hour & 0b00011111), minute, second);
        LCDPrint(buffer);
        _delay_ms(1000);
    }

    return 0;
}
