#include <pin.h>
#include <wait.h>

enum {
    BLINK_DELAY_MS = 1000,
};

int main (void) {
    /* Set PIN 7 of PORTB (B7) for output. */
    pin_setup(B7, OUTPUT, LOW);

    while(1) {
        /* Set PIN 0 high to turn LED ON. */
        pin_set_state(B7, HIGH);
        wait(BLINK_DELAY_MS);

        /* Set PIN 0 low to turn LED OFF. */
        pin_set_state(B7, LOW);
        wait(BLINK_DELAY_MS);
    }

    return 0;
}
