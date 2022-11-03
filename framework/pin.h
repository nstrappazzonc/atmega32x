#include <avr/pgmspace.h>

#define HIGH 0x1
#define LOW  0x0

#define OUTPUT 0x1
#define INPUT 0x0

#define D0 0x00 //  0
#define D1 0x01 //  1
#define D2 0x02 //  2
#define D3 0x03 //  3
#define D4 0x04 //  4
#define D5 0x05 //  5
#define D6 0x06 //  6
#define D7 0x07 //  7
#define B0 0x08 //  8
#define B1 0x09 //  9
#define B2 0x0A // 10
#define B3 0x0B // 11
#define B4 0x0C // 12
#define B5 0x0D // 13
#define B6 0x0E // 14
#define B7 0x0F // 15
#define C2 0x10 // 16
#define C4 0x11 // 17
#define C5 0x12 // 18
#define C6 0x13 // 19
#define C7 0x14 // 20

#define pin_get_id(P) ( (volatile uint8_t *)( pgm_read_word( pins + (P))) )
#define port_get_id(P) ( (volatile uint8_t *)( pgm_read_word( ports + (P))) )
#define dir_get_id(P) ( (volatile uint8_t *)( pgm_read_word( dir + (P))) )
#define mask_get_id(P) ( pgm_read_byte( masks + (P) ) )
#define get_addr_port_id(P) ( pgm_read_byte( portAddr + (P) ) )

extern void pin_setup(uint8_t pin, uint8_t mode, uint8_t state);
extern void pin_set_state(uint8_t pin, uint8_t state);
extern uint8_t pin_get_state(uint8_t port, uint8_t pin);
extern uint8_t pin_get(uint8_t pin);
