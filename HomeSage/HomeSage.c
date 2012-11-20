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
	
	initSerialLCD();			// Initialize Serial
	initSerialADC();
	initSerialPC();
	_delay_ms(500);				// Wait for LCD to power up before initializing
	initLCD();					// Send initialization for LCD
	
	sei();
	
	while(1)					// Infinite loop
	{	
		voltage = getVoltageADC();					// Get voltage reading
		current = getCurrentADC();					// Get current reading
		power = getPowerADC(voltage, current);		// Calculate power
		
		clearScreenLCD();							// Clear the LCD
		printLayoutLCD(voltage, current, power);	// Print the values
		_delay_ms(1000);							// Wait 1 one second before next update
	}
}

ISR(USART0_RX_vect)
{
	char RecievedByte;
	
	RecievedByte = UDR0;
	UDR0 = RecievedByte;
	
	if(RecievedByte == 'D')
	{
		clearScreenLCD();
		setCursorLCD(0,0);
		writeLCD("GOT D");
	}	
}