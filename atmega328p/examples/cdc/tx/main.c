#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

static inline void serial_init();
static inline void serial_print(char*);
static inline void serial_send(unsigned char);

int main(void) {
    serial_init();

    while (1) {
        serial_print("Hello from ATmega328p with CH340C");
        serial_send(0x0D);
        serial_send(0x0A);

        _delay_ms(1000);
    }

    return 0;
}

static inline void serial_init() {
    UBRR0H  = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L  = (unsigned char)(UBRR_VALUE);
    UCSR0B |= (1<<RXEN0);   // Turn on receiver.
    UCSR0B |= (1<<TXEN0);   // Turn on transmitter.
    UCSR0B |= (1<<RXCIE0);  // RX complete interrupt.
    UCSR0C |= (0<<UMSEL00); // Set asynchronous mode.
    UCSR0C |= (0<<UPM00);   // Disable parity mode.
    UCSR0C |= (0<<USBS0);   // Set 8 bits frame data.
    UCSR0C |= (3<<UCSZ00);  // Set 1 stop bit.
}

static inline void serial_send(unsigned char data) {
    // Wait for empty transmit buffer.
    while(!(UCSR0A & (1<<UDRE0)));

    // Put data into buffer, sends the data.
    UDR0 = data;
}

static inline void serial_print(char* s) {
    // Sends the characters from the string one at a time.
    while(*s != 0x00) {
        serial_send(*s++);
    }
}
