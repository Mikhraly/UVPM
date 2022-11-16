/*
 * _7seg_3.c
 *
 * Created: 15.11.2022 14:52:07
 *  Author: m.gasratov
 */ 

#include <avr/io.h>
#include "7seg_3.h"


enum {
	ZERO = 0b10111111,
	ONE = 0b10000110,
	TWO = 0b11011011,
	THREE = 0b11001111,
	FOUR = 0b11100110,
	FIVE = 0b11101101,
	SIX = 0b11111101,
	SEVEN = 0b10000111,
	EIGHT = 0b11111111,
	NINE = 0b11101111,
	ERROR = 0b11111001
	};

void print(uint8_t number, uint8_t segment);


void _7seg_print(uint8_t number2, uint8_t number1, uint8_t number0) {
	print(number0, 0);
	_delay_us(500);
	print(number1, 1);
	_delay_us(500);
	print(number2, 2);
	_delay_us(500);
}

void print(uint8_t number, uint8_t segment) {
	switch (number) {
	case 0: PORT_7SEG = ZERO; break;
	case 1: PORT_7SEG = ONE; break;
	case 2: PORT_7SEG = TWO; break;
	case 3: PORT_7SEG = THREE; break;
	case 4: PORT_7SEG = FOUR; break;
	case 5: PORT_7SEG = FIVE; break;
	case 6: PORT_7SEG = SIX; break;
	case 7: PORT_7SEG = SEVEN; break;
	case 8: PORT_7SEG = EIGHT; break;
	case 9: PORT_7SEG = NINE; break;
	default: PORT_7SEG = ERROR;
	}
	
	switch (segment) {
	case 0:
		COM_7SEG |= (1 << SEG0);
		COM_7SEG &= ~(1 << SEG1);
		COM_7SEG &= ~(1 << SEG2);
		break;
	case 1:
		COM_7SEG &= ~(1 << SEG0);
		COM_7SEG |= (1 << SEG1);
		COM_7SEG &= ~(1 << SEG2);
		break;
	case 2:
		COM_7SEG &= ~(1 << SEG0);
		COM_7SEG &= ~(1 << SEG1);
		COM_7SEG |= (1 << SEG2);
		break;
	default: asm("nop");
	}
}