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
	double current, voltage, power;
	
	initSerialLCD();
	initSerialADC();
	//interruptEnablePWM();
	initLCD();
	initPeakDet();

	backlightOnLCD();

	
		
	while(1)
	{
		voltage = getVoltageADC(getValueADC(0));
		resetPeakDet();
		current = getCurrentADC(getValueADC(1));
		power = getPowerADC(voltage, current);
		clearScreenLCD();
		printLayoutLCD(voltage, current, 100.01);
		_delay_ms(100);
	}
}

/*ISR(PCINT2_vect)
{
	writeLCD("meow");
	_delay_ms(20);
}*/