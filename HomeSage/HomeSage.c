/*
 * HomeSage.c
 *
 * Created: 10/12/2012 1:46:44 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "adc.h"
#include "circctrl.h"
#include "globalvars.h"
#include "lcd.h"
#include "pc.h"

volatile char recflag = 0;		// Flag to be set by ISR to send readings to server
volatile char statflag = 0;		// Flag to be set to by ISR check status of circuit
volatile char togflag = 0;		// Flag to be set by ISR to toggle state of circuit
volatile char circstat = 0;		// Holds status of circuit (1 = on, 0 = off)

int main(void)
{
	double voltage, current1, current2, current3;
	double power1, power2, power3;
	int currprint = 3;
	int printdelay = 0;
	
	initSerialADC();
	initSerialPC();
	initSerialLCD();
	initCircCtrl();
	_delay_ms(500);			// Wait for LCD to power before initializing
	initLCD();
	
	onCircuit(0);
	onCircuit(1);
	onCircuit(2);
	
	sei();
	
	while(1)
	{
		voltage = getVoltageADC();		// Get voltage reading
		current1 = getCurrentADC(1);	// Get Current reading for circuit 1
		power1 = getPowerADC(voltage, current1);		// Calculate power
		current2 = getCurrentADC(2);	// Get Current reading for circuit 1
		power2 = getPowerADC(voltage, current2);		// Calculate power
		current3 = getCurrentADC(3);	// Get Current reading for circuit 1
		power3 = getPowerADC(voltage, current3);		// Calculate power
		
		clearScreenLCD();							// Clear the LCD
		
		switch(currprint)
		{
		case 1: 
			printLayoutLCD(voltage, current1, power1);	// Print the values for 1
			break;
		case 2:
			printLayoutLCD(voltage, current2, power2);	// Print the values for 2
			break;
		case 3:
			printLayoutLCD(voltage, current3, power3);	// Print the values for 3
			currprint = 0;
			break;
		default:
			break;
		}		
		
		currprint++;
		
		_delay_ms(500);
	
		if(recflag != 0)
		{
			if(recflag & 0b00000001)
			{
				sendValuesPC(1, voltage, current1);
			}
			if(recflag & 0b00000010)
			{
				sendValuesPC(2, voltage, current2);
			}
			if(recflag & 0b00000100)
			{
				sendValuesPC(3, voltage, current3);
			}
		
			recflag = 0;
		}
	
		if(statflag != 0)
		{			
			if(statflag & 0b00000001)
			{
				if(circstat & 0b00000001)
				{
					putCharPC(HS_CIRC0ON);
					putCharPC('\n');
				}
				else
				{
					putCharPC(HS_CIRC0OFF);
					putCharPC('\n');
				}
			}
			if(statflag & 0b00000010)
			{
				if(circstat & 0b00000010)
				{
					putCharPC(HS_CIRC1ON);
					putCharPC('\n');
				}
				else
				{
					putCharPC(HS_CIRC1OFF);
					putCharPC('\n');
				}
			}
			if(statflag & 0b00000100)
			{			
				if(0 != (circstat & 0b00000100))
				{
					putCharPC(HS_CIRC2ON);
					putCharPC('\n');
				}
				else
				{
					putCharPC(HS_CIRC2OFF);
					putCharPC('\n');
				}			
			}
		
			statflag = 0;
		}
	
		if(togflag != 0)
		{	

			if(togflag & 0b00000001)
			{
				if(circstat & 0b00000001)
				{
					offCircuit(0);
				}
				else
				{
					onCircuit(0);
				}
			}
			if(togflag & 0b00000010)
			{
				if(circstat & 0b00000010)
				{
					offCircuit(1);
				}
				else
				{
					onCircuit(1);
				}			
			}
			if(togflag & 0b00000100)
			{			
				if(circstat & 0b00000100)
				{				
					clearScreenLCD();
					setCursorLCD(0,0);
					writeLCD("Toggling");
					_delay_ms(500);
					offCircuit(2);
				}
				else
				{
					onCircuit(2);
				}			
			}
		
			togflag = 0;
		}
	}			
}

ISR(USART0_RX_vect)
{
	char RecievedByte;
	RecievedByte = UDR0;
	
	switch(RecievedByte)
	{
		case HS_GETMEAS0:
			recflag |= 0b00000001;
			break;
		case HS_GETMEAS1:
			recflag |= 0b00000010;
			break;
		case HS_GETMEAS2:
			recflag |= 0b00000100;
			break;
		case HS_GETCSTATE0:
			statflag |= 0b00000001;
			break;
		case HS_GETCSTATE1:
			statflag |= 0b00000010;
			break;
		case HS_GETCSTATE2:
			statflag |= 0b00000100;
			break;
		case HS_TOGCSTATE0:
			togflag |= 0b00000001;
			break;
		case HS_TOGCSTATE1:
			togflag |= 0b00000010;
			break;
		case HS_TOGCSTATE2:
			togflag |= 0b00000100;
			break;
		default:
			break;
	}
}
