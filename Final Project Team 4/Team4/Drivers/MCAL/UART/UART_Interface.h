#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/* 
 * Parameters:
 * - baud_rate: e.g., 9600, 115200
 * - data_bits: 5, 6, 7, or 8
 * - stop_bits: 1 or 2
 */
void USART_Init(u32 baud_rate, u8 data_bits, u8 stop_bits);
void USART_Transmit(u8 data);
u8 USART_Receive(void);
void USART_SendString(const char *str);

#endif /* UART_INTERFACE_H_ */