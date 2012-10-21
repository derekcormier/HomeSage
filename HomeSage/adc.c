/*
 * adc.c
 *
 * Created: 10/12/2012 3:37:01 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include "adc.h"
#include "lcd.h"

void initSerialADC(void)
{
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	SPCR = (1<<SPE)|(1<<MSTR);
}

void transmitADC(char data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

char recieveADC(void)
{
/* Wait for reception complete */
while(!(SPSR & (1<<SPIF)))
;
/* Return Data Register */
return SPDR;
}	

void getValueADC(void)
{
	PORTB |= (0<<PB4);
	PORTB |= (0<<PB4);
	char high=0b00000000;
	char low=0b00000000;
	high=SPSR;
	putCharLCD(high);
	putStrLCD("in loop\n\r");
	transmitADC(0b00001100);
	putStrLCD("transmitted\n\r");
	high = recieveADC();
	putStrLCD("recieved\n\r");
	//low = recieveADC();
	PORTB |= (0<<PB4);
	
	putCharLCD(high);
	putCharLCD(low);
}