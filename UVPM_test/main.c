/*
 * UVPM_test.c
 *
 * Created: 15.11.2022 14:19:07
 * Author : m.gasratov
 */ 

#include "main.h"


int main(void)
{
	port_init();
	timer1_init();
	timer2_init();
	
	asm("sei");
	
 	// TODO считать ПЗУ и если оно не равно нулю перейти в режим WORK
	
	while(1) {
		
		while (mode == HOME) 
		{	
			if ((BUTTON_PIN & (1<<BUTTON_1)) == 0) {
				buttonCounterON();
				while ((BUTTON_PIN & (1<<BUTTON_1)) == 0);
				buttonCounterOFF();
				
				if (counterButton_s < 2) {
					displaySheet = 0;
					displayOnesBlink();
				} else {
					mode = INIT_SEC;
				}
				
				_delay_ms(200);
			}
			
			if ((BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				_delay_ms(200);
				
				buttonCounterON();
				while (BUTTON_PIN & (1<<BUTTON_2));
				buttonCounterOFF();
				
				if (counterButton_s < 2) {
					displaySheet = 1;
					displayOnesBlink();
				} else {
					mode = INIT_MILSEC;
				}
				
				_delay_ms(200);
			}
		}


// 		while ((BUTTON_PIN & (1<<BUTTON_2)) == 0) {
// 			counter_s += 1;
// 			_delay_ms(90);
// 		}
// 		while ((BUTTON_PIN & (1<<BUTTON_1)) == 0) {
// 			counter_s -= 1;
// 			_delay_ms(90);
// 		}

	}
}



