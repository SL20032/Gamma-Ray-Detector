/*
 * Counter.c
 *
 * Created: 30.09.2022 17:01:20
 *  Author: SL20032
 */ 

#include "Counter.h"

uint16_t main_counter = 0;

extern ISR(PORTA_PORT_vect)
{
	main_counter++;
	SENSOR_PORT.INTFLAGS = 
}



void COUNTER_Init(void)
{
	SENSOR_PORT.DIRCLR = SENSOR_PIN;
	SENSOR_PORT.PIN6CTRL = PORT_ISC_RISING_gc;
}


