// #include <wait.h>
#include <pin.h>
// #include "framework/serial.h"

void setup(void);
void loop(void);
// void printOut1(int);

void setup() {
    // serial_init(57600);
    // serial_string("Hola mundo!\n\r");
    // printOut1(PINB);
    // serial_string("\n\r");
    // printOut1(PINB0);
    // serial_string("\n\r");
    // printOut1(PINB & (1 << PINB0));
    // serial_string("\n\r");

    pin_setup(8, INPUT, LOW);
    pin_setup(13, OUTPUT, LOW);
}

void loop() {
    // int dataPin = 9;
    // int latchPin = 10;
    // int clockPin = 11;

    // uint8_t led_pattern[5]={
    //                     0b10000000,
    //                     0b01000000,
    //                     0b00100000,
    //                     0b11110000,
    //                     0b00001000,
    //                     // 0b11111100,
    //                     // 0b11111110,
    //                     // 0b11111111
    //                 };
   

    while (1) {
        // for(int i=0;i<5;i++) {
        //     shift_out(dataPin,clockPin,latchPin,led_pattern[i]);
        //     wait(1000);
        // }

        if (pin_get(8) == 1) {
            pin_set_state(13, HIGH);
        } else {
            pin_set_state(13, LOW);
        }
    }
}

int main(void) {
    setup();

    for (;;) {
        loop();
    }

    return 0;
}

// void printOut1(int c) {
//     for (int bits = 7; bits > -1; bits--) {
//      // Compare bits 7-0 in byte
//         if (c & (1 << bits)) {
//             serial_char('1');
//         }
//         else {
//             serial_char('0');
//         }
//     }
// }
