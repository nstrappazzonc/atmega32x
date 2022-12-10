#include <pin.h>
#include <wait.h>

const uint8_t scale[] PROGMEM = {239,226,213,201,190,179,169,160,151,142,134,127};

int main(void) {
    uint8_t brightness = 0;
    // uint8_t fadein = 1;

    pin_setup(B7, OUTPUT, LOW);

    while(1) {
        

        for (int n=0; n<=12; n++) {
          // unsigned long top = F_CPU / frequency / 2 - 1;
          int octave = 4;
          int prescaler = 10 - (octave + n/12);
          if (prescaler<1 || prescaler>9) prescaler = 0;

          brightness = pgm_read_byte(&scale[n % 12]) - 1;
          TCCR0A |= ( 1 << COM0A0 | 1 << COM0B0 );
          // TCCR0A |= ( 1 << WGM01 | 1 << COM0A0 );
          OCR0A = brightness;
          TCCR0B = prescaler << CS00; // antes 1 << CS01
          // pin_set_state(B7, brightness);
          wait(500);
        }

        // Esto si para el timer.
        TCCR0A &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
        wait(10000);
    }

    return 0;
}
