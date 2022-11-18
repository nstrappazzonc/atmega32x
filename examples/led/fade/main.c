#include <pin.h>
#include <wait.h>

int main(void) {
    uint8_t brightness = 0;
    uint8_t fadein = 1;

    pin_setup(B7, OUTPUT, LOW);

    while(1) {
        pin_set_state(B7, brightness);

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
