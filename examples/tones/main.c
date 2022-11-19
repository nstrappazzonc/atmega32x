#include <avr/io.h>
#include <avr/pgmspace.h>
#include <wait.h>

const uint8_t scale[] PROGMEM = {239,226,213,201,190,179,169,160,151,142,134,127};
// const uint8_t scale[] PROGMEM = {
//   239, // Note C
//   225, // Note CS
//   213, // Note_D
//   201, // Note_DS
//   190, // Note_E
//   179, // Note_F
//   169, // Note_FS
//   159, // Note_G
//   150, // Note_GS
//   142, // Note_A
//   134, // Note_AS
//   127, // Note_B
// };

void note (int n);

int main(void) {
  while (1) {
    for (int n = 0; n < 12; n++) {
      note(n);
      // if (n!=4 && n!=11) n++;
      wait(100);
    }
    note(0);
    wait(1000);
  }

  return 0;
}

void note (int n) {
  uint32_t ocr = 0;
  // octave values between 1 and 6.

  // int prescaler = 10 - (octave + n/12);
  // if (prescaler<1 || prescaler>9) prescaler = 0;
  
  #if defined(__AVR_ATmega32U2__)

  #elif defined(__AVR_ATmega32U4__)
  DDRB   = DDRB | 1<<DDB6;        // PB6 as output
  TCCR4A = 0<<COM4A0 | 1<<COM4B0; // Toggle OC4B on match
  ocr = F_CPU / n / 2 - 1;
  // OCR4A  = pgm_read_byte(&scale[n % 12]) - 1;
  // OCR4C  = pgm_read_byte(&scale[n]) - 1;
  // OCR4C  = pgm_read_byte(&scale[n]);
  OCR4A  = ocr;
  // TCCR4B = 1<<CS40;
  TCCR4B = (TCCR4B & 0b11111000) | 0b001;
  // TCCR4B = b00001001;
  #endif
}
