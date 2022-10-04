/*
 * Counter.h
 *
 * Created: 30.09.2022 17:01:37
 *  Author: stani
 */ 


#ifndef COUNTER_H_
#define COUNTER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"
#include "UART.h"

void COUNTER_Init(void);
uint16_t Read_Counter(void);
uint16_t Read_CPM(void);

#endif /* COUNTER_H_ */