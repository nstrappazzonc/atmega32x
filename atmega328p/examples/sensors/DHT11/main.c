#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define DHT11_PIN 7
#define USART_BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

static int usart_putchar(char, FILE*);

FILE usart_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

static int usart_putchar(char c, FILE *stream) {
    // Wait until data register is empty
    while((UCSR0A & (1 << UDRE0)) == 0) {;}
    // Load transmit register with new data
    UDR0 = c;
    _delay_ms(1);
    return 0;
}

void Request(void) {
    DDRD |= (1<<DHT11_PIN);
    PORTD &= ~(1<<DHT11_PIN); /* set to low pin */
    _delay_ms(20);            /* wait for 20ms */
    PORTD |= (1<<DHT11_PIN);  /* set to high pin */
}

void Response(void) {
    DDRD &= ~(1<<DHT11_PIN);
    while(PIND & (1<<DHT11_PIN));
    while((PIND & (1<<DHT11_PIN))==0);
    while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data(void) {
    uint8_t c=0;
    for (int q=0; q<8; q++) {
        while((PIND & (1<<DHT11_PIN)) == 0); /* check received bit 0 or 1 */
        _delay_us(30);
        if(PIND & (1<<DHT11_PIN))            /* if high pulse is greater than 30ms */
            c = (c<<1)|(0x01);               /* then its logic HIGH */
        else                                 /* otherwise its logic LOW */
            c = (c<<1);
        while(PIND & (1<<DHT11_PIN));
    }
    return c;
}

int main(void) {
    uint8_t I_RH, D_RH, I_Temp, D_Temp, CheckSum;

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
        Request();               /* send start pulse */
        Response();              /* receive response */
        I_RH=Receive_data();     /* store first eight bit in I_RH */
        D_RH=Receive_data();     /* store next eight bit in D_RH */
        I_Temp=Receive_data();   /* store next eight bit in I_Temp */
        D_Temp=Receive_data();   /* store next eight bit in D_Temp */
        CheckSum=Receive_data(); /* store next eight bit in CheckSum */

        if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum) {
            continue;
        }

        printf("DHT11 - H: %d.%d %% T: %d.%d C.\r\n", I_RH, D_RH, I_Temp, D_Temp);

        _delay_ms(1000);
    }

    return 0;
}
