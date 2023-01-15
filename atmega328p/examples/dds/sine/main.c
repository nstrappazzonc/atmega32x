#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRD |= _BV(PD6);

    TCCR0A |= _BV(COM0A0) | _BV(WGM01);
    TCCR0B |= _BV(CS00) | _BV(CS01);

    int i = 0;

    while(1) {
        for(i=120;i<180;i++){
            OCR0A = i;
            _delay_ms(15);
        }
        for(i=180;i>120;i--){
            OCR0A = i;
            _delay_ms(15);
        }
    }

    return 0;
}
