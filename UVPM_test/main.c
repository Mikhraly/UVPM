/*
 * UVPM_test.c
 *
 * Created: 15.11.2022 14:19:07
 * Author : m.gasratov
 */ 

#include "main.h"

asm("sei");

int main(void)
{
	port_init();
	
 	// TODO считать пзу и если оно не равно нулю перейти в режим WORK
	
	while(1) {
		
		while (mode == HOME_SEC) 
		{
			if ((PIND & (1<<2)) == 0) {
				displayOnesBlink();
				flagDisplayMilSec = 0;
				_delay_ms(300);
			}
			if ((PIND & (1<<3)) == 0) {
				displayOnesBlink();
				flagDisplayMilSec = 1;
				_delay_ms(300);
			}
		}

	}
	
	
	
	while ((PIND & (1<<2)) == 0) {
		counterSec += 1;
		_delay_ms(300);
	}
	while ((PIND & (1<<3)) == 0) {
		counterSec -= 1;
		_delay_ms(300);
	}
	
	switch (mode) {
	case HOME_SEC:
		break;
	case INIT_SEC:
		break;
	case INIT_MILSEC:
		break;
	case WORK:
		break;
	default:
		break;
	}
	
	
}


void displayOnesBlink() {
	_7SEG_SEG_PORT &= ~(1<<_7SEG_SEG_0) & ~(1<<_7SEG_SEG_1) & ~(1<<_7SEG_SEG_2) & ~(1<<_7SEG_SEG_3);
	_delay_ms(300);
}

void displayBlink(uint8_t status) {
	
}