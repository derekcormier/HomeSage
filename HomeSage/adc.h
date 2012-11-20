/*
 * adc.h
 *
 * Created: 10/12/2012 3:37:15 PM
 *  Author: Derek Cormier
 */ 


#ifndef ADC_H_
#define ADC_H_

void initSerialADC(void);
// POST: Initializes SPI serain communication for the ADC

char readWriteADC(char data);
// POST: Writes a character to the ADC, and returns data from the ADC

signed int getValueADC(int channel);
// PRE:  0<=channel<=7
// POST: Returns the 13-bit ADC value

double getCurrentADC(void);
// POST: Returns the current RMS corresponding to the ADC value

double getVoltageADC(void);
// POST: Return the voltage RMS corresponding the the ADC value

double getPowerADC(double voltage, double current);
// POST: Return the average power

#endif /* ADC_H_ */