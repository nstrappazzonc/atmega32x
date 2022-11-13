#include <avr/io.h> /* Include AVR std. library file */
#include <stdio.h> /* Include std. library file */
#include <util/delay.h> /* Include Delay header file */

#define BUZZER1_PORT    PORTB
#define BUZZER1     7
static void buzz_sound(uint16_t buzz_length_ms, uint16_t buzz_delay);
#define cbi(port_name, pin_number) ((port_name) &= (uint8_t)~(1 << pin_number))
#define sbi(port_name, pin_number) (port_name |= 1<<pin_number)

int main(void) {
    DDRB |= (1<<PB7); 
    // TCNT1 = 0; /* Set timer1 count zero */
    // ICR1 = 2499; /* Set TOP count for timer1 in ICR1 register */
    // TIMSK1 |= _BV(OCIE1A);
    /* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
    TCCR0A |= ( 1 << WGM00 | 1 << COM0A1 );
    TCCR0B |= ( 1 << CS01 );
    // TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11)|(1<<COM1B1);

    // TCCR0B = (1<<CS01); 
    // ACSR = 0;
    /* Set Prescaler to 1024. CS22=1, CS21=1,CS20=1 */
    // TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20); 
    // TIMSK2 = (1<<TOIE2); /* Enable Timer 2 Interrupt */

    while(1) {
        // OCR0A = 10;
        // _delay_ms(2000);
        // OCR0A = 1;
        buzz_sound(128, 500);
        buzz_sound(131, 500);
        buzz_sound(134, 500);
        buzz_sound(137, 500);
        buzz_sound(140, 500);
        buzz_sound(143, 500);
        buzz_sound(146, 500);
        buzz_sound(149, 500);
        buzz_sound(152, 500);
        buzz_sound(155, 500);
        buzz_sound(158, 500);
        buzz_sound(162, 500);
        buzz_sound(165, 500);
        buzz_sound(167, 500);
        buzz_sound(170, 500);
        buzz_sound(173, 500);
        buzz_sound(176, 500);
        buzz_sound(179, 500);
        buzz_sound(182, 500);
        buzz_sound(185, 500);
        buzz_sound(188, 500);
        buzz_sound(190, 500);
        buzz_sound(193, 500);
        buzz_sound(196, 500);
        buzz_sound(198, 500);
        buzz_sound(201, 500);
        buzz_sound(203, 500);
        buzz_sound(206, 500);
        buzz_sound(208, 500);
        buzz_sound(211, 500);
        buzz_sound(213, 500);
        buzz_sound(215, 500);
        buzz_sound(218, 500);
        buzz_sound(220, 500);
        buzz_sound(222, 500);
        buzz_sound(224, 500);
        buzz_sound(226, 500);
        buzz_sound(228, 500);
        buzz_sound(230, 500);
        buzz_sound(232, 500);
        buzz_sound(234, 500);
        buzz_sound(235, 500);
        buzz_sound(237, 500);
        buzz_sound(238, 500);
        buzz_sound(240, 500);
        buzz_sound(241, 500);
        buzz_sound(243, 500);
        buzz_sound(244, 500);


        _delay_ms(3000);
    }
}

static void buzz_sound(uint16_t buzz_length_ms, uint16_t buzz_delay_us) {
    uint32_t buzz_length_us;

    buzz_length_us = buzz_length_ms * (uint32_t)1000;
    while (buzz_length_us > buzz_delay_us*2) {
        buzz_length_us -= buzz_delay_us*2;
        OCR0A = 3;
        _delay_us(buzz_delay_us);
        OCR0A = 0;
        _delay_us(buzz_delay_us);
    }
}
