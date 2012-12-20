/*
 * pc.h
 *
 * Created: 10/25/2012 5:22:39 PM
 *  Author: Derek
 */ 

#ifndef PC_H_
#define PC_H_

#define HS_GETMEAS0					0xA0
#define HS_GETMEAS1					0xA1
#define HS_GETMEAS2					0xA2
#define HS_GETCSTATE0				0XB0
#define HS_GETCSTATE1				0XB1
#define HS_GETCSTATE2				0XB2
#define HS_TOGCSTATE0				0xC0
#define HS_TOGCSTATE1				0xC1
#define HS_TOGCSTATE2				0xC2
#define HS_CIRC0ON					0xD0
#define HS_CIRC1ON					0xD1
#define HS_CIRC2ON					0xD2
#define HS_CIRC0OFF					0xD8
#define HS_CIRC1OFF					0xD9
#define HS_CIRC2OFF					0xDA


void initSerialPC(void);
// POST: Initializes serial communication for the PC

void putCharPC(unsigned char data);
// POST: Sends one character to the PC

unsigned char getCharPC(void);
// POST: Get a character from the PC

void putStrPC(char str[]);
// POST: Sends a string to the PC

void sendValuesPC(int device, double voltage, double current);
// POST: Sends values to the PC for storage in the SQL table

#endif /* PC_H_ */