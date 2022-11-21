#include <pin.h>
#include <wait.h>

enum {
    BLINK_DELAY_MS = 1000,
};

int main (void) {
    /* Set PIN 7 of PORTB (D0) for output. */
    pin_setup(D0, OUTPUT, LOW);

    while(1) {
        /* Set PIN 0 high to turn LED ON. */
        pin_set_state(D0, HIGH);
        wait(BLINK_DELAY_MS);

        /* Set PIN 0 low to turn LED OFF. */
        pin_set_state(D0, LOW);
        wait(BLINK_DELAY_MS);
    }

    return 0;
}
