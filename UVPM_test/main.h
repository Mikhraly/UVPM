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
#include "timer.h"


#define BUTTON_PIN  PIND
	
enum Buttons {
	BUTTON_1 = 2,
	BUTTON_2 = 3
	};

enum Modes {
	HOME,
	INIT_SEC,
	INIT_MILSEC,
	CHOOSE,
	WORK
	};

volatile uint8_t mode = HOME;
volatile uint16_t counter_s = 1234;
volatile uint16_t counter_ms = 5678;
volatile uint8_t counterButton_33us = 0;	// ��������������� ��������. ������� �������� �� ���������
volatile uint8_t counterButton_s = 0;		// ��������������� ��������. ������� �������� �� ���������

volatile const uint8_t displayNumbers[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};
volatile const uint8_t displayChoose[] = {0x89, 0x00, 0x00, 0xCF};
volatile uint8_t displaySheet = 0;


ISR (TIMER1_COMPA_vect) {
	volatile static uint8_t segment = 0;
	
	_7SEG_SEG_PORT &= ~(1<<_7SEG_SEG_0) & ~(1<<_7SEG_SEG_1) & ~(1<<_7SEG_SEG_2) & ~(1<<_7SEG_SEG_3);
	
	volatile uint16_t divider1 = 10000;
	for (volatile uint8_t i = 0; i < segment; i++) {
		divider1 /= 10;
	}
	volatile uint16_t divider2 = divider1 / 10;
	
	switch (displaySheet) {
	case 0:
		_7SEG_DATA_PORT = displayNumbers[counter_s % divider1 / divider2];
		break;
	case 1:
		_7SEG_DATA_PORT = displayNumbers[counter_ms % divider1 / divider2];
		break;
	case 2:
		_7SEG_DATA_PORT = displayChoose[segment];
		break;
	default:
		break;
	}
	
	_7SEG_SEG_PORT |= 1 << (segment + _7SEG_SEG_0);
	if (++segment > 3) segment = 0;
}


inline void displayON() {
	SET_BIT(TIMSK, OCIE1A);					// ��������� ���������� �� ���������� TIMER1_COMPA_vect
}

inline void displayOFF() {
	RESET_BIT(TIMSK, OCIE1A);				// ��������� ���������� �� ���������� TIMER1_COMPA_vect
	_7SEG_SEG_PORT &= ~(1<<_7SEG_SEG_0) & ~(1<<_7SEG_SEG_1) & ~(1<<_7SEG_SEG_2) & ~(1<<_7SEG_SEG_3);
}

inline static void displayOnesBlink() {
	displayOFF();
	_delay_ms(200);
	displayON();
}

inline void displayBlinkON() {
	OCR1A = 8*125;							// ���������� ������ 8 �����������
}

inline void displayBlinkOFF() {
	OCR1A = 4*125;							// ���������� ������ 4 �����������
}


ISR (TIMER2_OVF_vect) {
	if (++counterButton_33us > 30) {
		counterButton_33us = 0;
		counterButton_s++;
	}
}

inline void buttonCounterON() {
	counterButton_33us = 0;
	counterButton_s = 0;
	SET_BIT(TIMSK, TOIE2);					// ��������� ���������� �� ������������
}

inline void buttonCounterOFF() {
	RESET_BIT(TIMSK, TOIE2);				// ��������� ���������� �� ������������
}

#endif /* MAIN_H_ */