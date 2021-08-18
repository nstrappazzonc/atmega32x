/*
l74hc165 lib 0x02

copyright (c) Davide Gironi, 2011

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include <avr/io.h>

#ifndef L74HC165_H_
#define L74HC165_H_

//setup ports
#define L74HC165_DDR DDRD
#define L74HC165_PORT PORTD
#define L74HC165_PIN PIND
#define L74HC165_LOADPIN PD2    // 2 PL pin 1
#define L74HC165_CLOCKPIN PD3   // 3 CP pin 2
#define L74HC165_DATAPIN PD4    // 4 Q7 pin 7

// int load = 2; // PL pin 1
// int clockIn = 3; // CP pin 2
// int dataIn = 4; // Q7 pin 7
// int clockEnablePin = 5; // CE pin 15


//setup number of chip attached to the board
#define L74HC165_ICNUMBER 1

//load delay us
#define L74HC165_DELAYLOADUS 5

//delay clock us
#define L74HC165_DELAYCLOCKUS 0

extern void l74hc165_init();
extern void l74hc165_shiftin(uint8_t *bytearray);

#endif
