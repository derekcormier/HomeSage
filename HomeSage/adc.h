/*
 * adc.h
 *
 * Created: 10/12/2012 3:37:15 PM
 *  Author: Derek Cormier
 */ 


#ifndef ADC_H_
#define ADC_H_

void initSerialADC(void);

char readWriteADC(char data);

//char recieveADC(void);

signed int getValueADC(int channel);

double getCurrentADC(unsigned int ADCValue);

double getVoltageADC(unsigned int ADCValue);

#endif /* ADC_H_ */