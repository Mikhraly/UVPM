/*
 * timer.c
 *
 * Created: 21.11.2022 14:58:00
 *  Author: m.gasratov
 */ 

#include "timer.h"


// ��� �������
void timer0_init() {
	TCNT0 = 0;
	SET_BIT(TIMSK, OCIE0);								// ��������� ���������� �� ����������
	OCR0 = 1*124;										// ������� ��������� - ���������� ������ ������������
	SET_BIT(TCCR0, WGM01); RESET_BIT(TCCR0, WGM00);		// Mode CTC - ����� ��� ����������
	RESET_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);	// Fclk:64, ��� Fclk=8��� ���� ������: 8 ���; 125 ��������: 1 ��
}

// ��� ����������
void timer1_init() {
	TCNT1 = 0;
	SET_BIT(TIMSK, OCIE1A);								// ��������� ���������� �� ���������� TIMER1_COMPA_vect
	OCR1A = 4*125;										// ���������� ������ 4 ������������
	//TIMSK |= 1<<OCIE1B;									// ��������� ���������� �� ���������� TIMER1_COMPB_vect
	//OCR1B = 7812;											// ���������� ������ �� �����������
	RESET_BIT(TCCR1B, WGM13); SET_BIT(TCCR1B, WGM12);	// Mode CTC - ����� ��� ����������
	RESET_BIT(TCCR1A, WGM11); RESET_BIT(TCCR1A, WGM10);
	RESET_BIT(TCCR1B, CS02); SET_BIT(TCCR1B, CS01); SET_BIT(TCCR1B, CS00);	// Fclk:64, ��� Fclk=8��� ���� ������: 8 ���; 125 ��������: 1 ��
}

// ��� ������ ������������ ������� ������
void timer2_init() {
	TCNT2 = 0;
	RESET_BIT(TIMSK, TOIE2);								// ��������� ���������� �� ������������
	//OCR2 = 125;											// ������� ��������� - ���������� ������ ������������
	RESET_BIT(TCCR2, WGM21); RESET_BIT(TCCR2, WGM20);		// Mode NORMAL - ���������� �����
	SET_BIT(TCCR2, CS02); SET_BIT(TCCR2, CS01); SET_BIT(TCCR2, CS00);	// Fclk:1024, ��� Fclk=8��� ���� ������: 128 ���
}