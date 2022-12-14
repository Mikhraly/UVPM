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
	
	eeprom_busy_wait();
	counter_s = eeprom_read_word((uint16_t *)0x00);
	eeprom_busy_wait();
	counter_ms = eeprom_read_word((uint16_t *)0x02);
	
	if ((counter_s > 9999) || (counter_ms > 999)) {
		counter_s = 0;
		counter_ms = 0;
	} else if (counter_s || counter_ms) {
		mode = WORK;
	}
	
	while(1) {
		switch (mode) {
		case HOME:
			homeMode();
			break;
		case INIT_SEC:
			initSecMode();
			break;
		case INIT_MILSEC:
			initMilsecMode();
			break;
		case CHOOSE:
			chooseMode(displaySheet);
			break;
		case WORK:
			workMode();
			break;
		default:
			break;
		}
	}
}




/************************************************************************/
/*                        ?????? ??????                                 */
/************************************************************************/

void homeMode() {
	while ((BUTTON_PIN & (1<<BUTTON_1)) == 0 || (BUTTON_PIN & (1<<BUTTON_2)) == 0);
	
	while (mode == HOME)
	{
		if ((BUTTON_PIN & (1<<BUTTON_1)) == 0 || (BUTTON_PIN & (1<<BUTTON_2)) == 0) {
			_delay_ms(60);
			
			if ((BUTTON_PIN & (1<<BUTTON_1)) == 0 && (BUTTON_PIN & (1<<BUTTON_2)) != 0) {
				buttonCounterON();
				while (((BUTTON_PIN & (1<<BUTTON_1)) == 0) && (counterButton_s < 2));
				buttonCounterOFF();
				
				if (counterButton_s < 2) {
					displaySheet = 0;
					displayOnesBlink();
				} else {
					mode = INIT_SEC;
				}
				
			} else if (((BUTTON_PIN & (1<<BUTTON_1)) != 0) && (BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				buttonCounterON();
				while (((BUTTON_PIN & (1<<BUTTON_2)) == 0) && (counterButton_s < 2));
				buttonCounterOFF();
				
				if (counterButton_s < 2) {
					displaySheet = 1;
					displayOnesBlink();
				} else {
					mode = INIT_MILSEC;
				}
				
			} else if ((BUTTON_PIN & (1<<BUTTON_1)) == 0 && (BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				buttonCounterON();
				while (((BUTTON_PIN & (1<<BUTTON_1)) == 0 && (BUTTON_PIN & (1<<BUTTON_2)) == 0) && (counterButton_s < 2));
				buttonCounterOFF();
				
				if (counterButton_s >= 2) {
					mode = CHOOSE;
				}
			}
			
			_delay_ms(60);
		}
	}
}


void initSecMode() {
	initTime(INIT_SEC, 0, &counter_s);
}


void initMilsecMode() {
	initTime(INIT_MILSEC, 1, &counter_ms);
}


void initTime(uint8_t _mode, uint8_t _displaySheet, volatile uint16_t *counter) {
	displaySheet = _displaySheet;
	uint16_t upperLimit = mode == INIT_SEC ? 9999 : 999;
	
	displayBlinkON();
	while ((BUTTON_PIN & (1<<BUTTON_1)) == 0 || (BUTTON_PIN & (1<<BUTTON_2)) == 0);
	_delay_ms(60);
	buttonCounterON();
	
	while (mode == _mode) {
		if (counterButton_s >= 5) mode = HOME;
		
		if ((BUTTON_PIN & (1<<BUTTON_1)) == 0) {
			counterButton_s = 0;
			if (*counter > 0) *counter -= 1;
			_delay_ms(200);
			
			while ((BUTTON_PIN & (1<<BUTTON_1)) == 0) {
				counterButton_s = 0;
				if (*counter > 0) *counter -= 1;
				_delay_ms(10);
			}
		} else if ((BUTTON_PIN & (1<<BUTTON_2)) == 0) {
			counterButton_s = 0;
			if (*counter < upperLimit) *counter += 1;
			_delay_ms(200);
			
			while ((BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				counterButton_s = 0;
				if (*counter < upperLimit) *counter += 1;
				_delay_ms(10);
			}
		}
	}
	
	buttonCounterOFF();
	displayBlinkOFF();
}


void chooseMode(uint8_t _displaySheet) {
	displaySheet = 2;
	displayBlinkON();
	while ((BUTTON_PIN & (1<<BUTTON_1)) == 0 || (BUTTON_PIN & (1<<BUTTON_2)) == 0);
	_delay_ms(60);
	buttonCounterON();
	
	while (mode == CHOOSE) {
		if (counterButton_s >= 5) mode = HOME;
		
		if ((BUTTON_PIN & (1<<BUTTON_1)) == 0) {
			mode = WORK;
			_delay_ms(60);
		} else if ((BUTTON_PIN & (1<<BUTTON_2)) == 0) {
			eeprom_busy_wait();
			eeprom_write_word((uint16_t *)0x00, counter_s);
			eeprom_busy_wait();
			eeprom_write_word((uint16_t *)0x02, counter_ms);
			
			mode = HOME;
			displaySheet = _displaySheet;
			displayBlinkOFF();
			displayOnesBlink();
			_delay_ms(100);
			displayOnesBlink();
		}
	}
	
	buttonCounterOFF();
	displaySheet = _displaySheet;
	displayBlinkOFF();
}


void workMode() {
	timer0_init();
	while ((BUTTON_PIN & (1<<BUTTON_1)) == 0 || (BUTTON_PIN & (1<<BUTTON_2)) == 0);
	
	while (mode == WORK) {
		if ((BUTTON_PIN & (1<<BUTTON_1)) == 0 || (BUTTON_PIN & (1<<BUTTON_2)) == 0) {
			_delay_ms(60);
			
			if ((BUTTON_PIN & (1<<BUTTON_1)) == 0 && (BUTTON_PIN & (1<<BUTTON_2)) != 0) {
				displaySheet = 0;
				displayOnesBlink();
			} else if (((BUTTON_PIN & (1<<BUTTON_1)) != 0) && (BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				displaySheet = 1;
				displayOnesBlink();
			} else if ((BUTTON_PIN & (1<<BUTTON_1)) == 0 && (BUTTON_PIN & (1<<BUTTON_2)) == 0) {
				buttonCounterON();
				while (((BUTTON_PIN & (1<<BUTTON_1)) == 0 && (BUTTON_PIN & (1<<BUTTON_2)) == 0) && (counterButton_s < 2));
				buttonCounterOFF();
				
				if (counterButton_s >= 2) {
					mode = HOME;
					stopTimer();
					PORTB &= ~(1 << 0);
					displayOnesBlink();
				}
			}
			
			_delay_ms(60);
		}
	}
}