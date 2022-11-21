#include <stdint.h>
#include <wait.h>
#include <cdc.h>

int main(void) {
    cdc_init();

    while (1) {
        // Write string into terminal.
        cdc_write_string(PSTR("\r\nHello from serial."));

        wait(1000);
    }

    return 0;
}
