#include <avr/interrupt.h>
#include <util/atomic.h>
#include "wait.h"
#include "tone.h"

// Used to track end note with timer when playing note in the background.
unsigned long _tAC_time;
// Duty for linear volume control.
uint8_t _tAC_volume[] = { 200, 100, 67, 50, 40, 33, 29, 22, 11, 2 };

void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background) {
  // If frequency or volume are 0, turn off sound and return.
  if (frequency == NOTONEAC || volume == 0) { no_tone(); return; }
  // Make sure volume is in range (1 to 10).
  if (volume > 10) volume = 10;

  // Routine that plays the note using timers.
  tone_play_note(frequency, volume);

  // If length is zero, play note forever.
  if (length == PLAY_FOREVER) return;

  if (background) {                   // Background tone playing, returns control to your sketch.
    _tAC_time = millis() + length;    // Set when the note should end.
    TIMSK1 |= _BV(OCIE1A);            // Activate the timer interrupt.
  } else {
    wait(length);                     // Just a simple delay, doesn't return control till finished.
    no_tone();
  }
}

void tone_play_note(unsigned long frequency, uint8_t volume) {
  PWMT1DREG |= _BV(PWMT1AMASK); // Set timer 1 PWM pins to OUTPUT (because analogWrite does it too).

  uint8_t prescaler = _BV(CS10);                  // Try using prescaler 1 first.
  unsigned long top = F_CPU / frequency / 2 - 1;  // Calculate the top.
  if (top > 65535) {                              // If not in the range for prescaler 1, use prescaler 256 (122 Hz and lower @ 16 MHz).
    prescaler = _BV(CS12);                        // Set the 256 prescaler bit.
    top = top / 256 - 1;                          // Calculate the top using prescaler 256.
  }

  ICR1   = top;                                     // Set the top.
  if (TCNT1 > top) TCNT1 = top;                     // Counter over the top, put within range.
  TCCR1B = _BV(WGM13)  | prescaler;                 // Set PWM, phase and frequency corrected (top=ICR1) and prescaler.
  OCR1A  = OCR1B = top / _tAC_volume[volume - 1];   // Calculate & set the duty cycle (volume).
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0); // Inverted/non-inverted mode (AC).
}

void no_tone() {
  TIMSK1 &= ~_BV(OCIE1A);        // Remove the timer interrupt.
  TCCR1B  = _BV(CS11);           // Default clock prescaler of 8.
  TCCR1A  = _BV(WGM10);          // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
  PWMT1PORT &= ~_BV(PWMT1AMASK); // Set timer 1 PWM pins to LOW.
  // PWMT1PORT &= ~_BV(PWMT1BMASK); // Other timer 1 PWM pin also to LOW.
}

ISR(TIMER1_COMPA_vect) {                 // Timer interrupt vector.
  if (millis() >= _tAC_time) no_tone(); // Check to see if it's time for the note to end.
}

volatile unsigned long timer0_millis = 0;
volatile unsigned long timer0_overflow_count = 0;


unsigned long millis() {
  unsigned long m;
  uint8_t oldSREG = SREG;

  // disable interrupts while we read timer0_millis or we might get an
  // inconsistent value (e.g. in the middle of a write to timer0_millis)
  cli();
  m = timer0_millis;
  SREG = oldSREG;

  return m;
}

unsigned long micros() {
  unsigned long m;
  uint8_t oldSREG = SREG, t;
  
  cli();
  m = timer0_overflow_count;
  t = TCNT1L;
  SREG = oldSREG;
  
  return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}
