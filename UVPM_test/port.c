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
	
	DDRB = 0b00000001;
	PORTB = 0b11111110;
	
	DDRC = 0x00;
	PORTC = 0xFF;
	
	DDRD = 0b11110000;
	PORTD = 0b00001111;
	
	//MCUCR	= 0b00001010;		// Режим работы внешних прерываний INT0, INT1 по заднему фронту	
	//GICR |= 1<<INT0 | 1<<INT1;	// Включить внешние прерывания INT0, INT1
}