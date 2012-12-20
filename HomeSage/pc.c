/*
 * pc.c
 *
 * Created: 10/25/2012 5:22:18 PM
 *  Author: Derek
 */ 

#include <avr/io.h>
#include <string.h>
#include "pc.h"
#include "lcd.h"

void initSerialPC(void)			
	// POST: Initializes serial communication for the PC
{
	UBRR0L = 0b00110011;						// Set UBRR1 to 51, for 9600 baud
	UBRR0H = 0;									// (for 8MHz clock)
	
	DDRD |= 0b00000010;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);		// Enable receive and transmit lines
	
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);		// Frame: 8-bit, no parity, 1 stop bit
}

void putCharPC(unsigned char data)
	// POST: Sends one character to the PC
{
	while (!(UCSR0A & (1<<UDRE0)));			// Wait for the transmit buffer to be empty
	
	UDR0 = data;							// Put data in buffer and send
}

unsigned char getCharPC(void)
	// POST: Get a character from the PC
{
	while (!(UCSR0A & (1<<RXC0)));			// Wait for data to be received
	
	return UDR0;							// Get data from buffer
}

void putStrPC(char str[])
	// POST: Sends a string to the PC
{
	for(int i=0; i<strlen(str); i++)		// Put each character to the PC
	{
		putCharPC(str[i]);
	}	
}

void sendValuesPC(int device, double voltage, double current)
{
	char sendstr[19] = "";
	char volt[6];
	char curr[8];
	
	sendstr[0] = device + 0x30;
	sendstr[1] = 0;
	snprintf(volt, 6 , "%3.1f", voltage);
	
	strcat(sendstr, volt);
	snprintf(curr, 8, "%2.7f", current);
	strcat(sendstr, curr);
	strcat(sendstr, "\r");
	
	putStrPC(&sendstr);
	
	setCursorLCD(0,1);
	writeLCD(sendstr);
}