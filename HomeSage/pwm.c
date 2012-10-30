/*
 * pwm.c
 *
 * Created: 10/28/2012 5:32:12 PM
 *  Author: Derek
 */ 

#include <avr/interrupt.h>
#include "pwm.h"

void interruptEnablePWM(void)
	// POST: Enables PCINT2 at pin PORTC7, triggered at any edge
{
	DDRC &= ~(1 << DDC7);		// Set pin PORTC7 to output
	
	PORTC |= (1 << PORTC7);		// Enable internal pull-up resistor
	
	EICRA |= (1 << ISC00);		// Trigger interrupt on any edge
	
	PCICR |= (1 << PCIE2);		// Enable PCINT2
	
	PCMSK2 |= (1 << PCINT23);	// Use PORTC7 for interrupt pin
	
	sei();						// Enable interrupts globally
}