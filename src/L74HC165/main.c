//this example runs with 2 shift registers
// renombrar el proyecto cómo: shiftin

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUAD 57600
#define BUAD_RATE_CALC ((F_CPU/16/BUAD) - 1)

void setup(void);
void loop(void);

void usart_init(uint16_t ubrr){
	// Enable receiver and transmitter.
	UCSR0B = (_BV(RXEN0))|(_BV(TXEN0));
	// Set baud rate.
	UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
}

void usart_putchar(char c){
	while (( UCSR0A & (_BV(UDRE0)))  == 0){};
	UDR0 = c;
}

void usart_putstr(char *s){
	while(*s){
		usart_putchar(*s);
		s++;
	}
}

void setup() {
	usart_init(BUAD_RATE_CALC);

	// l74hc165_init
// Todos van al PDx
// int load = PD2; // PL pin 1
// int clockIn = PD3; // CP pin 2
// int dataIn = PD4; // Q7 pin 7
// int clockEnablePin = PD5; // CE pin 15
	//output
	DDRD |= (1 << PD3);
	DDRD |= (1 << PD2);
	//input
	DDRD &= ~(1 << PD4);
	//low
	PORTD &= ~(1 << PD3);
	PORTD &= ~(1 << PD2);
}

void loop() {
	usart_putstr("IN:");
	usart_putchar('\n');
	usart_putchar('\r');


//  // Write pulse to load pin
//  digitalWrite(load, LOW);
//  delayMicroseconds(5);
//  digitalWrite(load, HIGH);
//  delayMicroseconds(5);
//
//  // Get data from 74HC165
//  digitalWrite(clockIn, HIGH);
//  digitalWrite(clockEnablePin, LOW);
//  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
//  digitalWrite(clockEnablePin, HIGH);
//
//  // Print to serial monitor
//  Serial.print("Pin States:");
////  Serial.println(incoming, BIN);
//  printOut1(incoming);
//
////  sprintf(incoming, "%08d", incoming);
//  Serial.println();
//  delay(50);

	_delay_ms(200);
}

int main(void) {
	setup();

	for (;;) {
		loop();
	}

	return 0;
}

void l74hc165_shiftin(uint8_t *bytearray) {
}
