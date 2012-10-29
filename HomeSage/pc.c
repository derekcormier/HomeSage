/*
 * pc.c
 *
 * Created: 10/25/2012 5:22:18 PM
 *  Author: Derek
 */ 

#include <avr/io.h>
#include <string.h>
#include "pc.h"

void initSerialPC(void)			// POST: Initializes serial communtication for the Serial LCD
{
	UBRR0L = 0b00110011;			// Set UBRR1 to 51, for 9600 baud
	UBRR0H = 0;
	
	DDRD |= 0b00000010;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);		// Enable recieve and transmit lines
	
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);	// Frame: 8-bit, no parity, 1 stop bit
}

void putCharPC(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));			// Wait for the transmit buffer to be empty
	
	UDR0 = data;							// Put data in buffer and send
}

unsigned char getCharPC(void)			// POST: Send character to the LCD
{
	while (!(UCSR0A & (1<<RXC0)));			// Wait for data to be received
	
	return UDR0;							// Get data from buffer
}

void putStrPC(char str[])
{
	for(int i=0; i<strlen(str); i++)
	{
		putCharPC(str[i]);
	}	
}