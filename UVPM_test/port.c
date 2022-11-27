/*
 * port.c
 *
 * Created: 15.11.2022 14:20:42
 *  Author: m.gasratov
 */ 

#include "port.h"


void port_init() {
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRB = 0;
	PORTB = 0xFF;
	
	DDRC = 0b01111111;
	PORTC = 0b10000000;
	
	DDRD = 0b11110000;
	PORTD = 0b00001111;
	
	//MCUCR	= 0b00001010;		// Режим работы внешних прерываний INT0, INT1 по заднему фронту	
	//GICR |= 1<<INT0 | 1<<INT1;	// Включить внешние прерывания INT0, INT1
}