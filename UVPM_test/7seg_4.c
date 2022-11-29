/*
 * _7seg_4.c
 *
 * Created: 15.11.2022 14:52:07
 *  Author: m.gasratov
 */ 

// !!! ÍÅ ÀÊÒÓÀËÜÍÎ È ÍÅ ÈÑÏÎËÜÇÓÅÒÑß !!!

#include "7seg_4.h"


const static uint8_t displayNumbers[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};

void printNumber(uint8_t number, uint8_t segment);


void print(uint8_t number) {
	printNumber(number / 1000, 3);
	_delay_us(4);
	printNumber(number % 1000 / 100, 2);
	_delay_us(4);
	printNumber(number % 100 / 10, 1);
	_delay_us(4);
	printNumber(number % 10, 0);
	_delay_us(4);
}

void printNumber(uint8_t digit, uint8_t segment) {
	_7SEG_SEG_PORT &= ~(1<<_7SEG_SEG_0) & ~(1<<_7SEG_SEG_1) & ~(1<<_7SEG_SEG_2) & ~(1<<_7SEG_SEG_3);
	
	_7SEG_DATA_PORT = displayNumbers[digit];
	_7SEG_SEG_PORT |= 1 << (segment + _7SEG_SEG_0);
}