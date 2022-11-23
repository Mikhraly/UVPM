/*
 * _7seg_4.h
 *
 * Created: 15.11.2022 14:52:28
 *  Author: m.gasratov
 */ 


#ifndef _7SEG_4_H_
#define _7SEG_4_H_


#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>


#define _7SEG_DATA_PORT PORTC
#define _7SEG_SEG_PORT PORTD
#define _7SEG_SEG_0 7
#define _7SEG_SEG_1 6
#define _7SEG_SEG_2 5
#define _7SEG_SEG_3 4


void print(uint8_t number);


#endif /* _7SEG_4_H_ */