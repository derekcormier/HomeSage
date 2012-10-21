/*
 * lcd.c
 *
 * Created: 10/12/2012 3:35:13 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <string.h>
#include "lcd.h"

void initSerialLCD(void)			// POST: Initializes serial communtication for the Serial LCD
{
	UBRR1L = 0b00110011;			// Set UBRR1 to 51, for 9600 baud
	UBRR1H = 0;
	
	DDRD |= 0b00001000;
	
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);		// Enable recieve and transmit lines
	
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);	// Frame: 8-bit, no parity, 1 stop bit
}

void initLCD(void)
{
	while(getCharLCD() != UART_READY);
	
	putCharLCD(SLCD_CONTROL_HEADER);		// Send bytes to initialize serial LCD
	putCharLCD(SLCD_POWER_ON);
	putCharLCD(SLCD_INIT_ACK);
	
	while(getCharLCD() != SLCD_INIT_DONE);
}

void putCharLCD(unsigned char data)
{
	while (!(UCSR1A & (1<<UDRE1)));			// Wait for the transmit buffer to be empty
	
	UDR1 = data;							// Put data in buffer and send
}

unsigned char getCharLCD(void)			// POST: Send character to the LCD
{
	while (!(UCSR1A & (1<<RXC1)));			// Wait for data to be received
	
	return UDR1;							// Get data from buffer
}

void putStrLCD(char str[])
{
	for(int i=0; i<strlen(str); i++)
	{
		putCharLCD(str[i]);
	}	
}