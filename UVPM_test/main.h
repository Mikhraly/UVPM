/*
 * main.h
 *
 * Created: 21.11.2022 15:24:50
 *  Author: m.gasratov
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "port.h"
#include "7seg_4.h"
#include "myUtils.h"


enum Modes{
	HOME_SEC,
	HOME_MILSEC,
	INIT_SEC,
	INIT_MILSEC,
	WORK
	};

volatile uint8_t mode = HOME_SEC;
volatile uint16_t counterSec = 0;			// —четкик в секундах
volatile uint16_t counterMilSec = 0;		// —четкик в миллисекундах
volatile const uint8_t segmentNumbers[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};
volatile uint8_t flagDisplayMilSec = 0;

ISR (TIMER1_COMPA_vect) {
	volatile static uint8_t segment = 0;
	volatile static uint8_t display = 0;
	
	display = (flagDisplayMilSec) ? counterMilSec : counterSec;
	_7SEG_SEG_PORT &= ~(1<<_7SEG_SEG_0) & ~(1<<_7SEG_SEG_1) & ~(1<<_7SEG_SEG_2) & ~(1<<_7SEG_SEG_3);
	
	switch (segment) {
	case 0:
		_7SEG_DATA_PORT = ~(segmentNumbers[display % 10000 / 1000]);
		SET_BIT(_7SEG_SEG_PORT, _7SEG_SEG_0);
		break;
	case 1:
		_7SEG_DATA_PORT = ~(segmentNumbers[display % 1000 / 100]);
		SET_BIT(_7SEG_SEG_PORT, _7SEG_SEG_1);
		break;
	case 2:
		_7SEG_DATA_PORT = ~(segmentNumbers[display % 100 / 10]);
		SET_BIT(_7SEG_SEG_PORT, _7SEG_SEG_2);
		break;
	case 3:
		_7SEG_DATA_PORT = ~(segmentNumbers[display % 10]);
		SET_BIT(_7SEG_SEG_PORT, _7SEG_SEG_3);
		break;
	default:
		break;
	}
	
	if (++segment > 3) segment = 0;
}

void displayOnesBlink();
void displayBlink(uint8_t status);


#endif /* MAIN_H_ */