#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

static int usart_putchar(char, FILE*);

FILE usart_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

static int usart_putchar(char c, FILE *stream)
{
    // Wait until data register is empty
    while((UCSR0A & (1 << UDRE0)) == 0) {;}
    // Load transmit register with new data
    UDR0 = c;
    _delay_ms(1);
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

    // Set PINs for Rotary Encoder:
    DDRD &= ~(1 << 2); // PD2 Push Switch
    DDRD &= ~(1 << 3); // PD3 CLK
    DDRD &= ~(1 << 4); // PD4 DT

    stdout = &usart_stdout;

    int count = 0;

    while (1) {
        if(bit_is_clear(PIND, 3) || bit_is_clear(PIND, 4)){
            if (bit_is_clear(PIND,3)) {
                count++;
            }
            if (bit_is_clear(PIND,4)) {
                count--;
            }
        }
        printf("Rotary Encoder - Push Switch:%u CLK:%u DT:%u COUNT:%d\n\r", bit_is_clear(PIND, 2), bit_is_clear(PIND, 3), bit_is_clear(PIND, 4), count);
    }

    return 0;
}
