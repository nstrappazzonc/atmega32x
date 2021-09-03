// This may be 4 for all AVR chips
#define PORT_SHIFTER 4

// If you want to add more to this list, reference the PINx definitions in these header
// files: https://github.com/vancegroup-mirrors/avr-libc/tree/master/avr-libc/include/avr
#define ADDRESS_BASE 0x00
#define PINB_ADDRESS 0x3
#define PINC_ADDRESS 0x6
#define PIND_ADDRESS 0x9

#define _PIN_ADDRESS(p, offset) _SFR_IO8(ADDRESS_BASE + ((p) >> PORT_SHIFTER) + (offset))

// Port X Input Pins Address
#define PINx_ADDRESS(p) _PIN_ADDRESS(p, 0)
// Port X Data Direction Register,  0:input 1:output
#define DDRx_ADDRESS(p) _PIN_ADDRESS(p, 1)
// Port X Data Register
#define PORTx_ADDRESS(p) _PIN_ADDRESS(p, 2)

#define RGBLIGHT_DI_PIN PD1

typedef struct { uint8_t red, green, blue; } RGBColor;
extern void __attribute__((noinline)) led_strip(uint8_t pin, RGBColor *colors);
