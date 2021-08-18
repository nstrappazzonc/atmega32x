#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#include "serial.h"

void serial_init(unsigned int b){
	//Normal mode UBRR formula
	unsigned int ubrr = F_CPU/16/b-1;

	//shift MSB and store in UBRR0H
	UBRR0H = (unsigned char) (ubrr >> 8);

	//store LSB in UBRR0L
	UBRR0L = (unsigned char) ubrr;

	//Enable transmitter/receiver
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	//8-Bit Characters, 0 Stop bits, No parity
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

	// Enable receiver and transmitter.
	// UCSR0B = (_BV(RXEN0))|(_BV(TXEN0));
	// Set baud rate.
	// UBRR0H = (((F_CPU/16/b) - 1) >> 8);
	// UBRR0L = ((F_CPU/16/b) - 1);
}

void serial_char(char c){
	//Wait for empty transmit buffer
	while (( UCSR0A & (_BV(UDRE0)))  == 0){};
	//Start transmission by writing to UDR0
	UDR0 = c;
}

void serial_string(char *s){
	while(*s){
		serial_char(*s);
		s++;
	}
}

// int getNumOfDigits(int num) {
// 	int s;
// 	while(num != 0) {
// 		num /= 10;
// 		++s;
// 	}
// 	return s;
// }

// unsigned char decToChar(int num) {
// 	unsigned char *str;
// 	int size;

// 	size = getNumOfDigits(num);
// 	str = (char *) malloc(size+1);
// 	sprintf(str, "%d", num);

// 	return *str;
// }
