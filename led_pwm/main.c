/*
 * MCU: ATmega32U4
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    uint8_t brightness = 0;
    uint8_t fadein = 1;

    //Initialize PWM Channel 0
    //Set 8-bit fast PWM mode
    TCCR0A |= (1 << WGM00)|(1 << WGM01)|(1 << COM0A1);
    TCCR0B = 1 << CS00;
    //Initialize port PB7 as output
    DDRB |= (1 << PB7);

    while(1) {
        OCR0A = brightness;

        if(fadein)
            brightness += 5;
        else
            brightness -= 5;

        if(brightness == 0 || brightness == 255) {
            fadein = !fadein;
        }

        _delay_ms(50);
    }
}
