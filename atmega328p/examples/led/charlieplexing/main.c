#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


void TenSegmentDisplay(uint8_t level) {
	if (level >= 1) {
		// (4,5) Led 1 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC4); // O
		PORTC &= ~(1 << PC5); // L
		PORTC |=  (1 << PC4); // H
		_delay_ms(1);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC4); // I
	}
	if (level >= 2) {
		// (5,4) Led 2 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC4); // O
		PORTC |=  (1 << PC5); // H
		PORTC &= ~(1 << PC4); // L
		_delay_ms(1);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC4); // I
	}

	if (level >= 3) {
		// (3,5) Led 3 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC3); // O
		PORTC &= ~(1 << PC5); // L
		PORTC |=  (1 << PC3); // H
		_delay_ms(1);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC3); // I
	}

	if (level >= 4) {
		// (5,3) Led 4 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC3); // O
		PORTC |=  (1 << PC5); // H
		PORTC &= ~(1 << PC3); // L
		_delay_ms(1);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC3); // I
	}

	if (level >= 5) {
		// (3,4) Led 5 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC3); // O
		PORTC &= ~(1 << PC4); // L
		PORTC |=  (1 << PC3); // H
		_delay_ms(1);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC3); // I
	}

	if (level >= 6) {
		// (4,3) Led 6 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC3); // O
		PORTC |=  (1 << PC4); // H
		PORTC &= ~(1 << PC3); // L
		_delay_ms(1);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC3); // I
	}

	if (level >= 7) {
		// (2,4) Led 7 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC2); // O
		PORTC &= ~(1 << PC4); // L
		PORTC |=  (1 << PC2); // H
		_delay_ms(1);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC2); // I
	}

	if (level >= 8) {
		// (4,2) Led 8 on:
		DDRC  |=  (1 << PC4); // O
		DDRC  |=  (1 << PC2); // O
		PORTC |=  (1 << PC4); // H
		PORTC &= ~(1 << PC2); // L
		_delay_ms(1);
		DDRC  &= ~(1 << PC4); // I
		DDRC  &= ~(1 << PC2); // I
	}

	if (level >= 9) {
		// (2,5) Led 9 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC2); // O
		PORTC &= ~(1 << PC5); // L
		PORTC |=  (1 << PC2); // H
		_delay_ms(1);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC2); // I
	}

	if (level >= 10) {
		// (5,2) Led 10 on:
		DDRC  |=  (1 << PC5); // O
		DDRC  |=  (1 << PC2); // O
		PORTC |=  (1 << PC5); // H
		PORTC &= ~(1 << PC2); // L
		_delay_ms(1);
		DDRC  &= ~(1 << PC5); // I
		DDRC  &= ~(1 << PC2); // I
	}
	
}

int main(void) {
	DDRC  &= ~(1 << PC5); // I
	DDRC  &= ~(1 << PC4); // I
	DDRC  &= ~(1 << PC3); // I
	DDRC  &= ~(1 << PC2); // I

	//sei(); // Set global interrupts.

	while(1) {
		for (uint8_t i = 1; i <= 10; i++) {
			for (uint8_t x = 1; x <= 100; x++) {
				TenSegmentDisplay(i);
				_delay_ms(5);
			}
		}
	}

	return 0;
}
