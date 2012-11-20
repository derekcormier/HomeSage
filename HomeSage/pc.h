/*
 * pc.h
 *
 * Created: 10/25/2012 5:22:39 PM
 *  Author: Derek
 */ 

#ifndef PC_H_
#define PC_H_

#define HS_RETRIEVEMEASUREMENTS		0xAA
#define HS_GETCIRCUITSTATE0			0XB0
#define HS_GETCIRCUITSTATE1			0XB1
#define HS_GETCIRCUITSTATE2			0XB2
#define HS_TOGGLECIRCUITSTATE0		0xC0
#define HS_TOGGLECIRCUITSTATE1		0xC1
#define HS_TOGGLECIRCUITSTATE2		0xC2

void initSerialPC(void);
// POST: Initializes serial communtication for the PC

void putCharPC(unsigned char data);
// POST: Sends one character to the PC

unsigned char getCharPC(void);
// POST: Get a character from the PC

void putStrPC(char str[]);
// POST: Sends a string to the PC


#endif /* PC_H_ */