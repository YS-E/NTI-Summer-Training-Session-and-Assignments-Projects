#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#ifndef F_CPU
#define F_CPU               8000000UL
#endif

/* Timeout loop count limit to prevent infinite blocking */
#define USART_TIMEOUT       50000UL

#endif /* UART_CONFIG_H_ */