#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

static inline int usart_putchar_printf(char, FILE*);

FILE usart_stdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

static inline int usart_putchar_printf(char c, FILE *stream)
{
    // if (c == 0x0A)
        // uart_putchar(0x0D);
    // loop_until_bit_is_set(UCSR0A, UDRE0);
    // UDR0 = c;
    // uart_putchar(c);
    // if(c == '\n')
        // usart_putchar_printf('\r', stream);
    // Wait until data register is empty
    while((UCSR0A & (1 << UDRE0)) == 0) {;}
    // Load transmit register with new data
    UDR0 = c;
    _delay_ms(10);
    return 0;
}

int main(void)
{
    UBRR0H  = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L  = (unsigned char)(UBRR_VALUE);
    UCSR0B |= (1<<RXEN0);   // Turn on receiver.
    UCSR0B |= (1<<TXEN0);   // Turn on transmitter.
    UCSR0C |= (0<<UMSEL00); // Set asynchronous mode.
    UCSR0C |= (0<<UPM00);   // Disable parity mode.
    UCSR0C |= (0<<USBS0);   // Set 8 bits frame data.
    UCSR0C |= (3<<UCSZ00);  // Set 1 stop bit.

    stdout = &usart_stdout;

    while (1) {
        printf("ABC");
        // printf("\n");
        _delay_ms(1000);
    }

    return 0;
}
