#include <stdint.h>
#include <wait.h>
#include <cdc.h>

int main(void) {
    // Initialize the USB, and then wait for the host
    // to set configuration.  If the Teensy is powered
    // without a PC connected to the USB port, this 
    // will wait forever.
    cdc_init();
    while (!cdc_configured()) /* wait */ ;
    wait(1000);

    while (1) {
        cdc_ready_to_receive();

        // Discard anything that was received prior.  Sometimes the
        // operating system or other software will send a modem
        // "AT command", which can still be buffered.
        cdc_flush_input();

        // Write string into terminal.
        cdc_write_string(PSTR("\r\nHello from serial."));

        wait(1000);
    }
}
