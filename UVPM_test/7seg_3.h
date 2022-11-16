/*
 * _7seg_3.h
 *
 * Created: 15.11.2022 14:52:28
 *  Author: m.gasratov
 */ 


#ifndef _7SEG_3_H_
#define _7SEG_3_H_


#define F_CPU 8000000UL

#include <util/delay.h>

#define PORT_7SEG PORTC
#define COM_7SEG PORTD
#define SEG0 7
#define SEG1 6
#define SEG2 5


void print(uint8_t number);


#endif /* _7SEG_3_H_ */