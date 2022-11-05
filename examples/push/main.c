#include <avr/io.h>
#include <util/delay.h>         

int main(void) {
    DDRB |=   1 << 5;  // Configuring PB5 as Output
    DDRB &= ~(1 << 0); // Configuring PB0 as Input

    while (1) {
        if ((PINB&(1<<0)) == 1) { // Lee el valor del PIN.
            PORTB |= 1<<5; // Escribe HIGH, para encender el LED.
        } else {
            PORTB &= ~(1<<5); // Escribe LOW, para apagar el LED.
        }
    }
}
