#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include "cdc.h"

#define LED_CONFIG  (DDRD |= (1<<6))
#define LED_ON      (PORTD |= (1<<6))
#define LED_OFF     (PORTD &= ~(1<<6))

void send_str(const char *s);
uint8_t recv_str(char *buf, uint8_t size);
void parse_and_execute_command(const char *buf, uint8_t num);

// Basic command interpreter for controlling port pins
int main(void) {
    char buf[32];
    uint8_t n;

    LED_CONFIG;
    LED_ON;

    // initialize the USB, and then wait for the host
    // to set configuration.  If the Teensy is powered
    // without a PC connected to the USB port, this 
    // will wait forever.
    cdc_init();
    while (!cdc_configured()) /* wait */ ;
    _delay_ms(1000);

    while (1) {
        // wait for the user to run their terminal emulator program
        // which sets DTR to indicate it is ready to receive.
        while (!(cdc_get_control() & CDC_DTR)) /* wait */ ;

        // discard anything that was received prior.  Sometimes the
        // operating system or other software will send a modem
        // "AT command", which can still be buffered.
        cdc_flush_input();

        // print a nice welcome message
        send_str(PSTR("\r\nAtmel atmega32u2 USB serial example, "
            "Simple Pin Control Shell\r\n\r\n"
            "Example Commands\r\n"
            "  B0?   Read Port B, pin 0\r\n"
            "  C2=0  Write Port C, pin 1 LOW\r\n"
            "  D6=1  Write Port D, pin 6 HIGH  (D6 is LED pin)\r\n\r\n"));

        // and then listen for commands and process them
        while (1) {
            send_str(PSTR("> "));
            n = recv_str(buf, sizeof(buf));
            if (n == 255) break;
            send_str(PSTR("\r\n"));
            parse_and_execute_command(buf, n);
        }
    }
}

// Send a string to the USB serial port.  The string must be in
// flash memory, using PSTR
//
void send_str(const char *s)
{
    char c;
    while (1) {
        c = pgm_read_byte(s++);
        if (!c) break;
        cdc_putchar(c);
    }
}

// Receive a string from the USB serial port.  The string is stored
// in the buffer and this function will not exceed the buffer size.
// A carriage return or newline completes the string, and is not
// stored into the buffer.
// The return value is the number of characters received, or 255 if
// the virtual serial connection was closed while waiting.
//
uint8_t recv_str(char *buf, uint8_t size)
{
    int16_t r;
    uint8_t count=0;

    while (count < size) {
        r = cdc_getchar();
        if (r != -1) {
            if (r == '\r' || r == '\n') return count;
            if (r >= ' ' && r <= '~') {
                *buf++ = r;
                cdc_putchar(r);
                count++;
            }
        } else {
            if (!cdc_configured() ||
              !(cdc_get_control() & CDC_DTR)) {
                // user no longer connected
                return 255;
            }
            // just a normal timeout, keep waiting
        }
    }
    return count;
}

// parse a user command and execute it, or print an error message
//
void parse_and_execute_command(const char *buf, uint8_t num)
{
    uint8_t port, pin, val;

    if (num < 3) {
        send_str(PSTR("unrecognized format, 3 chars min req'd\r\n"));
        return;
    }
    // first character is the port letter
    if (buf[0] >= 'A' && buf[0] <= 'F') {
        port = buf[0] - 'A';
    } else if (buf[0] >= 'a' && buf[0] <= 'f') {
        port = buf[0] - 'a';
    } else {
        send_str(PSTR("Unknown port \""));
        cdc_putchar(buf[0]);
        send_str(PSTR("\", must be A - F\r\n"));
        return;
    }
    // second character is the pin number
    if (buf[1] >= '0' && buf[1] <= '7') {
        pin = buf[1] - '0';
    } else {
        send_str(PSTR("Unknown pin \""));
        cdc_putchar(buf[0]);
        send_str(PSTR("\", must be 0 to 7\r\n"));
        return;
    }
    // if the third character is a question mark, read the pin
    if (buf[2] == '?') {
        // make the pin an input
        *(uint8_t *)(0x21 + port * 3) &= ~(1 << pin);
        // read the pin
        val = *(uint8_t *)(0x20 + port * 3) & (1 << pin);
        cdc_putchar(val ? '1' : '0');
        send_str(PSTR("\r\n"));
        return;
    }
    // if the third character is an equals sign, write the pin
    if (num >= 4 && buf[2] == '=') {
        if (buf[3] == '0') {
            // make the pin an output
            *(uint8_t *)(0x21 + port * 3) |= (1 << pin);
            // drive it low
            *(uint8_t *)(0x22 + port * 3) &= ~(1 << pin);
            return;
        } else if (buf[3] == '1') {
            // make the pin an output
            *(uint8_t *)(0x21 + port * 3) |= (1 << pin);
            // drive it high
            *(uint8_t *)(0x22 + port * 3) |= (1 << pin);
            return;
        } else {
            send_str(PSTR("Unknown value \""));
            cdc_putchar(buf[3]);
            send_str(PSTR("\", must be 0 or 1\r\n"));
            return;
        }
    }
    // otherwise, error message
    send_str(PSTR("Unknown command \""));
    cdc_putchar(buf[0]);
    send_str(PSTR("\", must be ? or =\r\n"));
}
