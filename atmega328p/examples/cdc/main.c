#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// #define UBRR_VALUE F_CPU/16/USART_BAUDRATE-1
// #define UBRR_VALUE 103

void USART_Transmit(uint8_t c);
// void UART_puts(char* s);

void USART_Transmit(uint8_t c) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)));
    // while (( UCSR0A & (1 << UDRE0 )) == 0){};
    UDR0 = c;
}

// void UART_puts(char* s) {
    // transmit character until NULL is reached
    // while(*s > 0) USART_Transmit(*s++);
// }

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection
#define DISABLED    (0<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection
#define ONE_BIT (0<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

int main(void) {
    _delay_ms(100);
    // UBRR0 = UBRR_VALUE ; // Set baud rate
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)UBRR_VALUE;
    // UBRRH = UBRR_VALUE >> 8; // Set high byte of baud rate
    // UBRRL = UBRR_VALUE & 0 xff ; // Set low byte of baud rate
    UCSR0B |= (1<<RXEN0 ); // Turn on receiver
    UCSR0B |= (1<<TXEN0 ); // Turn on transmitter
    UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
    // UCSR0C  = (3 << UCSZ00 ); // Set for async . operation , no
    // UCSR0C |= (1<<USBS0);  // 8data
    // UCSR0C |= (3<<UCSZ00); // 2stop bit
    // UCSR0C = 0x06;

    // unsigned char str[18] = "\n\rExplore Embedded";
    // unsigned char strLenght = 18;
    // unsigned char i = 0;

    int i = 0;
    unsigned char data[] = "Hello from ATmega328p with CH340";
    // unsigned char data = "Hola"
    // int i = 0;

    while(1){
        i = 0;
        while(data[i] != 0){
            // USART_Transmit('L');
            while (!( UCSR0A & (1<<UDRE0)));
            UDR0 = data[i];
            i++;
        }
        // USART_Transmit('H');
        // USART_Transmit('O');
        // _delay_ms(1000);
        // i = 0;
        // while(data[i] != 0) {
        //     USART_Transmit(data[i++]);
        // }
        // UART_puts(data);

        while (!( UCSR0A & (1<<UDRE0)));   /* Wait for empty transmit buffer       */
        UDR0 = '\n';
        while (!( UCSR0A & (1<<UDRE0)));   /* Wait for empty transmit buffer       */
        UDR0 = '\r';

        _delay_ms(1000);
        // USART_Transmit(67);
        // _delay_ms(1000);
        // USART_Transmit(68);
        // USART_Transmit( str[i++] );
        // if(i >= strLenght)
        // i = 0;
        // _delay_ms(1000);
    }

    return(0); 
}
