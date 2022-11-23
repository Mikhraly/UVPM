/*
 * _7seg_4.c
 *
 * Created: 15.11.2022 14:52:07
 *  Author: m.gasratov
 */ 

#include "7seg_4.h"


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

void printNumber(uint8_t number, uint8_t segment);


void print(uint8_t number) {
	printNumber(number/100, 2);
	_delay_us(500);
	printNumber((number%100)/10, 1);
	_delay_us(500);
	printNumber(number%10, 0);
	_delay_us(500);
}

void printNumber(uint8_t number, uint8_t segment) {
	switch (number) {
	case 0: _7SEG_DATA_PORT = ZERO; break;
	case 1: _7SEG_DATA_PORT = ONE; break;
	case 2: _7SEG_DATA_PORT = TWO; break;
	case 3: _7SEG_DATA_PORT = THREE; break;
	case 4: _7SEG_DATA_PORT = FOUR; break;
	case 5: _7SEG_DATA_PORT = FIVE; break;
	case 6: _7SEG_DATA_PORT = SIX; break;
	case 7: _7SEG_DATA_PORT = SEVEN; break;
	case 8: _7SEG_DATA_PORT = EIGHT; break;
	case 9: _7SEG_DATA_PORT = NINE; break;
	default: _7SEG_DATA_PORT = ERROR;
	}
	
	switch (segment) {
	case 0:
		_7SEG_SEG_PORT |= (1 << _7SEG_SEG_0);
		_7SEG_SEG_PORT &= ~(1 << _7SEG_SEG_1);
		_7SEG_SEG_PORT &= ~(1 << _7SEG_SEG_2);
		break;
	case 1:
		_7SEG_SEG_PORT &= ~(1 << _7SEG_SEG_0);
		_7SEG_SEG_PORT |= (1 << _7SEG_SEG_1);
		_7SEG_SEG_PORT &= ~(1 << _7SEG_SEG_2);
		break;
	case 2:
		_7SEG_SEG_PORT &= ~(1 << _7SEG_SEG_0);
		_7SEG_SEG_PORT &= ~(1 << _7SEG_SEG_1);
		_7SEG_SEG_PORT |= (1 << _7SEG_SEG_2);
		break;
	default: asm("nop");
	}
}