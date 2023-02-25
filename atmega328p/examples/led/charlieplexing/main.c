#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	uint8_t sleep = 500;

	DDRC  &= ~(1 << PC5); // I
	DDRC  &= ~(1 << PC4); // I
	DDRC  &= ~(1 << PC3); // I
	DDRC  &= ~(1 << PC2); // I

	while(1) {
		// (4,5) Led 1 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC4); // O
		PORTC &= ~(1 << PC5); // L
		PORTC |=  (1 << PC4); // H
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC4); // I

		// (5,4) Led 2 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC4); // O
		PORTC |=  (1 << PC5); // H
		PORTC &= ~(1 << PC4); // L
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC4); // I

		// (3,5) Led 3 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC3); // O
		PORTC &= ~(1 << PC5); // L
		PORTC |=  (1 << PC3); // H
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC3); // I

		// (5,3) Led 4 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC3); // O
		PORTC |=  (1 << PC5); // H
		PORTC &= ~(1 << PC3); // L
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC3); // I

		// (3,4) Led 5 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC3); // O
		PORTC &= ~(1 << PC4); // L
		PORTC |=  (1 << PC3); // H
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC3); // I

		// (4,3) Led 6 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC3); // O
		PORTC |=  (1 << PC4); // H
		PORTC &= ~(1 << PC3); // L
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC3); // I

		// (2,4) Led 7 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC2); // O
		PORTC &= ~(1 << PC4); // L
		PORTC |=  (1 << PC2); // H
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC2); // I

		// (4,2) Led 8 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC2); // O
		PORTC |=  (1 << PC4); // H
		PORTC &= ~(1 << PC2); // L
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC2); // I

		// (2,5) Led 9 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC2); // O
		PORTC &= ~(1 << PC5); // L
		PORTC |=  (1 << PC2); // H
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC2); // I

		// (5,2) Led 10 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC2); // O
		PORTC |=  (1 << PC5); // H
		PORTC &= ~(1 << PC2); // L
		_delay_ms(sleep);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC2); // I

		// All leds off:
		PORTC &= ~(1 << PC5); // L
		PORTC &= ~(1 << PC4); // L
		PORTC &= ~(1 << PC3); // L
		PORTC &= ~(1 << PC2); // L
		_delay_ms(1000);
	}

	return 0;
}
