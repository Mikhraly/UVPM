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
	
 	// TODO считать ПЗУ и если оно не равно нулю перейти в режим WORK
	
	while(1) {
		
		while (mode == HOME) 
		{
			if ((BUTTON_PIN & (1<<BUTTON_1)) == 0) {
				displaySheet = 0;
				displayOnesBlink();
				_delay_ms(300);
			}
			if ((BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				displaySheet = 1;
				displayOnesBlink();
				_delay_ms(300);
			}
		}

	}
	
	
	
	while ((PIND & (1<<2)) == 0) {
		counter_s += 1;
		_delay_ms(300);
	}
	while ((PIND & (1<<3)) == 0) {
		counter_s -= 1;
		_delay_ms(300);
	}
	
	switch (mode) {
	case HOME:
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



