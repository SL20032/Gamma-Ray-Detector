#include "UART.h"

const uint8_t Frame_start[3] PROGMEM = {0x41, 0x54, 0x2b}; //AT+

uint8_t Frame_buf[9]; 

uint8_t calc_crc(uint8_t* data, unsigned int data_length)
{
	uint8_t crc = 0;
	for (int i = 0; i < data_length; i++) {
		crc = (crc ^ data[i]);
	}
	return crc;
}

void uart_registers_init(USART_t* const usart, uint16_t baud_rate) {
  usart->CTRLA = 1 << USART_RXCIE_bp;  // Receive Complete Interrupt Enable: enabled

  usart->CTRLB = 1 << USART_RXEN_bp        // Enable receiver
                 | USART_RXMODE_NORMAL_gc  // Normal mode
                 | 1 << USART_TXEN_bp;     // Enable transmitter

  usart->BAUD = (uint16_t)USART_BAUD_RATE(baud_rate);
}

void UART_Init(void)
{
	UART_TX_PORT.DIRSET = UART_TX_PIN;
	UART_RX_PORT.DIRCLR = UART_RX_PIN;
	
	/*#if UART_TX_PORT != PIN6_bm 
		PORTMUX.CTRLB = 1 << PORTMUX_USART0_bp;
	#endif*/
	
	PORTMUX.CTRLB = 1 << PORTMUX_USART0_bp;
	
	uart_registers_init(&USART0,UART_BAUDRATE);
}

void uart_send_byte(USART_t* const usart, uint8_t data) {
  while (!(usart->STATUS & USART_DREIF_bm)) {
  }

  usart->TXDATAL = data;
}

void UART_Send(uint8_t* data, unsigned int length) {
  int indeks_send = 0;
  for (indeks_send = 0; indeks_send < length; indeks_send++) {
    uart_send_byte(&USART0, data[indeks_send]);
  }
}

void FRAME_Generator(uint16_t counts, uint16_t CPM)
{
	uint16_t indeks = 0;
	
	while (indeks < 3)
	{
		Frame_buf[indeks] = pgm_read_byte(&Frame_start[indeks]);
		indeks++;
	}
	
	Frame_buf[3] = counts >> 8;
	Frame_buf[4] = counts & 0xFF;
	Frame_buf[5] = CPM >> 8;
	Frame_buf[6] = CPM & 0xFF;
	Frame_buf[7] = calc_crc(Frame_buf,7);
	Frame_buf[8] = UART_STOP_BYTE;
}

void UART_Send_Frame(uint16_t counts, uint16_t CPM)
{
	FRAME_Generator(counts,CPM);
	UART_Send(Frame_buf,9);	
}
