/*
 * lcd.h
 *
 * Created: 10/12/2012 3:35:49 PM
 *  Author: Derek Cormier
 */ 

#ifndef LCD_H_
#define LCD_H_

#include <stdlib.h>

#define UART_READY				0xA3
#define SLCD_CONTROL_HEADER		0x9F
#define SLCD_POWER_ON			0x83
#define SLCD_POWER_OFF			0x82
#define SLCD_INIT_ACK			0xA5
#define SLCD_INIT_DONE			0xAA
#define SLCD_CLEAR_DISPLAY		0x65
#define SLCD_BACKLIGHT_ON		0x81
#define SLCD_BACKLIGHT_OFF		0x80
#define SLCD_CURSOR_HEADER		0xFF
#define SLCD_CHAR_HEADER		0xFE


void initSerialLCD(void);
// POST: Initializes serial for LCD at 9600 baud, 8 bit, no parity, 1 stop bit

void initLCD(void);
// POST: Initializes serial communtication for the Serial LCD:
//		16X2 characters with 5X8 dots font
//		Display on
//		Cursor off
//		Blinking off
//		Address increments by 1 from left to right
//		No screen shift
//		Backlight off 

void putByteLCD(unsigned char data);
// POST: Sends one byte of data to the LCD

unsigned char getCharLCD(void);
// POST: Recieves one byte of data from the LCD

void writeLCD(char str[]);
// POST: Writes a string of characters to the LCD

void backlightOnLCD(void);
// POST: Turns on the LCD Backlight

void backlightOffLCD(void);
// POST: Turns off the LCD Backlight

void setCursorLCD(int col, int row);
// PRE:	 0<=col<=15, row = 0 or 1
// POST: Sets the cursor to the specified column and row

void clearScreenLCD(void);
// POST: Clears the LCD screen

void printLayoutLCD(double voltage, double current, double power);
// POST: Prints values in a good format to the LCD

#endif /* LCD_H_ */