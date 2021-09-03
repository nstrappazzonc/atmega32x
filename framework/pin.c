#include "pin.h"

const uint16_t PROGMEM dir[] = {
    (uint16_t) &DDRD, /*  0 */
    (uint16_t) &DDRD, /*  1 */
    (uint16_t) &DDRD, /*  2 */
    (uint16_t) &DDRD, /*  3 */
    (uint16_t) &DDRD, /*  4 */
    (uint16_t) &DDRD, /*  5 */
    (uint16_t) &DDRD, /*  6 */
    (uint16_t) &DDRD, /*  7 */
    (uint16_t) &DDRB, /*  8 */
    (uint16_t) &DDRB, /*  9 */
    (uint16_t) &DDRB, /* 10 */
    (uint16_t) &DDRB, /* 11 */
    (uint16_t) &DDRB, /* 12 */
    (uint16_t) &DDRB, /* 13 */
    (uint16_t) &DDRB, /* 14 */
    (uint16_t) &DDRB, /* 15 */
    (uint16_t) &DDRC, /* 16 */
    (uint16_t) &DDRC, /* 17 */
    (uint16_t) &DDRC, /* 18 */
    (uint16_t) &DDRC, /* 19 */
    (uint16_t) &DDRC, /* 20 */
    (uint16_t) &DDRC, /* 21 */
};

const uint16_t PROGMEM ports[] = {
    (uint16_t) &PORTD, /*  0 */
    (uint16_t) &PORTD, /*  1 */
    (uint16_t) &PORTD, /*  2 */
    (uint16_t) &PORTD, /*  3 */
    (uint16_t) &PORTD, /*  4 */
    (uint16_t) &PORTD, /*  5 */
    (uint16_t) &PORTD, /*  6 */
    (uint16_t) &PORTD, /*  7 */
    (uint16_t) &PORTB, /*  8 */
    (uint16_t) &PORTB, /*  9 */
    (uint16_t) &PORTB, /* 10 */
    (uint16_t) &PORTB, /* 11 */
    (uint16_t) &PORTB, /* 12 */
    (uint16_t) &PORTB, /* 13 */
    (uint16_t) &PORTB, /* 14 */
    (uint16_t) &PORTB, /* 15 */
    (uint16_t) &PORTC, /* 16 */
    (uint16_t) &PORTC, /* 17 */
    (uint16_t) &PORTC, /* 18 */
    (uint16_t) &PORTC, /* 19 */
    (uint16_t) &PORTC, /* 20 */
    (uint16_t) &PORTC, /* 21 */
};

const uint16_t PROGMEM pins[] = {
    (uint16_t) &PIND, /*  0 */
    (uint16_t) &PIND, /*  1 */
    (uint16_t) &PIND, /*  2 */
    (uint16_t) &PIND, /*  3 */
    (uint16_t) &PIND, /*  4 */
    (uint16_t) &PIND, /*  5 */
    (uint16_t) &PIND, /*  6 */
    (uint16_t) &PIND, /*  7 */
    (uint16_t) &PINB, /*  8 */
    (uint16_t) &PINB, /*  9 */
    (uint16_t) &PINB, /* 10 */
    (uint16_t) &PINB, /* 11 */
    (uint16_t) &PINB, /* 12 */
    (uint16_t) &PINB, /* 13 */
    (uint16_t) &PINB, /* 14 */
    (uint16_t) &PINB, /* 15 */
    (uint16_t) &PINC, /* 16 */
    (uint16_t) &PINC, /* 17 */
    (uint16_t) &PINC, /* 18 */
    (uint16_t) &PINC, /* 19 */
    (uint16_t) &PINC, /* 20 */
    (uint16_t) &PINC, /* 21 */
};

const uint8_t PROGMEM masks[] = {
    _BV(0),/*  0 PD0 Analog PWM */
    _BV(1),/*  1 PD1 Analog */
    _BV(2),/*  2 PD2 Analog */
    _BV(3),/*  3 PD3 Analog */
    _BV(4),/*  4 PD4 Analog */
    _BV(5),/*  5 PD5 Analog */
    _BV(6),/*  6 PD6 Analog */
    _BV(7),/*  7 PD7 Analog */
    _BV(0),/*  8 PB0 Diginal */
    _BV(1),/*  9 PB1 Diginal */
    _BV(2),/* 10 PB2 Diginal */
    _BV(3),/* 11 PB3 Diginal */
    _BV(4),/* 12 PB4 Diginal */
    _BV(5),/* 13 PB5 Diginal */
    _BV(6),/* 14 PB6 Diginal */
    _BV(7),/* 15 PB7 Diginal PWM */
    _BV(1),/* 16 PC1 Diginal RESET */
    _BV(2),/* 17 PC2 Diginal */
    _BV(4),/* 18 PC4 Diginal */
    _BV(5),/* 19 PC5 Diginal PWM */
    _BV(6),/* 20 PC6 Diginal PWM */
    _BV(7),/* 21 PC7 Diginal */
};

void pin_setup(uint8_t pin, uint8_t mode, uint8_t state) {
    volatile uint8_t *reg;

    reg = dir_get_id(pin);

    if (mode == INPUT) {
        *reg &= ~mask_get_id(pin);
    } else {
        *reg |= mask_get_id(pin);
    }

    pin_set_state(pin, state);
}

void pin_set_state(uint8_t pin, uint8_t state) {
    if (state == HIGH) {
        *port_get_id(pin) |= mask_get_id(pin);
    } else if (state == LOW) {
        *port_get_id(pin) &= ~mask_get_id(pin);
    } else {
        // Set PWM
        switch(pin) {
            case 0:
                TCCR0A |= ( 1 << WGM00 | 1 << COM0B1 );
                TCCR0B |= ( 1 << CS00 );
                OCR0B = state;
				break;
            case 15:
                TCCR0A |= ( 1 << WGM00 | 1 << COM0A1 );
                TCCR0B |= ( 1 << CS01 );
                OCR0A = state;
				break;
            case 19:
                TCCR1A |= ( 1 << WGM10 | 1 << COM1B1 );
                TCCR1B |= ( 1 << CS10);
                OCR1B = state;
				break;
            case 20:
                TCCR1A |= ( 1 << WGM10 | 1 << COM1A1 );
                TCCR1B |= ( 1 << CS11);
                OCR1A = state;
				break;
        }
    }
}

uint8_t pin_get_state(uint8_t port, uint8_t pin) {
    return port & mask_get_id(pin);
}

uint8_t pin_get(uint8_t pin) {
    return *pin_get_id(pin) & mask_get_id(pin);
}
