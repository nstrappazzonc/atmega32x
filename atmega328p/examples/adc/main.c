#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

static int usart_putchar(char, FILE*);

FILE usart_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    // Cofigure CDC:
    UBRR0H  = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L  = (unsigned char)(UBRR_VALUE);
    UCSR0B |= (1<<RXEN0);   // Turn on receiver.
    UCSR0B |= (1<<TXEN0);   // Turn on transmitter.
    UCSR0C |= (0<<UMSEL00); // Set asynchronous mode.
    UCSR0C |= (0<<UPM00);   // Disable parity mode.
    UCSR0C |= (0<<USBS0);   // Set 8 bits frame data.
    UCSR0C |= (3<<UCSZ00);  // Set 1 stop bit.

    stdout = &usart_stdout;

    // Configure ADC:
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

    uint16_t result=0;

    while (1) {
        // Select ADC channel with safety mask.
        ADMUX = (ADMUX & 0xF0) | (0 & 0x0F);
        // Start conversion.
        ADCSRA |= (1<<ADSC);
        // Wait until ADC conversion is complete.
        while( ADCSRA & (1<<ADSC) );
        result = ADC;
        // Print the current value.
	    printf("Value: %u\r\n", result);
        // Wait 1 second.
        _delay_ms(1000);
    }

    return 0;
}

static int usart_putchar(char c, FILE *stream)
{
    // Wait until data register is empty
    while((UCSR0A & (1 << UDRE0)) == 0) {;}
    // Load transmit register with new data
    UDR0 = c;
    _delay_ms(1);
    return 0;
}
