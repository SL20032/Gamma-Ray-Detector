/*
 * config.h
 *
 * Created: 30.09.2022 10:12:07
 *  Author: SL20032
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define SENSOR_PORT		PORTA
#define SENSOR_PIN		PIN6_bm
#define SENSOR_PIN_CR	PIN6CTRL
#define SENSOR_IQR		PORT_INT6_bp

#define UART_TX_PORT	PORTA
#define UART_TX_PIN		PIN1_bm

#define UART_RX_PORT	PORTA
#define UART_RX_PIN		PIN2_bm

#define UART_BAUDRATE	9600

#define PUSHBUTTON_PORT	PORTA
#define PUSHBUTTON_PIN	PIN3_bm

#define CPM_ARR_SIZE	5
#define CPM_PERIOD_S	5

#endif /* CONFIG_H_ */