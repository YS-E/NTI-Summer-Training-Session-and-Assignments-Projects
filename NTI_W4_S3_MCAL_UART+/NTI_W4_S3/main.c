#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "LED_Interface.h"
#include "UART_Interface.h"

#define LED_PORT        PORTB_ID
#define RED_LED_PIN     PIN0
#define YELLOW_LED_PIN  PIN1
#define GREEN_LED_PIN   PIN2

int main(void)
{
	u8 received_data = 0;

	LED_voidInit(LED_PORT, RED_LED_PIN);
	LED_voidInit(LED_PORT, YELLOW_LED_PIN);
	LED_voidInit(LED_PORT, GREEN_LED_PIN);

	LED_voidTurnOff(LED_PORT, RED_LED_PIN);
	LED_voidTurnOff(LED_PORT, YELLOW_LED_PIN);
	LED_voidTurnOff(LED_PORT, GREEN_LED_PIN);

	USART_Init(9600);


	while (1)
	{
		received_data = USART_Receive();

		switch (received_data)
		{
			case 'R':
			LED_voidTurnOn(LED_PORT, RED_LED_PIN);
			break;

			case 'Y':
			LED_voidTurnOn(LED_PORT, YELLOW_LED_PIN);
			break;

			case 'G':
			LED_voidTurnOn(LED_PORT, GREEN_LED_PIN);
			break;

			case 'F':
			LED_voidTurnOff(LED_PORT, RED_LED_PIN);
			LED_voidTurnOff(LED_PORT, YELLOW_LED_PIN);
			LED_voidTurnOff(LED_PORT, GREEN_LED_PIN);
			break;
			
			default:
			break;
		}
	}
}