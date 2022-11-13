#include <avr/pgmspace.h>

// #if defined (__AVR_ATmega32U4__) || defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
  #define PWMT1AMASK DDB7
  // #define PWMT1BMASK DDB6
  #define PWMT1DREG DDRB
  #define PWMT1PORT PORTB
// #elif defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__)
//   #define PWMT1AMASK DDD4
//   #define PWMT1BMASK DDD5
//   #define PWMT1DREG DDRD
//   #define PWMT1PORT PORTD
// #else
//   #define PWMT1AMASK DDB1
//   #define PWMT1BMASK DDB2
//   #define PWMT1DREG DDRB
//   #define PWMT1PORT PORTB
// #endif

#define NOTONEAC 0
#define PLAY_FOREVER 0

unsigned long millis(void);
unsigned long micros(void);
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )

extern void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background);
extern void tone_play_note(unsigned long frequency, uint8_t volume);
extern void no_tone();
