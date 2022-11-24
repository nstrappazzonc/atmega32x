#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

int main(void) {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE);
    UCSR0B |= (1<<RXEN0);   // Turn on receiver.
    UCSR0B |= (1<<TXEN0);   // Turn on transmitter.
    UCSR0C |= (0<<UMSEL00); // Set asynchronous mode.
    UCSR0C |= (0<<UPM00);   // Disable parity mode.
    UCSR0C |= (0<<USBS0);   // Set 8 bits frame data.
    UCSR0C |= (3<<UCSZ00);  // Set 1 stop bit.

    int i = 0;
    unsigned char data[] = "Hello from ATmega328p with CH340C";

    while(1){
        i = 0;
        while(data[i] != 0){
            while (!(UCSR0A & (1<<UDRE0)));
            UDR0 = data[i];
            i++;
        }

        while (!(UCSR0A & (1<<UDRE0)));
        UDR0 = '\n';
        while (!(UCSR0A & (1<<UDRE0)));
        UDR0 = '\r';

        _delay_ms(1000);
    }

    return 0;
}
