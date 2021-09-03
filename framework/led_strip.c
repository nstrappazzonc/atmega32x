// This is AVR code for driving the RGB LED strips from Pololu.
//
// This version can control any AVR pin.  It uses "lds" and "sts" instructions,
// which means it has to write to the entire port register every time it toggles
// the I/O line, but that should be safe because interrupts are disabled.
//
// It allows complete control over the color of an arbitrary number of LEDs.
// This implementation disables interrupts while it does bit-banging with
// inline assembly.

// This line specifies the frequency your AVR is running at.
// This code supports 20 MHz, 16 MHz and 8MHz
// #define F_CPU 20000000

// These lines specify what pin the LED strip is on.
// You will either need to attach the LED strip's data line to PH3
// (pin 6 on the Arduino Mega 2560) or change these
// lines to specify a different pin.

#include <avr/interrupt.h>
#include <util/delay.h>
#include "pin.h"
#include "led_strip.h"

void __attribute__((noinline)) led_strip(uint8_t pin, RGBColor *colors) {
  uint16_t count = sizeof(RGBColor) + 1;

  pin_setup(pin, OUTPUT, LOW);

  cli();
  while (count--) {
    // Send a color to the LED strip.
    // The assembly below also increments the 'colors' pointer,
    // it will be pointing to the next color at the end of this loop.
    asm volatile (
        "ld __tmp_reg__, %a0+\n"
        "ld __tmp_reg__, %a0\n"
        "rcall send_led_strip_byte%=\n"  // Send red component.
        "ld __tmp_reg__, -%a0\n"
        "rcall send_led_strip_byte%=\n"  // Send green component.
        "ld __tmp_reg__, %a0+\n"
        "ld __tmp_reg__, %a0+\n"
        "ld __tmp_reg__, %a0+\n"
        "rcall send_led_strip_byte%=\n"  // Send blue component.
        "rjmp led_strip_asm_end%=\n"     // Jump past the assembly subroutines.

        // send_led_strip_byte subroutine:  Sends a byte to the LED strip.
        "send_led_strip_byte%=:\n"
        "rcall send_led_strip_bit%=\n"  // Send most-significant bit (bit 7).
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"  // Send least-significant bit (bit 0).
        "ret\n"

        // send_led_strip_bit subroutine:  Sends single bit to the LED strip by driving the data line
        // high for some time.  The amount of time the line is high depends on whether the bit is 0 or 1,
        // but this function always takes the same time (2 us).
        "send_led_strip_bit%=:\n"
        "sbi %2, %3\n"                           // Drive the line high.
        "rol __tmp_reg__\n"                      // Rotate left through carry.
        "nop\n" "nop\n"
        "brcs .+2\n" "cbi %2, %3\n"              // If the bit to send is 0, drive the line low now.
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "brcc .+2\n" "cbi %2, %3\n"              // If the bit to send is 1, drive the line low now.

        "ret\n"
        "led_strip_asm_end%=: "
        : "=b" (colors)
        // %a0 points to the next color to display
        : "0" (colors),
          // %2 is the port register (e.g. _SFR_IO_ADDR(PORTD) )
          "I" (_SFR_IO_ADDR(PORTx_ADDRESS(RGBLIGHT_DI_PIN))),
          // %3 is the pin number (0-8) // PD1
          "I" (RGBLIGHT_DI_PIN)
    );
  }
  // Send the reset signal.
  _delay_us(80);
}
