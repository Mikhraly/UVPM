/*
 * UVPM_test.c
 *
 * Created: 15.11.2022 14:19:07
 * Author : m.gasratov
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "port.h"
#include "7seg_3.h"

uint8_t numbers[] = {0, 5, 7};

ISR (INT0_vect) {
	
}

ISR (INT1_vect) {
	
}

//asm("sei");

int main(void)
{
	port_init();
	
    while (1) 
    {
		if ((PIND & (1<<2)) == 0) {
			PORTD |= 1<<4;
			numbers[0]++;
			_delay_ms(5);
		}
		
		
		_7seg_print(numbers[2], numbers[1], numbers[0]);
    }
}

