#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <pin.h>
#include <led_strip.h>

#define LED_COUNT 6

RGBColor colors[LED_COUNT];

int main() {
  colors[0] = (RGBColor){ 1, 0, 0 };
  colors[1] = (RGBColor){ 0, 2, 1 };
  colors[2] = (RGBColor){ 1, 1, 0 };
  colors[3] = (RGBColor){ 1, 0, 0 };
  colors[4] = (RGBColor){ 1, 0, 0 };
  colors[5] = (RGBColor){ 1, 0, 0 };
  // colors[6] = (RGBColor){ 1, 1, 1 };
  // colors[7] = (RGBColor){ 1, 1, 1 };

  pin_setup(1, OUTPUT, LOW);
  led_strip(colors);

  while (1) {}
}
