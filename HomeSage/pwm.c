/*
 * pwm.c
 *
 * Created: 10/28/2012 5:32:12 PM
 *  Author: Derek
 */ 

#include <avr/interrupt.h>
#include "pwm.h"

void initPWM(void)
// POST: Initializes the PWM
{
	TCCR0A |= (1 << WGM01);
	TCCR1B |= (1 << CS02)|(1 << CS00);

	OCR1A = 24999;
}

void interruptEnablePWM(void)
// POST: External interrupt one is enabled on pin 0 of PORTA
{
	DDRC &= ~(1 << DDC7);
	
	PORTC |= (1 << PORTC7);
	
	EICRA |= (1 << ISC00);
	
	PCICR |= (1 << PCIE2);
	
	PCMSK2 |= (1 << PCINT23);
	
	sei();
}