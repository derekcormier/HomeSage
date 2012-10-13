/*
 * HomeSage.c
 *
 * Created: 10/12/2012 1:46:44 PM
 *  Author: Derek Cormier
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "peakdet.h"
#include "lcd.h"
#include "adc.h"

int main(void)
{
	initPeakDet();
    while(1)
    {
       resetPeakDet();
    }
}