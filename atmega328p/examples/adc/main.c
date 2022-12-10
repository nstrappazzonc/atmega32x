#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

static inline void serial_init();
static inline void serial_print(char*);
static inline void serial_send(unsigned char);
static inline void serial_send_number(int);
static inline void serial_send_number_16(uint16_t);
static inline void serial_send_newline();
static inline void adc_init();
char nibbleToHexCharacter(uint8_t);

int main(void) {
    serial_init();
    adc_init();

    uint16_t result=0;

    while (1) {
        serial_print("Value: ");

        // Select ADC channel with safety mask.
        ADMUX = (ADMUX & 0xF0) | (0 & 0x0F);
        // Start conversion.
        ADCSRA |= (1<<ADSC);
        // Wait until ADC conversion is complete.
        // while( ADCSRA & (1<<ADSC) );
        // loop_until_bit_is_clear(ADCSRA, ADSC);
        while( !(ADCSRA & (1<<ADIF)) );
        result = ADC;
        // Clear the ADIF flag.
        ADCSRA |= (1<<ADIF);

        uint16_t  temp = 0;
        temp = result;
        serial_send(nibbleToHexCharacter(temp % 16));
        temp = temp/16;
        serial_send('0' + (temp % 16));
        temp = temp/16;
        serial_send('0' + (temp % 16));
        
        serial_send_newline();

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

static inline void serial_send_number(int n) {
    // Print values from 0 to 999 in int,
    // Or in binary 0b11111111 equal to 255.
    // No use uint8_t the limit is 231.
    serial_send('0' + (n / 100));       // Hundreds
    serial_send('0' + ((n / 10) % 10)); // Tens
    serial_send('0' + (n % 10));        // Ones
}

static inline void serial_send_number_16(uint16_t n) {
    serial_send('0' + ((n / 1000) % 10)); // Thousands
    serial_send('0' + ((n / 100) % 10));  // Hundreds
    serial_send('0' + ((n / 10) % 10));   // Tens
    serial_send('0' + (n % 10));          // Ones
}

static inline void serial_send_newline(void) {
    // New line "\r\n" - CRLF (0x0D 0x0A)
    serial_send(0x0D); // CR is \r.
    serial_send(0x0A); // LF is \n.
}

static inline void adc_init() {
    // Select reference voltage on AVCC.
    ADMUX  |= (1<<REFS0);
    // Select internal reference voltage 1.1v.
    // ADMUX  |= (1<<REFS0) | (1<<REFS1);
    // Left-adjust result, return only 8 bits
    // ADMUX  |= (1 << ADLAR);
    // Set prescaller to 128.
    ADCSRA |= (1<<ADPS0);
    ADCSRA |= (1<<ADPS1);
    ADCSRA |= (1<<ADPS2);
    // Enable ADC.
    ADCSRA |= (1<<ADEN);
    // Enable interrupt.
    // ADCSRA |= (1<<ADIF);
    // Enable global interrupt.
    // sei();
}

char nibbleToHexCharacter(uint8_t nibble) {
  if (nibble < 10) {
    return ('0' + nibble);
  }
  else {
    return ('A' + nibble - 10);
  }
}