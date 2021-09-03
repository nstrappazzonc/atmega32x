#include <util/delay.h>
#include "shift.h"

//Sends a clock pulse on SH_CP line
void shift_pulse(uint8_t clockPin) {
    //Pulse the Shift Clock
    pin_set_state(clockPin, HIGH);
    pin_set_state(clockPin, LOW);
}

//Sends a clock pulse on ST_CP line
void shift_latch(uint8_t latchPin) {
    //Pulse the Store Clock
    pin_set_state(latchPin, HIGH);
    _delay_loop_1(1);
    pin_set_state(latchPin, LOW);
    _delay_loop_1(1);
}

void shift_out(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t bitOrder) {
    pin_setup(clockPin, OUTPUT, LOW);
    pin_setup(latchPin, OUTPUT, LOW);
    pin_setup(dataPin, OUTPUT, LOW);

    //Send each 8 bits serially
    //Order is MSB first
    for(uint8_t i=0; i<8; i++) {
        //Output the data on DS line according to the
        //Value of MSB
        if(bitOrder & 0b10000000) {
           //MSB is 1 so output high
           pin_set_state(dataPin, HIGH);
        } else {
           //MSB is 0 so output high
           pin_set_state(dataPin, LOW);
        }

        shift_pulse(clockPin);  //Pulse the Clock line
        bitOrder = bitOrder << 1;  //Now bring next bit at MSB position
    }

    //Now all 8 bits have been transferred to shift register
    //Move them to output latch at one
    shift_latch(latchPin);
}
