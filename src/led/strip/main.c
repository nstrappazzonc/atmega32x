#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <pin.h>
#include <led_strip.h>

#define LED_COUNT 3

RGBColor colors[LED_COUNT];

int main() {
  colors[0] = (RGBColor){ 0, 0, 1 };
  colors[1] = (RGBColor){ 0, 0, 1 };
  colors[2] = (RGBColor){ 0, 0, 1 };

  pin_setup(1, OUTPUT, LOW);
  led_strip(colors);

  while (1) {}
}
