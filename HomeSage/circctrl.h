/*
 * circctrl.h
 *
 * Created: 12/18/2012 4:02:49 PM
 *  Author: Derek
 */ 



#ifndef CIRCCTRL_H_
#define CIRCCTRL_H_

void initCircCtrl(void);
// POST: initializes control for circuits

void onCircuit(int circuit);
// POST: Turn specific circuit on, sets status

void offCircuit(int circuit);
// POST: Turn specific circuit off, sets status

#endif /* CIRCCTRL_H_ */