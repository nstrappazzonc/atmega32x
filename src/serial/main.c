#include <avr/io.h>
#include <util/delay.h>

#define BUAD 19200
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
}

void loop() {
	char *strA = "Hello tty terminal!"; 

	usart_putstr(strA);
	usart_putchar('\n');
	usart_putchar('\r');

	_delay_ms(1000);
}

int main(void) {
	setup();

	for (;;) {
		loop();
	}

	return 0;
}
