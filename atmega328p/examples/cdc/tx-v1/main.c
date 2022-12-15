#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

static void USARTInit(void);
static void USARTSend(uint8_t);
static void USARTSendString(char* string);

int main(void) {
    USARTInit();

    while(1){
        USARTSendString("Hello from ATmega328p with CH340C\n\r");
        _delay_ms(1000);
    }

    return 0;
}

static void USARTInit(void) {
    UBRR0H  = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L  = (uint8_t)(UBRR_VALUE);
    UCSR0B |= (1<<RXEN0);   // Turn on receiver.
    UCSR0B |= (1<<TXEN0);   // Turn on transmitter.
    UCSR0C |= (0<<UMSEL00); // Set asynchronous mode.
    UCSR0C |= (0<<UPM00);   // Disable parity mode.
    UCSR0C |= (0<<USBS0);   // Set 8 bits frame data.
    UCSR0C |= (3<<UCSZ00);  // Set 1 stop bit.
}

static void USARTSend(uint8_t data){
    // Wait for empty transmit buffer.
    while(!(UCSR0A & (1<<UDRE0)));

    // Put data into buffer, sends the data.
    UDR0 = data;
}

static void USARTSendString(char* strptr){
    // Sends the characters from the string one at a time.
    while(*strptr != 0x00) {
        USARTSend(*strptr++);
    }
}
