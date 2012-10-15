/*
 * HomeSage.c
 *
 * Created: 10/12/2012 1:46:44 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "peakdet.h"
#include "lcd.h"
#include "adc.h"

FILE LCDstream = FDEV_SETUP_STREAM (putCharLCD, getCharLCD, _FDEV_SETUP_RW);

int main(void)
{
	initSerialLCD();
	initPeakDet();
	
	//stdout = &LCDstream;
    while(1)
    {
		fprintf(&LCDstream, "U");
    }
}