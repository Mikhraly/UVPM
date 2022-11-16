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


ISR (INT0_vect) {
	
}

ISR (INT1_vect) {
	
}

//asm("sei");

int main(void)
{
	uint8_t delay = 0;
	
	port_init();
	
    while (1) 
    {
		print(delay);
		
		if ((PIND & (1<<2)) == 0) {
			delay += 1;
			_delay_ms(300);
		}
		
		if ((PIND & (1<<3)) == 0) {
			while (delay) {
				_delay_ms(1000);
				delay--;
				print(delay);
			}
			
			PORTD |= 1<<4;
		}
    }
}

