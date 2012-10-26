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

unsigned char getCharPC(void);
// POST: Send character to the PC

void putStrPC(char str[]);


#endif /* PC_H_ */