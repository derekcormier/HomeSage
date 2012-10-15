/*
 * lcd.h
 *
 * Created: 10/12/2012 3:35:49 PM
 *  Author: Derek Cormier
 */ 

#include <stdlib.h>

#ifndef LCD_H_
#define LCD_H_

void initSerialLCD(void);
// POST: Initializes serial communtication for the Serial LCD

void putCharLCD(unsigned char data);

unsigned char getCharLCD(void);
// POST: Send character to the LCD

#endif /* LCD_H_ */