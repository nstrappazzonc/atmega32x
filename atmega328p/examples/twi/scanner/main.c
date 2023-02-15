#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <stdio.h>

#define SCL_CLOCK 100000UL
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

void TWIInit(void) {
    // Set SCL to 100kHz, see SCL_CLOCK.
    TWSR = (0<<TWPS1)|(0<<TWPS0);
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / (2*1);;
}

void TWIStart(void) {
    // Enable TWI, generate START.
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    // Wait until TWI finish its current job.
    while ((TWCR & (1<<TWINT)) == 0);
    // Check for the acknowledgement.
    while ((TWSR & 0xF8) != 0x08);
}

void TWIStop(void) {
    // Disable TWI, generate STOP.
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    while ((TWCR & (1<<TWSTO)) == 0);
}

void TWIWrite(uint8_t address) {
    TWDR = address;
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t TWIGetStatus(void) {
    // Read TWI status register and mask with 0xF8.
    return (TWSR & 0xF8);
}

uint8_t TWIPing(uint8_t address){
    uint8_t status;
    TWIStart();
    status = TWIGetStatus();
    if((status != TWSR) && (status != TW_REP_START))
        return 0;
    TWIWrite(address);
    status = TWIGetStatus();
    if((status != TW_MT_SLA_ACK) && (status != TW_MR_SLA_ACK))
        return 0;
    return 1;
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

    TWIInit();

    while (1) {
        for(uint8_t address = 1; address < 127; address++ ) {
            if( (TWIPing((address << 1) | 0))==1 ){
                printf("Scanner for TWI (i2c): device address: 0x%X.\r\n", address);
            }

            TWIStop();

            _delay_ms(10);
        }
        _delay_ms(1000);
    }

    return 0;
}

