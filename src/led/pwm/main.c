#include <pin.h>
#include <wait.h>

int main(void) {
    uint8_t brightness = 0;
    uint8_t fadein = 1;

    // pin_setup( 0, OUTPUT, LOW); // PD0
    pin_setup(15, OUTPUT, LOW); // PB7
    // pin_setup(19, OUTPUT, LOW); // PC5
    // pin_setup(20, OUTPUT, LOW); // PC6

    while(1) {
        // pin__state(0, brightness);
        pin_set_state(15, brightness);
        // pin_set_state(19, brightness);
        // pin_set_state(20, brightness);

        if(fadein)
            brightness += 5;
        else
            brightness -= 5;

        if(brightness == 0 || brightness == 255) {
            fadein = !fadein;
        }

        wait(50);
    }
}
