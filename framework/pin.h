#include <avr/io.h>
#include <avr/pgmspace.h>

#define HIGH 0x1
#define LOW  0x0

#define OUTPUT 0x1
#define INPUT 0x0

#define pin_get_id(P) ( (volatile uint8_t *)( pgm_read_word( pins + (P))) )
#define port_get_id(P) ( (volatile uint8_t *)( pgm_read_word( ports + (P))) )
#define dir_get_id(P) ( (volatile uint8_t *)( pgm_read_word( dir + (P))) )
#define mask_get_id(P) ( pgm_read_byte( masks + (P) ) )
#define get_addr_port_id(P) ( pgm_read_byte( portAddr + (P) ) )

extern void pin_setup(uint8_t pin, uint8_t mode, uint8_t state);
extern void pin_set_state(uint8_t pin, uint8_t state);
extern uint8_t pin_get_state(uint8_t port, uint8_t pin);
extern uint8_t pin_get(uint8_t pin);
