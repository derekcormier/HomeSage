/*
 * pc.h
 *
 * Created: 10/25/2012 5:22:39 PM
 *  Author: Derek
 */ 


#ifndef PC_H_
#define PC_H_


void initSerialPC(void);
// POST: Initializes serial communtication for the PC

void putCharPC(unsigned char data);
// POST: Sends one character to the PC

unsigned char getCharPC(void);
// POST: Get a character from the PC

void putStrPC(char str[]);
// POST: Sends a string to the PC


#endif /* PC_H_ */