#ifndef cdc_h__
#define cdc_h__

#include <stdint.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// Setup
void cdc_init(void);          // Initialize everything
uint8_t cdc_configured(void); // Is the USB port configured

// Receiving data
int16_t cdc_getchar(void);       // Receive a character (-1 if timeout/error)
uint8_t cdc_available(void);     // Number of bytes in receive buffer
void cdc_flush_input(void);      // Discard any buffered input
void cdc_ready_to_receive(void); // Ready to receive data from terminal.

// Transmitting data
int8_t cdc_putchar(uint8_t c);                          // Transmit a character
int8_t cdc_putchar_nowait(uint8_t c);                   // Transmit a character, do not wait
int8_t cdc_write(const uint8_t *buffer, uint16_t size); // Transmit a buffer
void cdc_flush_output(void);                            // Immediately transmit any buffered output
void cdc_write_string(const char *data);                // Write string into buffer

// Serial parameters
uint8_t cdc_get_stopbits(void);          // Get the number of stop bits
uint8_t cdc_get_paritytype(void);        // Get the parity type
uint8_t cdc_get_numbits(void);           // Get the number of data bits
uint8_t cdc_get_control(void);           // Get the RTS and DTR signal state
int8_t cdc_set_control(uint8_t signals); // Set DSR, DCD, RI, etc

// Constants corresponding to the various serial parameters
#define CDC_DTR          0x01
#define CDC_RTS          0x02
#define CDC_1_STOP       0
#define CDC_1_5_STOP     1
#define CDC_2_STOP       2
#define CDC_PARITY_NONE  0
#define CDC_PARITY_ODD   1
#define CDC_PARITY_EVEN  2
#define CDC_PARITY_MARK  3
#define CDC_PARITY_SPACE 4
#define CDC_DCD          0x01
#define CDC_DSR          0x02
#define CDC_BREAK        0x04
#define CDC_RI           0x08
#define CDC_FRAME_ERR    0x10
#define CDC_PARITY_ERR   0x20
#define CDC_OVERRUN_ERR  0x40

// Everything below this point is only intended for serial.c
#ifdef CDC_PRIVATE_INCLUDE
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define EP_TYPE_CONTROL         0x00
#define EP_TYPE_BULK_IN         0x81
#define EP_TYPE_BULK_OUT        0x80
#define EP_TYPE_INTERRUPT_IN    0xC1
#define EP_TYPE_INTERRUPT_OUT   0xC0
#define EP_TYPE_ISOCHRONOUS_IN  0x41
#define EP_TYPE_ISOCHRONOUS_OUT 0x40
#define EP_SINGLE_BUFFER        0x02
#define EP_DOUBLE_BUFFER        0x06
#define EP_SIZE(s) ((s) == 64 ? 0x30 : \
                   ((s) == 32 ? 0x20 : \
                   ((s) == 16 ? 0x10 : \
                    0x00)))

#define MAX_ENDPOINT 4

#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)
#define HW_CONFIG()
#define PLL_CONFIG() (PLLCSR = ((1<<PLLE)|(1<<PLLP0)))
#define CDC_CONFIG() (USBCON = (1<<USBE))
#define CDC_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))

// Standard control endpoint request types
#define GET_STATUS                  0
#define CLEAR_FEATURE               1
#define SET_FEATURE                 3
#define SET_ADDRESS                 5
#define GET_DESCRIPTOR              6
#define GET_CONFIGURATION           8
#define SET_CONFIGURATION           9
#define GET_INTERFACE               10
#define SET_INTERFACE               11
// CDC (communication class device)
#define CDC_SET_LINE_CODING         0x20
#define CDC_GET_LINE_CODING         0x21
#define CDC_SET_CONTROL_LINE_STATE  0x22
#endif

#endif
