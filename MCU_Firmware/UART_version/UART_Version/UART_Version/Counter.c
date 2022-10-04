/*
 * Counter.c
 *
 * Created: 30.09.2022 17:01:20
 *  Author: SL20032
 */ 

#include "Counter.h"

volatile uint16_t main_counter = 0;
volatile uint16_t CPM_Arr[CPM_ARR_SIZE];
volatile uint8_t CPM_indeks = 0;
volatile uint8_t CPM_time_indeks = 0;

extern ISR(PORTA_PORT_vect)
{
	main_counter++;
	CPM_Arr[CPM_indeks]++;
	SENSOR_PORT.INTFLAGS = 1 << SENSOR_IQR;
}

extern ISR(TCA0_OVF_vect)
{
	CPM_time_indeks++;
	if (CPM_time_indeks >= CPM_PERIOD_S)
	{
		CPM_time_indeks = 0;
		//UART_Send("ok",2);
		CPM_indeks++;
		if (CPM_indeks >= CPM_ARR_SIZE) CPM_indeks = 0;
		CPM_Arr[CPM_indeks] = 0;
	}
	//UART_Send("ok",2);
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;	//clearing interrupt flag
}

void TCA_Init(void)
{
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc     /* System Clock / 64 */
	| 1 << TCA_SINGLE_ENABLE_bp;    /* Module Enable: enabled */
	
	TCA0.SINGLE.PER = ((uint16_t)(F_CPU / 1024));	//interrupt roughly 1 per second

	TCA0.SINGLE.INTCTRL = 1 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt: enabled */
}

void COUNTER_Init(void)
{
	main_counter = 0;
	CPM_indeks = 0;
	SENSOR_PORT.DIRCLR = SENSOR_PIN;
	SENSOR_PORT.SENSOR_PIN_CR = PORT_ISC_RISING_gc;
	
	TCA_Init();
}

uint16_t Read_Counter(void)
{
	return main_counter;
}


uint16_t Read_CPM(void)
{
	uint16_t temp = 0;
	for (uint16_t i = 0; i < CPM_ARR_SIZE; i++) temp += CPM_Arr[i];
	temp = ((float)(temp * (60 / (CPM_ARR_SIZE * CPM_PERIOD_S))));
	return temp;
}

