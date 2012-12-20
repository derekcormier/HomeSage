/*
 * adc.c
 *
 * Created: 10/12/2012 3:37:01 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <math.h>
#include <util/delay.h>
#include "adc.h"
#include "lcd.h"

void initSerialADC(void)
	// POST: Initializes SPI serial communication for the ADC
{
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);			// Set MOSI, SCK, SS output
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA);	// Enable SPI, Enable Master,
													//	mode 0,0
}

char readWriteADC(char data)
	// POST: Writes a character to the ADC, and returns data from the ADC
{
	SPDR = data;						// Write data to the register to be sent
	while(!(SPSR & (1<<SPIF)));			// Wait for data to be sent, received
	data = SPDR;						
	return data;						// Return data from the register
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

double getCurrentADC(int channel)
	// POST: Returns the current RMS corresponding to the ADC value
{
	unsigned int samples = 6000;	// Number of samples to be taken from ADC
	signed int value[6000];			// Array of sample values
	double ADCTotal=0;				// Total of all sample values added together
	int center;						// Average ADC value which each certain current sensor 
									//  tends to float around when no load is attached
	
	switch(channel)					// These are each of the values that the current
	{								//  sensors tend to float around when there is no
	case 1:							//  load on the circuit. The this is subtracted from
		center = 2067;				//	the sample value to get the distance from 0Amps
		break;						//	that the current sensor is reading.
	case 2:
		center = 2059;
		break;
	case 3:
		center = 2110;
		break;
	default:
		break;
	}		
	
	for(int i=0;i<samples;i++)		// Get 6000 samples from the current sensor
	{
		value[i]=(getValueADC(channel)-center);		// Subtract center value to get 
	}												//	amplitude
	
	for(int j=0;j<samples;j++)		// Add all samples (squared) together
	{
		if(value[j] < 0)			// If the amplitide is negative, take the absolute
		{							//	value; important for RMS calculation
			value[j] = -value[j];
		}
	ADCTotal+= pow(value[j],2);		// Square the value and add to total
	}	

	switch(channel)		// Return current RMS, based on which channel. Each channel
	{					//	is calibrated differently to meet specifications
		case 1:
			return (sqrt(ADCTotal/samples)+2.26)/141.45;
		case 2:
			return (sqrt(ADCTotal/samples)+1.33)/140.67;
		case 3:
			return (sqrt(ADCTotal/samples)-.92)/139.32;
		default:
			return 0;
	}
}

double getVoltageADC(void)
	// POST: Returns the voltage RMS corresponding the the ADC value
{
	double voltage = 0;					// RMS voltage
	double ADCValue = 0;				// Total of samples added together
	
	for(int i=0;i<1000;i++)				// Take 1000 samples, add them
	{
		ADCValue += getValueADC(0);
	}	
	ADCValue = ADCValue / 1000.0;		// divide by 1000 for average
	voltage = ((ADCValue+36334)/320.85);		
	// Equation relating ADCValue to VRMS
	return voltage;
}

double getPowerADC(double voltage, double current)
	// POST: Return the average power
{
	return voltage*current;			//Calculate the power; return
}