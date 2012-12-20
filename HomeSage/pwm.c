/*
 * pwm.c
 *
 * Created: 10/28/2012 5:32:12 PM
 *  Author: Derek
 */ 

#include <avr/interrupt.h>
#include "pwm.h"
volatile char circstat;

void interruptEnablePWM(void)
	// POST: Enables PCINT2 at pin PORTC7, triggered at any edge
{
	DDRC &= ~(1 << DDC7);		// Set pin PORTC7 to input
	
	DDRC |= (1 << DDC0);		// Set pin PORTC0 to output
	
	PORTC &= ~(1 << PORTC7);	// Enable internal pull-up resistor
	
	EICRA |= (1 << ISC20);		// Trigger interrupt on any edge
	EICRA &= ~(1 << ISC21);		
	
	PCICR |= (1 << PCIE2);		// Enable PCINT2
	
	PCMSK2 |= (1 << PCINT23);	// Use PORTC7 for interrupt pin
}

void initPWM(void)
	// POST: Initializes timer used in PWM circuit
{
	TCCR0A |= (1 << WGM01);		// CTC Mode
	
	TCCR0B |= (1 << CS02) | (1 << CS00);		// Timer prescaler 256
	
	TIMSK0 |= (1 << OCIE0A);	// Timer compare int enable
	
	OCR0A = 60;
}

void lightOn(void)
	// POST: Turns on light and PWM timer
{
	
}

void lightOff(void)
{
	
}	