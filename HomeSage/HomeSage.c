/*
 * HomeSage.c
 *
 * Created: 10/12/2012 1:46:44 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "peakdet.h"
#include "lcd.h"
#include "adc.h"

#include <avr/interrupt.h>

void init_interrupt(void);

FILE LCDstream = FDEV_SETUP_STREAM (putCharLCD, getCharLCD, _FDEV_SETUP_RW);

int main(void)
{
	init_interrupt();
	initSerialLCD();
	initPeakDet();
	
	sei();
	
	//stdout = &LCDstream;
    while(1)
    {
		
		getValueADC();
		_delay_ms(1000);
    }
}
