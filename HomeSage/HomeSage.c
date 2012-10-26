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
#include "pc.h"

#define F_CPU 8000000UL

//FILE LCDstream = FDEV_SETUP_STREAM (putCharLCD, getCharLCD, _FDEV_SETUP_RW);

int main(void)
{
	//initSerialADC();
	initSerialLCD();
	initSerialPC();
	//initPeakDet();
	initLCD();
	
	backlightOnLCD();
	WriteLCD("I <3 Chad!");
	
	setCursorLCD(0,1);
	
	WriteLCD("Just Kidding.");
	
	//stdout = &LCDstream;
    while(1)
    {
		//putStrPC("Shit works yo.\n\r");
//		//resetPeakDet();
//		getValueADC(1);
		//_delay_ms(10000);
    }
}