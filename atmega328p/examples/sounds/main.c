#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define SAMPLE_RATE 8000

/*
  The audio data needs to be unsigned, 8-bit, 8000 Hz, and small enough
  to fit in flash. 10000-13000 samples is about the limit.

  sounddata.h should look like this:
      const int sounddata_length=10000;
      const unsigned char sounddata_data[] PROGMEM = { ..... };

  You can use wav2c from GBA CSS:
      https://thieumsweb.free.fr/english/gbacss.html
  Then add "PROGMEM" in the right place. I hacked it up to dump the samples
  as unsigned rather than signed, but it shouldn't matter.

  https://musicthing.blogspot.com/2005/05/tiny-music-makers-pt-4-mac-startup.html
  mplayer -ao pcm macstartup.mp3
  sox audiodump.wav -v 1.32 -c 1 -r 8000 -u -1 macstartup-8000.wav
  sox macstartup-8000.wav macstartup-cut.wav trim 0 10000s
  wav2c macstartup-cut.wav sounddata.h sounddata

  (starfox) nb. under sox 12.18 (distributed in CentOS 5), i needed to run
  the following command to convert my wav file to the appropriate format:
  sox audiodump.wav -c 1 -r 8000 -u -b macstartup-8000.wav
*/

#include "wave.h"

int speakerPin = 11; // Can be either 3 or 11, two PWM outputs connected to Timer 2
volatile uint16_t sample;
byte lastSample;


void stopPlayback()
{
  // Disable playback per-sample interrupt.
  TIMSK1 &= ~_BV(OCIE1A);

  // Disable the per-sample timer completely.
  TCCR1B &= ~_BV(CS10);

  // Disable the PWM timer.
  TCCR2B &= ~_BV(CS10);

  digitalWrite(speakerPin, LOW);
}

// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
  if (sample >= sounddata_length) {
    if (sample == sounddata_length + lastSample) {
      stopPlayback();
    }
    else {
      if (speakerPin == 11) {
        // Ramp down to zero to reduce the click at the end of playback.
        OCR2A = sounddata_length + lastSample - sample;
      } else {
        OCR2B = sounddata_length + lastSample - sample;
      }
    }
  }
  else {
    if (speakerPin == 11) {
      OCR2A = pgm_read_byte(&sounddata_data[sample]);
    } else {
      OCR2B = pgm_read_byte(&sounddata_data[sample]);
    }
  }

  ++sample;
}

void startPlayback()
{
  pinMode(speakerPin, OUTPUT);

  // Set up Timer 2 to do pulse width modulation on the speaker
  // pin.

  // Use internal clock (datasheet p.160)
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));

  // Set fast PWM mode  (p.157)
  TCCR2A |= _BV(WGM21) | _BV(WGM20);
  TCCR2B &= ~_BV(WGM22);

  if (speakerPin == 11) {
    // Do non-inverting PWM on pin OC2A (p.155)
    // On the Arduino this is pin 11.
    TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
    TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
    // No prescaler (p.158)
    TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set initial pulse width to the first sample.
    OCR2A = pgm_read_byte(&sounddata_data[0]);
  } else {
    // Do non-inverting PWM on pin OC2B (p.155)
    // On the Arduino this is pin 3.
    TCCR2A = (TCCR2A | _BV(COM2B1)) & ~_BV(COM2B0);
    TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
    // No prescaler (p.158)
    TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set initial pulse width to the first sample.
    OCR2B = pgm_read_byte(&sounddata_data[0]);
  }





  // Set up Timer 1 to send a sample every interrupt.

  cli();

  // Set CTC mode (Clear Timer on Compare Match) (p.133)
  // Have to set OCR1A *after*, otherwise it gets reset to 0!
  TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
  TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

  // No prescaler (p.134)
  TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

  // Set the compare register (OCR1A).
  // OCR1A is a 16-bit register, so we have to do this with
  // interrupts disabled to be safe.
  OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 8000 = 2000

  // Enable interrupt when TCNT1 == OCR1A (p.136)
  TIMSK1 |= _BV(OCIE1A);

  lastSample = pgm_read_byte(&sounddata_data[sounddata_length - 1]);
  sample = 0;
  sei();
}


void setup() {
  startPlayback();
}

void loop()
{
  for (int i = 0; i < 3; i++) {
    startPlayback();
    //   startPlayback();
    delay(300);
  }
  delay(1000);
}

//#include "wave.h"
//
//void setup() {
//  //DDRD |= _BV(PD3);
//  DDRD  |= (1 << PD3);
//  PORTD ^= (1 << PD3);
//  // pinMode(3, OUTPUT);
// OCR1A = F_CPU / SAMPLE_RATE;
//
//  TCCR2A = 1<<COM2B0 |  2<<WGM20;
//}
//
//void loop() {
//    for(int i=0;i<laser_length;i++){
//      OCR2A = pgm_read_byte(&laser_data[i]);
//      delayMicroseconds(600);
//    }
//    OCR2A = 0;
//    delay(3000);
//}
