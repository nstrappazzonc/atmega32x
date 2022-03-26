#include <avr/interrupt.h>

#define GET_DESCRIPTOR 0x06
#define GET_STATUS 0x00
#define SET_ADDRESS 0x05
#define GET_CONFIGURATION 0x08
#define SET_CONFIGURATION 0x09
#define STATUS_IDLE 0x01
#define STATUS_HALT 0x02

#define HW_CONFIG()  (REGCR = 0x00)
#define PLL_CONFIG() (PLLCSR = 0x06)      // Controls USB interface clock 0x06 for 16MHz clock source 0x02 for 8MHz clock source
#define USB_CONFIG() (USBCON = (1<<USBE)) // No UPGPADE for the ATmega32u2
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))

void USBInit();
void general_isr();
void processControlRequest();
void configureEndpoint();

static volatile uint8_t STATUS = 0;
