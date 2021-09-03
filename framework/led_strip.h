#define RGBLIGHT_DI_PORT PORTD
#define RGBLIGHT_DI_PIN PD1

typedef struct { uint8_t red, green, blue; } RGBColor;
extern void __attribute__((noinline)) led_strip(RGBColor *colors);
