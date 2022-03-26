#include <avr/io.h>
// #include <util/delay.h>
// #include <pin.h>
// #include <wait.h>
#include <util/delay.h>

enum {
    BLINK_DELAY_MS = 1000,
};

int main (void) {
    /* set pin 0 of PORTD (PC7) for output*/
    DDRB |= _BV(DDB0);
    // pin_setup(PC7, OUTPUT, LOW);

    while(1) {
        /* set pin 0 high to turn led on */
        PORTB |= _BV(PORTB7);
        // pin_set_state(PC7, HIGH);
        _delay_ms(BLINK_DELAY_MS);
        // wait(BLINK_DELAY_MS);

        /* set pin 0 low to turn led off */
        PORTB &= ~_BV(PORTB7);
        // pin_set_state(PC7, LOW);
        _delay_ms(BLINK_DELAY_MS);
        // wait(BLINK_DELAY_MS);
    }

    return 0;
}
