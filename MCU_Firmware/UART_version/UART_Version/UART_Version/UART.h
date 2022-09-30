#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "config.h"

// A standard formula for baud rate.
#define USART_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#define UART_STOP_BYTE 0xFE

// Initializes UART module
void UART_Init(void);

// Sends data byte-by-byte on UART.
void UART_Send(uint8_t* data, unsigned int length);

//Send data frame over UART
void UART_Send_Frame(uint16_t counts, uint16_t CPM);
