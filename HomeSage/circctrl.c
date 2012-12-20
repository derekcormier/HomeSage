/*
 * circctrl.c
 *
 * Created: 12/18/2012 4:02:25 PM
 *  Author: Derek
 */ 

#include <avr/io.h>
#include "circctrl.h"
#include "globalvars.h"

//volatile char circstat;		// Holds status of circuit (1 = on, 0 = off)

void initCircCtrl(void)
	// POST: initializes control for circuits
{
	DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC6);
		// Set pins 0, 1 and 3 on PORTC to outputs, used to control circuits
		
	PORTC &= ~((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC6));
		// Make all outputs low
}

void onCircuit(int circuit)
	// POST: Turn specific circuit on, sets status
{
	switch(circuit)		// Check which circuit to deal with
	{
	case 0:
		PORTC |= (1 << PORTC0);		// Set PORTC0 output high
		circstat |= 0b00000001;		// Set status to on
		break;
	case 1:
		PORTC |= (1 << PORTC1);		//	SEE 
		circstat |= 0b00000010;		//	ABOVE
		break;
	case 2:
		PORTC |= (1 << PORTC6);
		circstat |= 0b00000100;
		break;
	default:
		break;
	}		
}

void offCircuit(int circuit)
	// POST: Turn specific circuit off, sets status
{
	switch(circuit)		// Check which circuit to deal with
	{
	case 0:
		PORTC &= ~(1 << PORTC0);	// Set PORTC0 output low
		circstat &= ~(0b00000001);	// Set status to off
		break;
	case 1:
		PORTC &= ~(1 << PORTC1);	//	SEE
		circstat &= ~(0b00000010);	//	ABOVE
		break;
	case 2:
		PORTC &= ~(1 << PORTC6);
		circstat &= ~(0b00000100);
		break;
	default:
		break;
	}
}