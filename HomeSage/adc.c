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
	// POST: Initializes SPI serain communication for the ADC
{
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);			// Set MOSI, SCK, SS output
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA);	// Enable SPI, Enable Master,
													//	mode 0,0
}

char readWriteADC(char data)
	// POST: Writes a character to the ADC, and returns data from the ADC
{
	SPDR = data;						// Write data to the register to be sent
	while(!(SPSR & (1<<SPIF)));			// Wait for data to be sent, recieved
	data = SPDR;						
	return data;						// Return data from the resgister
}

signed int getValueADC(int channel)
	// PRE:  0<=channel<=7
	// POST: Returns the 13-bit ADC value	
{
	int sHigh = 0;				// High byte to send to ADC
	int sLow = 0;				// Low byte to send to ADC
	int rHigh=0;				// Holds upper values from ADC
	int rLow=0;					// Holds lower values from ADC
	int value=0;				// Holds combined value to be returned

	PORTB |= (1<<PB4);			// Select line must be brought high before each read
	PORTB &= !(1<<PB4);			// Bring select line low to initiate read from ADC
	
	sHigh=((channel>>1)|(0b00001100));		// Send start bit, select single-sided
	sLow=(channel<<7);						//	reading, select channel
	
	readWriteADC(sHigh);			// Send high byte of ADC request					
	rHigh = readWriteADC(sLow);		// Send low byte of ADC request, get high byte result
	rLow = readWriteADC(0);			// Get high byte of result
	PORTB |= (1<<PB4);				// Bring select line high (deselect ADC)
	
	rHigh &= (0b00111111);			// Add leading zeroes to the high byte to destroy any
									//	random data that is before the actual data
	value = rLow + (rHigh<<8);		// Merge high and low bytes for the complete reading.
	
	return value;
}

double getCurrentADC(unsigned int ADCValue)
	// PRE:  ADCValue is from getValueADC
	// POST: Returns the current RMS corresponding to the ADC value
{
	double current = 0;
	current = ((ADCValue*(1/699.96))-(93.149/699.96));	// Equation relating ADCValue to IRMS
	return current;
}

double getVoltageADC(unsigned int ADCValue)
	// PRE:  ADCValue is from getValueADC
	// POST: Returns the voltage RMS corresponding the the ADC value
{
	double voltage = 0;
	voltage = (ADCValue*(12.0/4095.0))+113.6;			// Equation relating ADCValue to VRMS
	return voltage;
}

double getPowerADC(double voltage, double current)
	// POST: Return the average power
{
	return voltage*current;
}