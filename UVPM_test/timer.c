/*
 * timer.c
 *
 * Created: 21.11.2022 14:58:00
 *  Author: m.gasratov
 */ 

#include "timer.h"


void timer0_init() {
	TCNT0 = 0;
	SET_BIT(TIMSK, OCIE0);								// Разрешено прерывание по совпадению
	OCR0 = 125;											// Регистр сравнения
	SET_BIT(TCCR0, WGM01); RESET_BIT(TCCR0, WGM00);		// Mode CTC - сброс при совпадении
	RESET_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);	// Fclk:64, при Fclk=8МГц один отсчет: 8 мкс; 125 отсчетов: 1 мс
}

void timer1_init() {
	TCNT1 = 0;
	SET_BIT(TIMSK, OCIE1A);								// Разрешено прерывание по совпадению
	RESET_BIT(TCCR1B, WGM13); SET_BIT(TCCR1B, WGM12);	// Mode CTC - сброс при совпадении
	RESET_BIT(TCCR1A, WGM11); RESET_BIT(TCCR1A, WGM10);
	RESET_BIT(TCCR1B, CS02); SET_BIT(TCCR1B, CS01); SET_BIT(TCCR1B, CS00);	// Fclk:64, при Fclk=8МГц один отсчет: 8 мкс; 125 отсчетов: 1 мс
	SET_BIT(TIMSK, OCIE1A);								// Разрешено прерывание по совпадению TIMER1_COMPA_vect
	OCR1A = 15*125;										// Прерывание каждуые 15 миллисекунд
	//TIMSK |= 1<<OCIE1B;									// Разрешено прерывание по совпадению TIMER1_COMPB_vect
	//OCR1B = 7812;											// Прерывание каждуые 15 миллисекунд
}