#include <stdint.h>
#include <pin.h>
#include <wait.h>
#include <cdc.h>

int main(void) {
    char buf[32];
    uint8_t n;

    pin_setup(B7, OUTPUT, LOW);

    cdc_init();

    while (1) {
        cdc_ready_to_receive();
        cdc_flush_input();
        cdc_write_string(PSTR("\r\nType PB7 to turn on/off.\r\n"));

        while (1) {
            cdc_write_string(PSTR("> "));
            n = cdc_read_string(buf, sizeof(buf));
            if (n == 255) break;
            if (n == 3 && buf[0] == 'P' && buf[1] == 'B' && buf[2] == '7') {
                cdc_write_string(PSTR("\r\nOK"));
                if ( pin_get_state(B7) == LOW) {
                    pin_set_state(B7, HIGH);
                } else {
                    pin_set_state(B7, LOW);
                }
            }
            
            cdc_write_string(PSTR("\r\n"));
        }
    }

    return 0;
}
