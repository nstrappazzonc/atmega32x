const int scale[] PROGMEM = {
  31,   // NOTE_B0
  33,   // NOTE_C1
  35,   // NOTE_CS1
  37,   // NOTE_D1
  39,   // NOTE_DS1
  41,   // NOTE_E1
  44,   // NOTE_F1
  46,   // NOTE_FS1
  49,   // NOTE_G1
  52,   // NOTE_GS1
  55,   // NOTE_A1
  58,   // NOTE_AS1
  62,   // NOTE_B1
  65,   // NOTE_C2
  69,   // NOTE_CS2
  73,   // NOTE_D2
  78,   // NOTE_DS2
  82,   // NOTE_E2
  87,   // NOTE_F2
  93,   // NOTE_FS2
  98,   // NOTE_G2
  104,  // NOTE_GS2
  110,  // NOTE_A2
  117,  // NOTE_AS2
  123,  // NOTE_B2
  131,  // NOTE_C3
  139,  // NOTE_CS3
  147,  // NOTE_D3
  156,  // NOTE_DS3
  165,  // NOTE_E3
  175,  // NOTE_F3
  185,  // NOTE_FS3
  196,  // NOTE_G3
  208,  // NOTE_GS3
  220,  // NOTE_A3
  233,  // NOTE_AS3
  247,  // NOTE_B3
  262,  // NOTE_C4
  277,  // NOTE_CS4
  294,  // NOTE_D4
  311,  // NOTE_DS4
  330,  // NOTE_E4
  349,  // NOTE_F4
  370,  // NOTE_FS4
  392,  // NOTE_G4
  415,  // NOTE_GS4
  440,  // NOTE_A4
  466,  // NOTE_AS4
  494,  // NOTE_B4
  523,  // NOTE_C5
  554,  // NOTE_CS5
  587,  // NOTE_D5
  622,  // NOTE_DS5
  659,  // NOTE_E5
  698,  // NOTE_F5
  740,  // NOTE_FS5
  784,  // NOTE_G5
  831,  // NOTE_GS5
  880,  // NOTE_A5
  932,  // NOTE_AS5
  988,  // NOTE_B5
  1047, // NOTE_C6
  1109, // NOTE_CS6
  1175, // NOTE_D6
  1245, // NOTE_DS6
  1319, // NOTE_E6
  1397, // NOTE_F6
  1480, // NOTE_FS6
  1568, // NOTE_G6
  1661, // NOTE_GS6
  1760, // NOTE_A6
  1865, // NOTE_AS6
  1976, // NOTE_B6
  2093, // NOTE_C7
  2217, // NOTE_CS7
  2349, // NOTE_D7
  2489, // NOTE_DS7
  2637, // NOTE_E7
  2794, // NOTE_F7
  2960, // NOTE_FS7
  3136, // NOTE_G7
  3322, // NOTE_GS7
  3520, // NOTE_A7
  3729, // NOTE_AS7
  3951, // NOTE_B7
  4186, // NOTE_C8
  4435, // NOTE_CS8
  4699, // NOTE_D8
  4978, // NOTE_DS8
};

// static const unsigned int notes[] PROGMEM = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int beats[] = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int tones[] = {1915,1700,1519,1432,1275,1136,1014,956,834,765,593,468,346,224,655,715};


void note2 (int frequency) {
  uint32_t ocr = 0;
  ocr = F_CPU / frequency / 2 - 1;

  DDRB   = DDRB | 1<<DDB6;        // PB6 as output
  TCCR4A = 0<<COM4A0 | 1<<COM4B0; // Toggle OC4B on match
  OCR4C  = ocr;
  TCCR4B = 0<<CS40;
}

// void note (int n, int octave) {
//   int prescaler = 8 + Clock - (octave + n/12);
//   if (prescaler<1 || prescaler>15 || octave==0) prescaler = 0;

//   DDRD = DDRD | 1<<DDD0;
//   TCCR0A = 0 << COM0A0 | 1 << COM0B0;
//   // int prescaler = 10 - (octave + n/12);
//   // if (prescaler<1 || prescaler>9) prescaler = 0;
//   OCR0B = pgm_read_byte(&scale[n % 12]) - 1;
//   TCCR0B = prescaler << CS00;
// }

// PB6 PCINT6/OC1B/OC4B/ADC
// OC1B/PCINT6/OC.4B/ADC13 (Output Compare and PWM Output B for Timer/Counter1 or
// Pin Change Interrupt 6 or Timer 4 Output Compare B / PWM output or Analog to Digital
// Converter channel 13)
// Control signals are found in the Timer/Counter Control Registers TCCR4A, TCCR4B, TCCR4C, TCCR4D, and TCCR4E.
// TCCR4A = 15.12.1 TCCR4A – Timer/Counter4 Control Register A, COM4A0 COM4B0

// PD0 Timer/Counter0 OC0B