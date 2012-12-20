/*
 * pwm.h
 *
 * Created: 10/28/2012 5:32:50 PM
 *  Author: Derek
 */ 


#ifndef PWM_H_
#define PWM_H_

void interruptEnablePWM(void);
// POST: Enables PCINT2 at pin PORTC7, triggered at any edge

void initPWM(void);
// POST: Initializes timers used in PWM circuit

void lightOn(void);
// POST: Turns light on (80% brightness) and sets state to on

void lightOff(void);
// POST: Turns light off and sets state to off

#endif /* PWM_H_ */