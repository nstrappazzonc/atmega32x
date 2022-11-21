#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <pin.h>
#include <wait.h>

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

volatile long timer0_toggle_count;
long toggle_count = 0;
void toneSetup();
void tone(unsigned int frequency, unsigned long duration);

const uint8_t scale[] PROGMEM = {
  239, // Note C
  225, // Note CS
  213, // Note_D
  201, // Note_DS
  190, // Note_E
  179, // Note_F
  169, // Note_FS
  159, // Note_G
  150, // Note_GS
  142, // Note_A
  134, // Note_AS
  127, // Note_B
};

int main (void) {
  pin_setup(B7, OUTPUT, LOW);
  toneSetup();
  // while (1) {
    // for (int n = 0; n < 12; n++) {
      tone(2253, 0);
      wait(1000);
    // }

    // wait(1000);
  // }

  return 0;
}

void toneSetup() {
  // sei();

  TCCR0A = 0;
  TCCR0B = 0;

  TCCR0A |= ( 1 << WGM00 | 1 << COM0A1 | 1 << COM0B1);
  TCCR0B |= ( 1 << CS00 );

  // bitWrite(TCCR0A, WGM01, 1);
  // bitWrite(TCCR0B, CS00, 1);
}

void tone(unsigned int frequency, unsigned long duration) {
    uint32_t ocr = F_CPU / frequency / 2 - 1;
    uint8_t prescalarbits = 0b010;  // ck/1: same for both timers

    // int prescaler = 10 - (4 + n/12);
    // if (prescaler<1 || prescaler>9) prescaler = 0;

    // Calculate the toggle count
    // if (duration > 0)
    // {
    //   toggle_count = 2 * frequency * duration / 1000;
    // }
    // else
    // {
    //   toggle_count = -1;
    // }

    OCR0A = ocr;
    TCCR0B = (TCCR0B & 0b11111000) | prescalarbits;
    // OCR0A = pgm_read_byte(&frequency) - 1;
    // duration = (uint32_t)((a_freq * a_duration)/500);

    // timer0_toggle_count = toggle_count;
    // TIMSK0 |= _BV(OCIE0A);
    // while(duration);
    // bitWrite(TIMSK0, OCIE0A, 1);
}

ISR(TIMER0_COMPA_vect) {
//   // Pone en low el puerto cuando termina.
//   if (timer0_toggle_count != 0) {
//     pin_setup(B7, OUTPUT, HIGH);
//     if (timer0_toggle_count > 0)
//       timer0_toggle_count--;
//   } else {
    TIMSK0 = 0;
    pin_setup(B7, OUTPUT, LOW);
//   }
}
