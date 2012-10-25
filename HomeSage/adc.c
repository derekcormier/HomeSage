/*
 * adc.c
 *
 * Created: 10/12/2012 3:37:01 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "adc.h"
#include "lcd.h"

void initSerialADC(void)
{
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA);
}

char readWriteADC(char data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	return data;
}

/*char recieveADC(void)
{
// Wait for reception complete
while(!(SPSR & (1<<SPIF)))
;
// Return Data Register 
return SPDR;
}	*/

signed int getValueADC(int channel)
{
	PORTB |= (1<<PB4);			// Select line must be brought high before each read
	PORTB &= !(1<<PB4);			// Bring select line low to initiate read from ADC
	unsigned int sHigh = 0;		// High byte to send to ADC
	unsigned int sLow = 0;		// Low byte to send to ADC
	signed int rHigh=0;			// Holds upper values from ADC
	signed int rLow=0;			// Holds lower values from ADC
	signed int value=0;			// Holds combined value to be returned
	double d=0;
	char str[10];
	
	//sHigh=
	
	readWriteADC(0b00001100);			
	rHigh = readWriteADC(0b00000000);
	rLow = readWriteADC(0b00000000);
	PORTB |= (1<<PB4);
	
	rHigh &= (0b00111111);
	rLow += (rHigh<<8);
	
	itoa(rLow,str,10);
	putStrLCD(str);
	putStrLCD("\n\r");
	
	//d =getCurrentADC(rLow);
	d = getVoltageADC(rLow);
	sprintf(str,"%f",d);
	putStrLCD(str);
	putCharLCD('A');
	putStrLCD("\n\r");

}

double getCurrentADC(unsigned int ADCValue)
{
	double current = 0;
	current = (ADCValue*(5.0/4095.0))-.02;
	return current;
}

double getVoltageADC(unsigned int ADCValue)
{
	double voltage = 0;
	voltage = (ADCValue*(5/12))+114;
}