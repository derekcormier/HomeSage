/*
 * peakdet.c
 *
 * Created: 10/13/2012 2:41:20 PM
 *  Author: Derek
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "peakdet.h"

void initPeakDet(void)			// POST: Sets up the pin(s) for output
{
	DDRC |= 0b00000001;			// Set PORTC pin 0 to output
	resetPeakDet();				// Initial reset of peak detector			
}

void resetPeakDet(void)			// POST: Resets current sensor peak detector
{
	PORTC = 0b00000001;			// Drain stored voltage from peak detector
	_delay_ms(1500);			// Wait long enough to discharge capacitor
	PORTC = 0b00000000;					// Close NMOS to begin storing voltage
	_delay_ms(1500);
}