#include <util/delay.h>
#include "usb.h"
#include "keys.h"

int main() {
    DDRD |=   1 << 7;  // Configuring PB5 as Output
    DDRB &= ~(1 << 0); // Configuring PB0 as Input

    USB_Init();

    while (1) {
        if ((PINB&(1<<0)) == 1) { // Lee el valor del PIN.
            PORTD |= 1<<7; // Escribe HIGH, para encender el LED.
            // shift
            press_key(KEY_LEFTSHIFT);
        } else {
            PORTD &= ~(1<<7); // Escribe LOW, para apagar el LED.
            release_key(KEY_LEFTSHIFT);
            release_all_keys();
        }
        usb_keyboard_send();
    }
}
