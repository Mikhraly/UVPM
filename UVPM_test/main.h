/*
 * main.h
 *
 * Created: 21.11.2022 15:24:50
 *  Author: m.gasratov
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 8000000UL

#define SET_BIT(REG, BIT) (REG |= (1<<BIT))
#define RESET_BIT(REG, BIT) (REG &= ~(1<<BIT))

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "port.h"
#include "7seg_3.h"


ISR (INT0_vect) {
	
}

ISR (INT1_vect) {
	
}


#endif /* MAIN_H_ */