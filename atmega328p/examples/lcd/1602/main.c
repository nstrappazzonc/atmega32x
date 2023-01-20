#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define E (1<<PD3)
#define RS (1<<PD2)

void lcdinit(void);
void latch(void);
void lcdcmd(uint8_t cmd);
void lcdchar(uint8_t data);
void lcdprint(char *str);
void lcdsetcursor(uint8_t x, uint8_t y);
void LCDClear(void);

int main(void) {
    lcdinit();

    while (1) {
        lcdsetcursor(1,1);
        lcdprint("Demo...:01234567");
        _delay_ms(1000);
        //lcdcmd(0);
        lcdcmd(0x01);
        _delay_ms(5);
        lcdsetcursor(1,1);
        lcdprint("Matias");
        _delay_ms(1000);

    };

    return 0;
}

void lcdinit(void){   
   //initialize PORTs for LCD   
   DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);
   //Send Pulse to Latch the data  
   latch();
   _delay_ms(2);  //delay for stable power
   // Command to set up the LCD
   lcdcmd(0x33);
   _delay_us(100);
  lcdcmd(0x32);
  _delay_us(100);
   lcdcmd(0x28);    // 2 lines 5x7 matrix dot
   _delay_us(100);
   //lcdcmd(0x0E);  // display ON, Cursor ON
    lcdcmd(0x0C);  // display ON, Cursor ON
  _delay_us(100);
   lcdcmd(0x01);    //clear LCD
   _delay_ms(20);   //wait
   lcdcmd(0x06);    //shift cursor to right
   _delay_ms(1);   
}
   
void latch(void){
    PORTD |= E;     //send high
    _delay_us(500);     //wait
    PORTD &= ~E;        //send low
    _delay_us(500);     //wait
}
   
void lcdcmd(uint8_t cmd){
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0);  // send high nibble
    PORTD &= ~RS; //send 0 to select command register
    latch();          //latch the data     
    PORTD = (PORTD & 0x0F) | (cmd<<4);    //send low nibble 
    latch();          //latch the data      
}
      
void lcdchar(uint8_t data){
    PORTD = (PORTD & 0x0F) | (data & 0xF0);  // send high nibble
    PORTD |= RS;  //send 1 to select data register
    latch();     
    PORTD = (PORTD & 0x0F) | (data<<4);  // send high nibble
    latch();      
}
      
void lcdprint(char *str){
    uint8_t k=0;
    while(str[k] != 0){
        lcdchar(str[k]);
        k++;
    }
}
 
void lcdsetcursor(uint8_t x, uint8_t y){
    uint8_t firstcharadr[] = {0x80, 0xC0, 0x94, 0xD4};
    lcdcmd(firstcharadr[y-1] + x-1);
    _delay_us(1000);
}
