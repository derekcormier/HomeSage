/*
 * HomeSage.c
 *
 * Created: 10/12/2012 1:46:44 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "peakdet.h"
#include "lcd.h"
#include "adc.h"
#include "pc.h"
#include "pwm.h"

int main(void)
{
	initSerialLCD();
	initLCD();
	interruptEnablePWM();

	backlightOnLCD();
	
    while(1)
    {
		writeLCD("hi");
		_delay_ms(2000);
		clearScreenLCD();
		setCursorLCD(0,0);
    }
}

ISR(PCINT2_vect)
{
	writeLCD("meow");
	_delay_ms(20);
}