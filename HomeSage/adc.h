/*
 * adc.h
 *
 * Created: 10/12/2012 3:37:15 PM
 *  Author: Derek Cormier
 */ 


#ifndef ADC_H_
#define ADC_H_

void initSerialADC(void);

void transmitADC(char data);

char recieveADC(void);

void getValueADC(void);

#endif /* ADC_H_ */