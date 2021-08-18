// #include <avr/io.h>
// #include <util/delay.h>
#include <pin.h>
#include <wait.h>

enum {
    BLINK_DELAY_MS = 1000,
};

int main (void) {
    /* set pin 0 of PORTD (PD0) for output*/
    // DDRD |= _BV(DDD0);
    pin_setup(PD0, OUTPUT, LOW);

    while(1) {
        /* set pin 0 high to turn led on */
        // PORTD |= _BV(PORTD0);
        pin_set_state(PD0, HIGH);
        // _delay_ms(BLINK_DELAY_MS);
        wait(BLINK_DELAY_MS);

        /* set pin 0 low to turn led off */
        // PORTD &= ~_BV(PORTD0);
        pin_set_state(PD0, LOW);
        // _delay_ms(BLINK_DELAY_MS);
        wait(BLINK_DELAY_MS);
    }

    return 0;
}
