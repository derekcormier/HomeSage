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
#define SLCD_INIT_ACK			0xA5
#define SLCD_INIT_DONE			0xAA


void initSerialLCD(void);
// POST: Initializes serial communtication for the Serial LCD

void initLCD(void);

void putCharLCD(unsigned char data);

unsigned char getCharLCD(void);
// POST: Send character to the LCD

void putStrLCD(char str[]);

#endif /* LCD_H_ */