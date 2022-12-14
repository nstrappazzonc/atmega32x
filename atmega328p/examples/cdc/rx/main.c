#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

static inline void serial_init();
static inline void serial_send(uint8_t);
static inline void serial_print(char* string);
static inline unsigned char serial_read(void);

int main(void) {
    serial_init();
    serial_print("Write anything:\n\r");

    while(1){
        serial_send(serial_read());
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

static inline void serial_send(uint8_t data){
    // Wait for empty transmit buffer.
    while(!(UCSR0A & (1<<UDRE0)));

    // Put data into buffer, sends the data.
    UDR0 = data;
}

static inline void serial_print(char* strptr){
    // Sends the characters from the string one at a time.
    while(*strptr != 0x00) {
        serial_send(*strptr++);
    }
}

static inline unsigned char serial_read(void) {
    // Wait for data to be received.
    while (!(UCSR0A & (1<<RXC0)));

    // Get and return received data from buffer.
    return UDR0;
}
