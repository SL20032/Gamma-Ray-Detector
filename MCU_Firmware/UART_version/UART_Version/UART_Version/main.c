/*
 * UART_Version.c
 *
 * Created: 30.09.2022 10:02:41
 * Author : SL20032
 */ 

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

#include "UART.h"
#include "Counter.h"

void CLK_init(void)
{
	//internal oscillator set by fuse to 20 MHz
	ccp_write_io((void*) & (CLKCTRL.MCLKCTRLA), (CLKCTRL_CLKSEL_OSC20M_gc));	//set clock src to 20/16 MHz internal oscillator
	ccp_write_io((void *)&(CLKCTRL.MCLKCTRLB), CLKCTRL_PDIV_4X_gc | 1 << CLKCTRL_PEN_bp);	//prescaller 4
}


int main(void)
{
	CLK_init();
    UART_Init();
	COUNTER_Init();
	sei();
	
    while (1) 
    {
		UART_Send_Frame(Read_Counter(),Read_CPM());
		_delay_ms(100);
    }
}

