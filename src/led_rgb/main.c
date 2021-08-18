#include <avr/io.h>
#include <util/delay.h>

/* LED RBG pins */
#define    LED_RED     PD0
#define    LED_GREEN   PD1
#define    LED_BLUE    PD2

/* Rainbow settings */
#define    MAX        (512)
#define    STEP        (1)

/* Fading states */
#define    REDtoYELLOW    (0)
#define    YELLOWtoGREEN    (1)
#define    GREENtoCYAN    (2)
#define    CYANtoBLUE    (3)
#define    BLUEtoVIOLET    (4)
#define    VIOLETtoRED    (5)

/* Global variables */
uint16_t red = MAX;
uint16_t green = 0;
uint16_t blue = 0;
uint16_t state = 0;

void
rainbow(int n)
{

    switch (state) {
    case REDtoYELLOW: green += n; break;
    case YELLOWtoGREEN: red -= n; break;
    case GREENtoCYAN: blue += n; break;
    case CYANtoBLUE: green -= n; break;
    case BLUEtoVIOLET: red += n; break;
    case VIOLETtoRED: blue -= n; break;

    default: break;
    }

    if (red >= MAX || green >= MAX || blue >= MAX || red <= 0 || green <= 0 || blue <= 0) {
        state = (state + 1) % 6; // Finished fading a color so move on to the next
    }
}


int
main(void)
{
    uint16_t i = 0;

    /* --- setup --- */
    
    DDRD = 0b00000111;
    PORTD = 0b00000111;

    /* --- loop --- */

        while (1) {

        /* Rainbow algorithm */

        if (i < red) {
            PORTD &= ~(1 << LED_RED);
        } else {
             PORTD |= 1 << LED_RED;
        }

        if (i < green) {
            PORTD &= ~(1 << LED_GREEN);
        } else {
             PORTD |= 1 << LED_GREEN;
        }

        if (i < blue) {
            PORTD &= ~(1 << LED_BLUE);
        } else {
             PORTD |= 1 << LED_BLUE;
        }

        if (i >= MAX) {
            rainbow(STEP);
            i = 0;
        }

        i++;
    }

    return (0);
}
