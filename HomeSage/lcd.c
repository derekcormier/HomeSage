/*
 * lcd.c
 *
 * Created: 10/12/2012 3:35:13 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <string.h>
#include "lcd.h"
#include "pc.h"

void initSerialLCD(void)
	// POST: Initializes serial for LCD at 9600 baud, 8 bit, no parity, 1 stop bit
{
	UBRR1L = 0b00110011;			// Set UBRR1 to 51, for 9600 baud
	UBRR1H = 0;
	
	DDRD |= 0b00001000;				// Set the TX line to output
	
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);		// Enable recieve and transmit lines
	
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);		// Frame: 8-bit, no parity, 1 stop bit
}

void initLCD(void)
	// POST: Initializes serial communtication for the Serial LCD:
	//		16X2 characters with 5X8 dots font
	//		Display on
	//		Cursor off
	//		Blinking off
	//		Address increments by 1 from left to right
	//		No screen shift
	//		Backlight off 
{
	putByteLCD(SLCD_CONTROL_HEADER);		// Power LCD off
	putByteLCD(SLCD_POWER_OFF);
	
	putByteLCD(SLCD_CONTROL_HEADER);		// Power LCD on, send bytes to initialize serial LCD
	putByteLCD(SLCD_POWER_ON);
	putByteLCD(SLCD_INIT_ACK);
	
	while(getCharLCD() != SLCD_INIT_DONE);	// Check if LCD initialized properly
}

void putByteLCD(unsigned char data)
// POST: Sends one byte of data to the LCD
{
	while (!(UCSR1A & (1<<UDRE1)));			// Wait for the transmit buffer to be empty
	
	UDR1 = data;							// Put data in buffer and send
}

unsigned char getCharLCD(void)
// POST: Recieves one byte of data from the LCD
{
	while (!(UCSR1A & (1<<RXC1)));			// Wait for data to be received
	
	return UDR1;							// Get data from buffer
}

void WriteLCD(char str[])
// POST: Writes a string of characters to the LCD
{
	putByteLCD(SLCD_CHAR_HEADER);			// Tell LCD to write follwing data to screen
	
	for(int i=0; i<strlen(str); i++)		// Put each character to the LCD
	{
		putByteLCD(str[i]);
	}	
}

void backlightOnLCD(void)
// POST: Turns on the LCD Backlight
{
	putByteLCD(SLCD_CONTROL_HEADER);		// Turn backlight on
	putByteLCD(SLCD_BACKLIGHT_ON);
}	

void setCursorLCD(int col, int row)
// PRE:	 0<=col<=15, row = 0 or 1
// POST: Sets the cursor to the specified column and row
{
	putByteLCD(SLCD_CONTROL_HEADER);	
	putByteLCD(SLCD_CURSOR_HEADER);			// Tell LCD next two bytes are coordinate for cursor
	putByteLCD(col); 
	putByteLCD(row);
}